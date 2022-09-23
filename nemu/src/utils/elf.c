#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <elf.h>
#include <sys/mman.h>
#include <unistd.h>

#include <assert.h>
#include <stdio.h>
#include <string.h>

struct elf_symbol {
  void* addr;
  uint64_t size;
  char name[128];
};

struct elf_symbol elfsts[128];

int sts_len = 0;

static void* mmapfile(const char* filename) {
  FILE *pyfile = fopen(filename, "r");
  if (pyfile == NULL) {
    perror("fopen()");
    return 0;
  }
  if (fseek(pyfile, 0, SEEK_END)) {
    perror("fseek()");
    fclose(pyfile);
    return 0;
  }
  long pyfile_size = ftell(pyfile);
  // printf("file size: %zd\n", pyfile_size);

  void *pybytes = mmap(NULL, (size_t)pyfile_size, PROT_READ, MAP_PRIVATE,
                       fileno(pyfile), 0);
  if (pybytes == NULL) {
    fclose(pyfile);
    perror("mmap()");
    return 0;
  }
  fclose(pyfile);

  return pybytes;
}

static int parseelf(void* pybytes, struct elf_symbol* sts) {
  const unsigned char expected_magic[] = {ELFMAG0, ELFMAG1, ELFMAG2, ELFMAG3};
  Elf64_Ehdr elf_hdr;
  memmove(&elf_hdr, pybytes, sizeof(elf_hdr));
  if (memcmp(elf_hdr.e_ident, expected_magic, sizeof(expected_magic)) != 0) {
    perror("Target is not an ELF executable\n");
    return 1;
  }
  if (elf_hdr.e_ident[EI_CLASS] != ELFCLASS64) {
    perror("Sorry, only ELF-64 is supported.\n");
    return 1;
  }

  // printf("program header offset: %zd\n", elf_hdr.e_phoff);
  // printf("program header num: %d\n", elf_hdr.e_phnum);
  // printf("section header offset: %zd\n", elf_hdr.e_shoff);
  // printf("section header num: %d\n", elf_hdr.e_shnum);
  // printf("section header string table: %d\n", elf_hdr.e_shstrndx);

  // size_t string_offset = elf_hdr.e_shstrndx;
  // printf("string offset at %zd\n", string_offset);
  // printf("\n");

  char *cbytes = (char *)pybytes;

  size_t dynstr_off = 0;
  size_t strtab_off = 0;
  size_t symtab_sz = 0;
  size_t symtab_off = 0;
  int findstrtab = 0;

  for (uint16_t i = 0; i < elf_hdr.e_shnum; i++) {
    size_t offset = elf_hdr.e_shoff + i * elf_hdr.e_shentsize;
    Elf64_Shdr shdr;
    memmove(&shdr, pybytes + offset, sizeof(shdr));
    switch (shdr.sh_type) {
      case SHT_SYMTAB:
        symtab_off = shdr.sh_offset;
        symtab_sz = shdr.sh_size;
        break;
      case SHT_STRTAB:
        if (!dynstr_off) {
          // printf("found dynamic string table at %zd\n", shdr.sh_offset);
          dynstr_off = shdr.sh_offset;
        } else if (!findstrtab) {
          // printf("found string table at %zd\n", shdr.sh_offset);
          strtab_off = shdr.sh_offset;
          findstrtab = 1;
        }
        break;
      // case SHT_DYNSYM:
      //   dynsym_off = shdr.sh_offset;
      //   dynsym_sz = shdr.sh_size;
      //   printf("found dynsym table at %zd, size %zd\n", shdr.sh_offset,
      //          shdr.sh_size);
      //   break;
      default:
        break;
    }
  }
  assert(dynstr_off);
  assert(strtab_off);

  int sts_idx = 0;
  for (size_t j = 0; j * sizeof(Elf64_Sym) < symtab_sz; j++) {
    Elf64_Sym sym;
    size_t absoffset = symtab_off + j * sizeof(Elf64_Sym);
    memmove(&sym, cbytes + absoffset, sizeof(sym));
    if (sym.st_info == STT_FUNC || sym.st_info == 18) 
    {
      char* name = cbytes + strtab_off + sym.st_name;
      char* dynname = cbytes + dynstr_off + sym.st_name;
      // printf("SYMBOL TABLE ENTRY %zd\n", j);
      // printf("st_name = %x", sym.st_name);
      if (strlen(name)) {
        // printf(" (%s), addr: %lx", name, strtab_off + sym.st_name);
        strcpy(sts[sts_idx].name, name);
      } else {
        // printf(" (%s)", cbytes + dynstr_off + sym.st_name);
        strcpy(sts[sts_idx].name, dynname);
      }
      // printf("\n");
      // printf("st_info = %d\n", sym.st_info);
      // printf("st_other = %x\n", sym.st_other);
      // printf("st_shndx = %x\n", sym.st_shndx);
      // printf("st_value = %p\n", (void *)sym.st_value);
      // printf("st_size = %lx\n", sym.st_size);
      // printf("\n");
      sts[sts_idx].addr = (void*)sym.st_value;
      sts[sts_idx].size = sym.st_size;
      ++sts_idx;
    }
  }
  // printf("\n");

  //for (int i = 0; i < sts_len; ++i) {
  //  printf("addr: %p, name: %s\n", sts[i].addr, sts[i].name);
  //}
  return sts_idx;
}

char* find_symbol(void* addr) {
  for (int i = 0; i < sts_len; ++i) {
    if (addr >= elfsts[i].addr && addr < elfsts[i].addr + elfsts[i].size) {
      return elfsts[i].name;
    }
  }
  return NULL;
}

void init_elf(const char* elf_file) {
  if (elf_file == NULL) {
    perror("no input elf file!\n");
    return;
  }
  printf("Parsing elf: %s\n", elf_file);
  void *pybytes = mmapfile(elf_file);
  sts_len = parseelf(pybytes, elfsts);
}
