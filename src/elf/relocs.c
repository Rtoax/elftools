#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <string.h>
#include <malloc.h>
#include <errno.h>
#include <inttypes.h>

#include <elf/elf_api.h>
#include <utils/util.h>
#include <utils/log.h>


#if defined(__x86_64__)
static const char *R_X86_64_STRING(int r) {
#define _I(v) case v: return #v;
	switch (r) {
	_I(R_X86_64_NONE)
	_I(R_X86_64_64)
	_I(R_X86_64_PC32)
	_I(R_X86_64_GOT32)
	_I(R_X86_64_PLT32)
	_I(R_X86_64_COPY)
	_I(R_X86_64_GLOB_DAT)
	_I(R_X86_64_JUMP_SLOT)
	_I(R_X86_64_RELATIVE)
	_I(R_X86_64_GOTPCREL)
	_I(R_X86_64_32)
	_I(R_X86_64_32S)
	_I(R_X86_64_16)
	_I(R_X86_64_PC16)
	_I(R_X86_64_8)
	_I(R_X86_64_PC8)
	_I(R_X86_64_DTPMOD64)
	_I(R_X86_64_DTPOFF64)
	_I(R_X86_64_TPOFF64)
	_I(R_X86_64_TLSGD)
	_I(R_X86_64_TLSLD)
	_I(R_X86_64_DTPOFF32)
	_I(R_X86_64_GOTTPOFF)
	_I(R_X86_64_TPOFF32)
	_I(R_X86_64_PC64)
	_I(R_X86_64_GOTOFF64)
	_I(R_X86_64_GOTPC32)
	_I(R_X86_64_GOT64)
	_I(R_X86_64_GOTPCREL64)
	_I(R_X86_64_GOTPC64)
	_I(R_X86_64_GOTPLT64)
	_I(R_X86_64_PLTOFF64)
	_I(R_X86_64_SIZE32)
	_I(R_X86_64_SIZE64)
	_I(R_X86_64_GOTPC32_TLSDESC)
	_I(R_X86_64_TLSDESC_CALL)
	_I(R_X86_64_TLSDESC)
	_I(R_X86_64_IRELATIVE)
	_I(R_X86_64_RELATIVE64)
	_I(R_X86_64_GOTPCRELX)
	_I(R_X86_64_REX_GOTPCRELX)
	default: return "Unknown";
	}
#undef _I
};

static const char *r_x86_64_name(int r)
{
	return R_X86_64_STRING(r);
}

#elif defined(__aarch64__)

