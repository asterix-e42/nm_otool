/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 01:48:05 by tdumouli          #+#    #+#             */
/*   Updated: 2019/04/29 23:38:06 by tdumouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_OTOOL_H
# define NM_OTOOL_H

# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include <mach-o/nlist.h>
# include <mach-o/loader.h>
# include <mach-o/fat.h>

void		handle_error(char *s);
void		nmotool_part(struct section_64 *sect, int i, char *ptr, char is64);
char		*get_segment();
void		putnb(uint64_t *number, char *str, char is64);
void		putnb_32(uint32_t *number, char *str);
void		set_segment_64(struct segment_command_64 *segment, void *ptr);
void		set_segment_32(struct segment_command *segment, void *ptr);
int			make_magic(char *filename, int pute);
void		print_output_sort_32(struct symtab_command *sym, char *ptr);
void		print_output_sort_64(struct symtab_command *sym, char *ptr);
void		handle_64(char *ptr, struct stat buf, char *av, int pute);
void		handle_32(char *ptr, struct stat buf, char *av, int pute);
char		get_symbol_letter_32(struct nlist array);
char		get_symbol_letter_64(struct nlist_64 array);
void		endian_mode(char is_endian);
uint16_t	endian2(uint16_t nb);
uint32_t	endian4(uint32_t nb);
uint64_t	endian8(uint64_t nb);
int			get_number_segment(int n);
void		magic(void *ptr, struct stat buf, char *av, int pute);

#endif
