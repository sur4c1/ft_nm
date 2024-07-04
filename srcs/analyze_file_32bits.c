/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_file_32bits.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyyyyyyy <yyyyyyyy@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 12:16:57 by yyyyyyyy          #+#    #+#             */
/*   Updated: 2024/07/04 11:02:01 by yyyyyyyy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <analyze_file_32bits.h>

static
char	*load_name(t_nm *nm, uint32_t name_offset, uint32_t name_table_offset)
{
	return ((char *) nm->file.raw_data + name_table_offset + name_offset);
}

static
int compare(t_symbol a, t_symbol b)
{
	int a_i;
	int b_i;

	if (a.name == NULL || b.name == NULL)
		return (0);
	a_i = 0;
	b_i = 0;
	while (a.name[a_i] && b.name[b_i])
	{
		while (a.name[a_i] && !ft_isalnum(a.name[a_i]))
			a_i++;
		while (b.name[b_i] && !ft_isalnum(b.name[b_i]))
			b_i++;
		if (
			ft_isalnum(a.name[a_i])
			&& ft_isalnum(b.name[b_i])
			&& ft_toupper(a.name[a_i]) != ft_toupper(b.name[b_i])
		)
			return (ft_toupper(a.name[a_i]) - ft_toupper(b.name[b_i]));
		a_i++;
		b_i++;
	}
	if (a.name[a_i] && !b.name[b_i])
		return (1);
	if (!a.name[a_i] && b.name[b_i])
		return (-1);
	if (ft_strcmp(a.name, b.name))
		return (ft_strcmp(a.name, b.name));
	return (a._32bits.value - b._32bits.value);
}

static
int rev_compare(t_symbol a, t_symbol b)
{
	return (-compare(a, b));
}

static
void	load_sections(t_nm *nm)
{
	int	i;

	if (nm->elf.header._32bits.shoff + nm->elf.header._32bits.shnum * nm->elf.header._32bits.shentsize > nm->file.size)
	{
		nm->file.status = MALFORMED_FILE;
		return ;
	}
	nm->elf.sections = ft_calloc(nm->elf.header._32bits.shnum, sizeof (t_section));
	if (nm->elf.sections == NULL)
	{
		nm->file.status = MALLOC_ERROR;
		return ;
	}
	i = 0;
	while (i < nm->elf.header._32bits.shnum)
	{
		ft_memcpy(nm->elf.sections + i, nm->file.raw_data + nm->elf.header._32bits.shoff + i * nm->elf.header._32bits.shentsize, nm->elf.header._32bits.shentsize);
		nm->elf.sections[i].name = load_name(nm, nm->elf.sections[i]._32bits.name, nm->elf.sections[nm->elf.header._32bits.shstrndx]._32bits.offset);
		i++;
	}
}

static
char load_type(t_nm *nm, t_symbol sym)
{
	char		type;
	char		bind;
	char		visibility;
	uint16_t	shndx;
	char		c;
	t_section	section;

	type = sym._32bits.info & 0xf;
	bind = sym._32bits.info >> 4;
	visibility = sym._32bits.other & 0x3;
	shndx = sym._32bits.shndx;
	if (shndx != SHN_UNDEF &&
		shndx != SHN_LORESERVE &&
		shndx != SHN_LOPROC &&
		shndx != SHN_HIPROC &&
		shndx != SHN_ABS &&
		shndx != SHN_COMMON &&
		shndx != SHN_HIRESERVE)
	section = nm->elf.sections[shndx];
	c = '?';
	if (bind == STB_WEAK)
	{
		if (type == STT_OBJECT)
		{
			c = 'V';
			if (shndx == SHN_UNDEF)
				c = 'v';
		}
		else
		{
			c = 'W';
			if (shndx == SHN_UNDEF)
				c = 'w';
		}
	}
	else if (shndx == SHN_UNDEF)
		c = 'U';
	else { // Real section and bind is GLOBAL or LOCAL
		if (shndx == SHN_ABS)
			c = 'a';
		else if (section._32bits.type == SHT_NOBITS)
			c = 'b';
		else if (section._32bits.flags & SHF_EXECINSTR)
			c = 't';
		else if (section._32bits.flags & SHF_WRITE)
			c = 'd';
		else if (section._32bits.flags & SHF_ALLOC)
			c = 'r';
		else if (section._32bits.flags & SHF_STRINGS)
			c = 'n';
		if (bind == STB_GLOBAL)
			c = ft_toupper(c);
	}
	return (c);
}

static
void	load_symbols(t_nm *nm)
{
	unsigned int	i;
	unsigned int	ii;
	unsigned int	nb_sections;

	nb_sections = nm->elf.header._32bits.shnum;
	i = 0;
	while (i < nb_sections)
	{
		if (
			nm->elf.sections[i]._32bits.type == SHT_SYMTAB
			// || nm->elf.sections[i]._32bits.type == SHT_DYNSYM
		)
		{
			if (nm->elf.sections[i]._32bits.offset + nm->elf.sections[i]._32bits.size > nm->file.size)
			{
				nm->file.status = MALFORMED_FILE;
				return ;
			}
			nm->elf.sections[i].symbols = ft_calloc(nm->elf.sections[i]._32bits.size / nm->elf.sections[i]._32bits.entsize, sizeof (t_symbol));
			ii = 0;
			while (ii < nm->elf.sections[i]._32bits.size / nm->elf.sections[i]._32bits.entsize)
			{
				ft_memcpy(
					&(nm->elf.sections[i].symbols[ii]._32bits),
					nm->file.raw_data + nm->elf.sections[i]._32bits.offset
						+ ii * nm->elf.sections[i]._32bits.entsize,
					nm->elf.sections[i]._32bits.entsize
				);
				if ((nm->elf.sections[i].symbols[ii]._32bits.info & 0xf) == STT_SECTION)
					nm->elf.sections[i].symbols[ii].name
						= load_name(
							nm,
							nm->elf.sections[nm->elf.sections[i].symbols[ii]._32bits.shndx]._32bits.name,
							nm->elf.sections[nm->elf.header._32bits.shstrndx]._32bits.offset
						);
				else
					nm->elf.sections[i].symbols[ii].name
						= load_name(
							nm, nm->elf.sections[i].symbols[ii]._32bits.name,
							nm->elf.sections[nm->elf.sections[i]._32bits.link]
								._32bits.offset
						);
				nm->elf.sections[i].symbols[ii].type = load_type(nm, nm->elf.sections[i].symbols[ii]);

				int	is_undef = nm->elf.sections[i].symbols[ii]._32bits.shndx == SHN_UNDEF;
				int	is_extern = (nm->elf.sections[i].symbols[ii]._32bits.info >> 4) == STB_GLOBAL
					|| (nm->elf.sections[i].symbols[ii]._32bits.info >> 4) == STB_WEAK;
				int is_debug = (nm->elf.sections[i].symbols[ii]._32bits.info & 0x4) == STT_FILE
					&& (nm->elf.sections[i].symbols[ii]._32bits.info >> 4) == STB_LOCAL;
				if (!nm->input.debug_symbols && is_debug)
					nm->elf.sections[i].symbols[ii].should_skip = 1;
				if (nm->input.extern_only && !is_extern)
					nm->elf.sections[i].symbols[ii].should_skip = 1;
				if (nm->input.undefined_only && !is_undef)
					nm->elf.sections[i].symbols[ii].should_skip = 1;
				if (ii == 0)
					nm->elf.sections[i].symbols[ii].should_skip = 1;

				ii++;
			}
		}
		i++;
	}
}

static
void	print_symbols(t_nm *nm)
{
	t_symbol		*symbols;
	unsigned int	total_symbols;
	unsigned int	i;

	total_symbols = 0;
	i = 0;
	while (i < nm->elf.header._32bits.shnum)
	{
		if (nm->elf.sections[i].symbols)
		{
			total_symbols += nm->elf.sections[i]._32bits.size / nm->elf.sections[i]._32bits.entsize;
		}
		i++;
	}
	symbols = ft_calloc(total_symbols, sizeof (t_symbol));
	i = 0;
	total_symbols = 0;
	while (i < nm->elf.header._32bits.shnum)
	{
		if (nm->elf.sections[i].symbols)
		{
			ft_memcpy(
				symbols + total_symbols,
				nm->elf.sections[i].symbols,
				sizeof (t_symbol) * (nm->elf.sections[i]._32bits.size / nm->elf.sections[i]._32bits.entsize)
			);
			total_symbols += nm->elf.sections[i]._32bits.size / nm->elf.sections[i]._32bits.entsize;
		}
		i++;
	}
	if (nm->input.no_sort)
		;
	else if (nm->input.reverse_sort)
		quick_sort(symbols, 0, total_symbols - 1, rev_compare);
	else
		quick_sort(symbols, 0, total_symbols - 1, compare);
	i = 0;
	while (i < total_symbols)
	{
		if (!symbols[i].should_skip)
		{
			char c = symbols[i].type;
			if ((symbols[i]._32bits.value == 0 || c == 'U')
					&& c != 'a'
					&& c != 'b'
					&& c != 't'
					&& c != 'T'
			)
				ft_printf("%8c %c %s\n", ' ', c, symbols[i].name);
			else
				ft_printf("%08x %c %s\n", symbols[i]._32bits.value, c, symbols[i].name);
		}
		i++;
	}
	if (!total_symbols)
		ft_dprintf(STDIN_FILENO, "ft_nm: %s: no symbols\n", nm->input.files.data[0]);
	free(symbols);
}

static
void cleanup(t_nm *nm)
{
	unsigned int	i;
	unsigned int	nb_sections;

	nb_sections = nm->elf.header._32bits.shnum;
	i = 0;
	while (i < nb_sections)
	{
		if (nm->elf.sections[i].symbols)
		{
			free(nm->elf.sections[i].symbols);
			nm->elf.sections[i].symbols = NULL;
		}
		i++;
	}
	free(nm->elf.sections);
	munmap(nm->file.raw_data, nm->file.size);
}

int	analyze_file_32bits(t_nm *nm, char *file_path)
{
	load_sections(nm);
	if (nm->file.status != SUCCESS)
	{
		ft_putstr_fd("ft_nm: ", STDIN_FILENO);
		ft_putstr_fd(nm->input.files.data[0], STDIN_FILENO);
		ft_putstr_fd(": file format not recognized\n", STDIN_FILENO);
		munmap(nm->file.raw_data, nm->file.size);
		return 1;
	}
	load_symbols(nm);
	print_symbols(nm);
	if (nm->input.files.nb_elem > 1)
		ft_printf("\n%s:\n", file_path);
	cleanup(nm);
	return 0;
}