static const char *R_AARCH64_STRING(int r) {
#define _I(v) case v: return #v;
	switch (r) {
	_I(R_AARCH64_NONE)
	_I(R_AARCH64_P32_ABS32)
	_I(R_AARCH64_P32_COPY)
	_I(R_AARCH64_P32_GLOB_DAT)
	_I(R_AARCH64_P32_JUMP_SLOT)
	_I(R_AARCH64_P32_RELATIVE)
	_I(R_AARCH64_P32_TLS_DTPMOD)
	_I(R_AARCH64_P32_TLS_DTPREL)
	_I(R_AARCH64_P32_TLS_TPREL)
	_I(R_AARCH64_P32_TLSDESC)
	_I(R_AARCH64_P32_IRELATIVE)
	_I(R_AARCH64_ABS64)
	_I(R_AARCH64_ABS32)
	_I(R_AARCH64_ABS16)
	_I(R_AARCH64_PREL64)
	_I(R_AARCH64_PREL32)
	_I(R_AARCH64_PREL16)
	_I(R_AARCH64_MOVW_UABS_G0)
	_I(R_AARCH64_MOVW_UABS_G0_NC)
	_I(R_AARCH64_MOVW_UABS_G1)
	_I(R_AARCH64_MOVW_UABS_G1_NC)
	_I(R_AARCH64_MOVW_UABS_G2)
	_I(R_AARCH64_MOVW_UABS_G2_NC)
	_I(R_AARCH64_MOVW_UABS_G3)
	_I(R_AARCH64_MOVW_SABS_G0)
	_I(R_AARCH64_MOVW_SABS_G1)
	_I(R_AARCH64_MOVW_SABS_G2)
	_I(R_AARCH64_LD_PREL_LO19)
	_I(R_AARCH64_ADR_PREL_LO21)
	_I(R_AARCH64_ADR_PREL_PG_HI21)
	_I(R_AARCH64_ADR_PREL_PG_HI21_NC)
	_I(R_AARCH64_ADD_ABS_LO12_NC)
	_I(R_AARCH64_LDST8_ABS_LO12_NC)
	_I(R_AARCH64_TSTBR14)
	_I(R_AARCH64_CONDBR19)
	_I(R_AARCH64_JUMP26)
	_I(R_AARCH64_CALL26)
	_I(R_AARCH64_LDST16_ABS_LO12_NC)
	_I(R_AARCH64_LDST32_ABS_LO12_NC)
	_I(R_AARCH64_LDST64_ABS_LO12_NC)
	_I(R_AARCH64_MOVW_PREL_G0)
	_I(R_AARCH64_MOVW_PREL_G0_NC)
	_I(R_AARCH64_MOVW_PREL_G1)
	_I(R_AARCH64_MOVW_PREL_G1_NC)
	_I(R_AARCH64_MOVW_PREL_G2)
	_I(R_AARCH64_MOVW_PREL_G2_NC)
	_I(R_AARCH64_MOVW_PREL_G3)
	_I(R_AARCH64_LDST128_ABS_LO12_NC)
	_I(R_AARCH64_MOVW_GOTOFF_G0)
	_I(R_AARCH64_MOVW_GOTOFF_G0_NC)
	_I(R_AARCH64_MOVW_GOTOFF_G1)
	_I(R_AARCH64_MOVW_GOTOFF_G1_NC)
	_I(R_AARCH64_MOVW_GOTOFF_G2)
	_I(R_AARCH64_MOVW_GOTOFF_G2_NC)
	_I(R_AARCH64_MOVW_GOTOFF_G3)
	_I(R_AARCH64_GOTREL64)
	_I(R_AARCH64_GOTREL32)
	_I(R_AARCH64_GOT_LD_PREL19)
	_I(R_AARCH64_LD64_GOTOFF_LO15)
	_I(R_AARCH64_ADR_GOT_PAGE)
	_I(R_AARCH64_LD64_GOT_LO12_NC)
	_I(R_AARCH64_LD64_GOTPAGE_LO15)
	_I(R_AARCH64_TLSGD_ADR_PREL21)
	_I(R_AARCH64_TLSGD_ADR_PAGE21)
	_I(R_AARCH64_TLSGD_ADD_LO12_NC)
	_I(R_AARCH64_TLSGD_MOVW_G1)
	_I(R_AARCH64_TLSGD_MOVW_G0_NC)
	_I(R_AARCH64_TLSLD_ADR_PREL21)
	_I(R_AARCH64_TLSLD_ADR_PAGE21)
	_I(R_AARCH64_TLSLD_ADD_LO12_NC)
	_I(R_AARCH64_TLSLD_MOVW_G1)
	_I(R_AARCH64_TLSLD_MOVW_G0_NC)
	_I(R_AARCH64_TLSLD_LD_PREL19)
	_I(R_AARCH64_TLSLD_MOVW_DTPREL_G2)
	_I(R_AARCH64_TLSLD_MOVW_DTPREL_G1)
	_I(R_AARCH64_TLSLD_MOVW_DTPREL_G1_NC)
	_I(R_AARCH64_TLSLD_MOVW_DTPREL_G0)
	_I(R_AARCH64_TLSLD_MOVW_DTPREL_G0_NC)
	_I(R_AARCH64_TLSLD_ADD_DTPREL_HI12)
	_I(R_AARCH64_TLSLD_ADD_DTPREL_LO12)
	_I(R_AARCH64_TLSLD_ADD_DTPREL_LO12_NC)
	_I(R_AARCH64_TLSLD_LDST8_DTPREL_LO12)
	_I(R_AARCH64_TLSLD_LDST8_DTPREL_LO12_NC)
	_I(R_AARCH64_TLSLD_LDST16_DTPREL_LO12)
	_I(R_AARCH64_TLSLD_LDST16_DTPREL_LO12_NC)
	_I(R_AARCH64_TLSLD_LDST32_DTPREL_LO12)
	_I(R_AARCH64_TLSLD_LDST32_DTPREL_LO12_NC)
	_I(R_AARCH64_TLSLD_LDST64_DTPREL_LO12)
	_I(R_AARCH64_TLSLD_LDST64_DTPREL_LO12_NC)
	_I(R_AARCH64_TLSIE_MOVW_GOTTPREL_G1)
	_I(R_AARCH64_TLSIE_MOVW_GOTTPREL_G0_NC)
	_I(R_AARCH64_TLSIE_ADR_GOTTPREL_PAGE21)
	_I(R_AARCH64_TLSIE_LD64_GOTTPREL_LO12_NC)
	_I(R_AARCH64_TLSIE_LD_GOTTPREL_PREL19)
	_I(R_AARCH64_TLSLE_MOVW_TPREL_G2)
	_I(R_AARCH64_TLSLE_MOVW_TPREL_G1)
	_I(R_AARCH64_TLSLE_MOVW_TPREL_G1_NC)
	_I(R_AARCH64_TLSLE_MOVW_TPREL_G0)
	_I(R_AARCH64_TLSLE_MOVW_TPREL_G0_NC)
	_I(R_AARCH64_TLSLE_ADD_TPREL_HI12)
	_I(R_AARCH64_TLSLE_ADD_TPREL_LO12)
	_I(R_AARCH64_TLSLE_ADD_TPREL_LO12_NC)
	_I(R_AARCH64_TLSLE_LDST8_TPREL_LO12)
	_I(R_AARCH64_TLSLE_LDST8_TPREL_LO12_NC)
	_I(R_AARCH64_TLSLE_LDST16_TPREL_LO12)
	_I(R_AARCH64_TLSLE_LDST16_TPREL_LO12_NC)
	_I(R_AARCH64_TLSLE_LDST32_TPREL_LO12)
	_I(R_AARCH64_TLSLE_LDST32_TPREL_LO12_NC)
	_I(R_AARCH64_TLSLE_LDST64_TPREL_LO12)
	_I(R_AARCH64_TLSLE_LDST64_TPREL_LO12_NC)
	_I(R_AARCH64_TLSDESC_LD_PREL19)
	_I(R_AARCH64_TLSDESC_ADR_PREL21)
	_I(R_AARCH64_TLSDESC_ADR_PAGE21)
	_I(R_AARCH64_TLSDESC_LD64_LO12)
	_I(R_AARCH64_TLSDESC_ADD_LO12)
	_I(R_AARCH64_TLSDESC_OFF_G1)
	_I(R_AARCH64_TLSDESC_OFF_G0_NC)
	_I(R_AARCH64_TLSDESC_LDR)
	_I(R_AARCH64_TLSDESC_ADD)
	_I(R_AARCH64_TLSDESC_CALL)
	_I(R_AARCH64_TLSLE_LDST128_TPREL_LO12)
	_I(R_AARCH64_TLSLE_LDST128_TPREL_LO12_NC)
	_I(R_AARCH64_TLSLD_LDST128_DTPREL_LO12)
	_I(R_AARCH64_TLSLD_LDST128_DTPREL_LO12_NC)
	_I(R_AARCH64_COPY)
	_I(R_AARCH64_GLOB_DAT)
	_I(R_AARCH64_JUMP_SLOT)
	_I(R_AARCH64_RELATIVE)
	_I(R_AARCH64_TLS_DTPMOD)
	_I(R_AARCH64_TLS_DTPREL)
	_I(R_AARCH64_TLS_TPREL)
	_I(R_AARCH64_TLSDESC)
	_I(R_AARCH64_IRELATIVE)
	default: return "Unknown";
	}
#undef _I
};

