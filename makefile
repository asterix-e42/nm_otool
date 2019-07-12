# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/08 16:51:40 by tdumouli          #+#    #+#              #
#    Updated: 2019/07/13 01:23:27 by tdumouli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

AUTEUR = "tdumouli"
NAMEI =
NAME_NM = ft_nm
NAME_OTOOL = ft_otool
OBJDIR = ./objet
SRCDIR = ./src
INCDIR = -I./include -I./libft/include


NM_OTOOL = error.o segment.o mach_o.o main.o endian.o archive.o
NM = handle.o output_32.o output_64.o part.o get_symbol_letter.o
OTOOL = handle.o part.o nm.o
LIB = libft/libft.a

OBJ_NM =	$(addprefix $(OBJDIR)/, $(NM_OTOOL)) \
			$(addprefix $(OBJDIR)/nm/, $(NM))

OBJ_OTOOL =	$(addprefix $(OBJDIR)/, $(NM_OTOOL)) \
			$(addprefix $(OBJDIR)/otool/, $(OTOOL))
LSTDIRI = nm otool
debugg = 

############################## normaly no change ###############################


NO_COLOR="\x1b[39m"
RED="\x1b[31m"
GREEN="\x1b[32m"
YELLOW="\x1b[33m"
CC = gcc
CFLAGS = $(INCDIR) -Wall -Wextra -Werror
DEBU = -fno-omit-frame-pointer -g
#-fsanitize=address -fno-omit-frame-pointer -g3
MAKE = /usr/bin/make

LSTDIR=	$(addprefix $(OBJDIR)/, $(LSTDIRI)) \

ifneq ($(NAMEI), )
all: objdir $(NAMEI)
	@echo $(GREEN)"compilation reussi"$(NO_COLOR)
else
all: objdir
	@$(MAKE) -C ./libft
	@$(MAKE) $(NAME_NM)
	@$(MAKE) $(NAME_OTOOL)
	@echo $(GREEN)"compilation reussi cpl"$(NO_COLOR)
endif

objdir:
	@if ! [ -d $(OBJDIR) ]; then\
		mkdir $(OBJDIR) $(LSTDIR);\
	fi

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@
	@echo $(GREEN)$@" compile"$(NO_COLOR)

$(NAMEI): $(OBJ)
	@ar cr $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo $(GREEN)"library compile"$(NO_COLOR)

$(NAME_NM): $(OBJ_NM)
	$(MAKE) -C ./libft
	$(CC) $(OBJ_NM) ./$(LIB) -o $(NAME_NM) $(DEBUG)
	@echo $(GREEN)$(NAME_NM)" a ete cree"$(NO_COLOR)

$(NAME_OTOOL): $(OBJ_OTOOL)
	$(MAKE) -C ./libft
	$(CC) $(OBJ_OTOOL) ./$(LIB) -o $(NAME_OTOOL) $(DEBUG)
	@echo $(GREEN)$(NAME_OTOOL)" a ete cree"$(NO_COLOR)

clean:
	@$(MAKE) clean -C ./libft
	@rm -rf $(OBJ_NM) $(OBJ_OTOOL)
	@$(MAKE) cleanv

ifeq ($(shell find . -type f | grep "\.o"), )
cleanv:
	@echo $(GREEN)"les objets sont clean"$(NO_COLOR)
else
cleanv:
	@echo $(RED)"il ya probleme"
	@echo $(YELLOW)$(shell echo | find . -type f | grep "\.o" | cat -e)
	exit
endif

cl:
	@if [ "test" = "test" ]; then\
		echo "Hello world";\
	fi

auteur:
	@echo $(AUTEUR) > auteur
	@echo $(GREEN)"le fichier auteur a bien ete cree"$(NO_COLOR)

fclean: clean
	@$(MAKE) fclean -C ./libft
	@rm -f $(NAME_NM) $(NAME_OTOOL)
	@echo $(GREEN)"tout est clean"$(NO_COLOR)

re: fclean
	@make all

.PHONY: all clean fclean re cleanv anc
