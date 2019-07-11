/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 01:48:05 by tdumouli          #+#    #+#             */
/*   Updated: 2019/07/11 19:06:49 by tdumouli         ###   ########.fr       */
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

int			handle_error(char *s);
int			handle_error_free(char *s);
int			nmotool_part(struct section_64 *sect, int i, char *ptr, void *b);
char		*get_segment(int reset);
void		putnb(uint64_t *number, char *str, char is64);
void		putnb_32(uint32_t *number, char *str);
int			set_segment_64(struct segment_command_64 *segment, void *ptr,
		void *buf);
int			set_segment_32(struct segment_command *segment, void *ptr,
		void *buf);
int			make_magic(char *filename, int pute);
int			print_output_sort_32(struct symtab_command *sym, char *ptr);
int			print_output_sort_64(struct symtab_command *sym, char *ptr);
int			handle_64(void *ptr, struct stat buf, char *av, int pute);
int			handle_32(void *ptr, struct stat buf, char *av, int pute);
char		get_symbol_letter_32(struct nlist array);
char		get_symbol_letter_64(struct nlist_64 array);
void		endian_mode(char is_endian);
uint16_t	endian2(uint16_t nb);
uint32_t	endian4(uint32_t nb);
uint64_t	endian8(uint64_t nb);
int			get_number_segment(int n);
int			magic(void *ptr, struct stat buf, char *av, int pute);
int			is_nm(void);
int			god(void *ptr, int reset);
char		*archive_2(int32_t jmp, char *av, char *archive);
int8_t		is_arch(int is);

#endif