static const char *r_aarch64_name(int r)
{
	return R_AARCH64_STRING(r);
}
#endif

// GELF_R_TYPE (rel->r_info)
const char *rela_type_string(int r)
{
#if defined(__x86_64__)
	return r_x86_64_name(r);
#elif defined(__aarch64__)
	return r_aarch64_name(r);
#endif
}

void print_rela(GElf_Rela *rela)
{
	printf("%016lx %16ld %16ld %16ld\n",
		rela->r_offset, rela->r_info,
		GELF_R_TYPE(rela->r_info), rela->r_addend);
}

static int
handle_relocs_rel(struct elf_file *elf, GElf_Shdr *shdr, Elf_Scn *scn)
{
	lwarning("SHT_REL not support yet.\n");
	return -1;
}

static int
handle_relocs_rela(struct elf_file *elf, GElf_Shdr *shdr, Elf_Scn *scn)
{
	int class = gelf_getclass(elf->elf);
	size_t sh_entsize = gelf_fsize (elf->elf, ELF_T_RELA, 1, EV_CURRENT);
	int nentries = shdr->sh_size / sh_entsize;

	/* Get the data of the section.  */
	Elf_Data *data = elf_getdata(scn, NULL);
	if (data == NULL)
		return -1;

	/* Get the symbol table information.  */
	Elf_Scn *symscn = elf_getscn (elf->elf, shdr->sh_link);
	GElf_Shdr symshdr_mem;
	GElf_Shdr *symshdr = gelf_getshdr (symscn, &symshdr_mem);
	Elf_Data *symdata = elf_getdata (symscn, NULL);

	/* Get the section header of the section the relocations are for.  */
	GElf_Shdr destshdr_mem;
	GElf_Shdr *destshdr = gelf_getshdr (elf_getscn (elf->elf, shdr->sh_info),
			&destshdr_mem);

	if (unlikely (symshdr == NULL || symdata == NULL || destshdr == NULL)) {
		lerror("\nInvalid symbol table at offset %#0" PRIx64 "\n",
			shdr->sh_offset);
		return -1;
	}

	/* Search for the optional extended section index table.  */
	Elf_Data *xndxdata = NULL;
	int xndxscnidx = elf_scnshndx (scn);
	if (unlikely (xndxscnidx > 0))
		xndxdata = elf_getdata (elf_getscn (elf->elf, xndxscnidx), NULL);

	/* Get the section header string table index.  */
	size_t shstrndx = elf->shdrstrndx;

	if (shdr->sh_info != 0) {
		// Relocation section [11] '.rela.plt' for section [24] '.got' at offset 0x2b38 contains 105 entries:
		ldebug("Relocation section [%2zu] '%s' for section [%2u] '%s' at offset %#0" PRIx64 " contains %d entry:\n",
			elf_ndxscn (scn),
			elf_strptr (elf->elf, shstrndx, shdr->sh_name),
			(unsigned int) shdr->sh_info,
			elf_strptr (elf->elf, shstrndx, destshdr->sh_name),
			shdr->sh_offset,
			nentries);
	} else {
		/* The .rela.dyn section does not refer to a specific section but
		 * instead of section index zero.  Do not try to print a section
		 * name.  */
		// Relocation section [10] '.rela.dyn' at offset 0x1728 contains 214 entries:
		ldebug("Relocation section [%2u] '%s' at offset %#0" PRIx64 " contains %d entry:\n",
			(unsigned int) elf_ndxscn (scn),
			elf_strptr (elf->elf, shstrndx, shdr->sh_name),
			shdr->sh_offset,
			nentries);
	}

	int is_statically_linked = 0;

	for (int cnt = 0; cnt < nentries; ++cnt) {

		GElf_Rela relmem;
		GElf_Rela *rel = gelf_getrela (data, cnt, &relmem);

		if (likely (rel != NULL)) {
			GElf_Sym symmem;
			Elf32_Word xndx;
			GElf_Sym *sym = gelf_getsymshndx (symdata, xndxdata,
				GELF_R_SYM (rel->r_info),
				&symmem, &xndx);

			if (unlikely (sym == NULL)) {
				/* As a special case we have to handle relocations in static
				 * executables.  This only happens for IRELATIVE relocations
				 * (so far).  There is no symbol table.  */
				if (is_statically_linked == 0) {
					/* Find the program header and look for a PT_INTERP
					 * entry. */
					is_statically_linked = -1;

					if (elf->ehdr->e_type == ET_EXEC) {
						is_statically_linked = 1;

						for (size_t inner = 0; inner < elf->phdrnum; ++inner) {
							GElf_Phdr phdr_mem;
							GElf_Phdr *phdr = gelf_getphdr (elf->elf, inner,
								&phdr_mem);
							if (phdr != NULL && phdr->p_type == PT_INTERP) {
								is_statically_linked = -1;
								break;
							}
						}
					}
				}

				if (is_statically_linked > 0 && shdr->sh_link == 0) {
					ldebug("  %#0*" PRIx64 "  %-15s %*s  %#6" PRIx64 " %s\n",
						class == ELFCLASS32 ? 10 : 18,
						rel->r_offset,
						rela_type_string(GELF_R_TYPE (rel->r_info)),
						class == ELFCLASS32 ? 10 : 18, "",
						rel->r_addend,
						elf_strptr (elf->elf, shstrndx, destshdr->sh_name));
				} else {
					ldebug("  %#0*" PRIx64 "  %-15s <%s %ld>\n",
						class == ELFCLASS32 ? 10 : 18,
						rel->r_offset,
						rela_type_string(GELF_R_TYPE (rel->r_info)),
						(long int) GELF_R_SYM (rel->r_info));
				}

			} // sym == NULL
			else if (GELF_ST_TYPE (sym->st_info) != STT_SECTION) {
				ldebug("  %#0*" PRIx64 "  %-15s %#0*" PRIx64 "  %+6" PRId64 " %s\n",
					class == ELFCLASS32 ? 10 : 18,
					rel->r_offset,
					rela_type_string(GELF_R_TYPE (rel->r_info)),
					class == ELFCLASS32 ? 10 : 18,
					sym->st_value,
					rel->r_addend,
					elf_strptr (elf->elf, symshdr->sh_link, sym->st_name));

			} else { // STT_SECTION

				/* This is a relocation against a STT_SECTION symbol.  */
				GElf_Shdr secshdr_mem;
				GElf_Shdr *secshdr;
				secshdr = gelf_getshdr(elf_getscn(elf->elf,
							sym->st_shndx == SHN_XINDEX
							? xndx : sym->st_shndx),
							&secshdr_mem);

				if (unlikely (secshdr == NULL)) {
					ldebug("  %#0*" PRIx64 "  %-15s <%s %ld>\n",
						class == ELFCLASS32 ? 10 : 18, rel->r_offset,
						rela_type_string(GELF_R_TYPE (rel->r_info)),
						(long int) (sym->st_shndx == SHN_XINDEX
						? xndx : sym->st_shndx));

				} else {

					ldebug("%#0*" PRIx64 "  %-15s %#0*" PRIx64 "  %+6" PRId64 " %s\n",
						class == ELFCLASS32 ? 10 : 18, rel->r_offset,
						rela_type_string(GELF_R_TYPE (rel->r_info)),
						class == ELFCLASS32 ? 10 : 18, sym->st_value,
						rel->r_addend,
						elf_strptr (elf->elf, shstrndx, secshdr->sh_name));
				}
			}
		}
	}


	return 0;
}

int handle_relocs(struct elf_file *elf, GElf_Shdr *shdr, Elf_Scn *scn)
{
	if (shdr->sh_type == SHT_REL)
		return handle_relocs_rel(elf, shdr, scn);
	else if (shdr->sh_type == SHT_RELA)
		return handle_relocs_rela(elf, shdr, scn);

	return -EINVAL;
}

