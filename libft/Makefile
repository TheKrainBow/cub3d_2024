SRCS_CHAR	=	char/ft_isalnum.c						\
				char/ft_isalpha.c						\
				char/ft_isascii.c						\
				char/ft_isdigit.c						\
				char/ft_isprint.c						\
				char/ft_iswhitespace.c					\
				char/ft_strmap.c						\
				char/ft_tolower.c						\
				char/ft_toupper.c						\

SRCS_FILE	=	file/get_next_line.c					\
				file/store_file.c						\

SRCS_LST	=	lst/ft_lst_to_tab.c						\
				lst/ft_lstadd_back.c					\
				lst/ft_lstadd_front.c					\
				lst/ft_lstclear.c						\
				lst/ft_lstdelone.c						\
				lst/ft_lstfirst.c						\
				lst/ft_lstiter.c						\
				lst/ft_lstlast.c						\
				lst/ft_lstmap.c							\
				lst/ft_lstnew.c							\
				lst/ft_lstprint.c						\
				lst/ft_lstrmone.c						\
				lst/ft_lstsplit.c						\
				lst/ft_lsttotab_if.c					\
				lst/ft_lstrm_if.c						\
				lst/ft_lstsize.c						\

SRCS_MATH	=	math/ft_atoi.c							\
				math/ft_itoa.c							\
				math/ft_max.c							\
				math/ft_min.c							\
				math/ft_pow.c							\
				math/ft_swap.c							\

SRCS_MEM	=	mem/ft_bzero.c							\
				mem/ft_calloc.c							\
				mem/ft_free_tab.c						\
				mem/ft_memccpy.c						\
				mem/ft_memchr.c							\
				mem/ft_memcmp.c							\
				mem/ft_memcpy.c							\
				mem/ft_memmove.c						\
				mem/ft_memset.c							\

SRCS_PRINT	=	print/ft_lstprint.c						\
				print/ft_print_tab.c					\
				print/ft_putchar.c						\
				print/ft_putendl.c						\
				print/ft_putnbr.c						\
				print/ft_putstr.c						\
				print/ft_printf.c						\
				print/ft_printf_utils.c					\

SRCS_STRS	=	strs/ft_split.c							\
				strs/ft_strchr.c						\
				strs/ft_strcmp.c						\
				strs/ft_strdup.c						\
				strs/ft_strisint.c						\
				strs/ft_strjoin_to.c					\
				strs/ft_strjoin.c						\
				strs/ft_strlcat.c						\
				strs/ft_strlcpy.c						\
				strs/ft_strlen.c						\
				strs/ft_strmapi.c						\
				strs/ft_strncmp.c						\
				strs/ft_strndup.c						\
				strs/ft_strnstr.c						\
				strs/ft_strrchr.c						\
				strs/ft_strs_to_tab.c					\
				strs/ft_strtrim.c						\
				strs/ft_strtrunc.c						\
				strs/ft_substr.c						\
				strs/ft_sort_strs.c						\
				strs/ft_tabjoin.c						\
				strs/ft_tablen.c						\
				strs/ft_tabrmi.c						\
				strs/ft_tabcpy.c						\


SRCS		=	$(SRCS_CHAR) $(SRCS_FILE) $(SRCS_LST) $(SRCS_MATH) $(SRCS_MEM) $(SRCS_PRINT) $(SRCS_STRS)

OBJS		=	$(SRCS:.c=.o)

NO_OF_FILES	=	$(words $(SRCS))
FIRST_CALL	=	0
I			=	0
TMP = 0
TMP2 = 20

CC			=	@cc
RM			=	@rm -f
NAME		=	libft.a

FLAGS		=	-Wall -Werror -Wextra -Iincludes #-fsanitize=address -g


.c.o:
				$(eval I=$(shell echo $$(($(I)+1))))
				@if [ "$(FIRST_CALL)" -eq "1" ]; then\
					printf "\033[1A\033[2K";\
					printf "\033[1A\033[2K";\
					printf "\033[1A\033[2K";\
				fi
				@$(eval FIRST_CALL=$(shell echo 1))
				@if [ "$(I)" -eq "$(NO_OF_FILES)" ]; then\
					printf "╭─ libft ────────────╮\n";\
					printf "│\033[0;32m████████████████████\033[0m│ %2d/%d compiled!\n" $(I) $(NO_OF_FILES);\
					printf "╰────────────────────╯\n";\
				else\
					printf "╭─ libft ────────────╮\n";\
					printf "│\033[0;32m%.*s%*c\033[0m│ %2d/%d %s\n" $(TMP) "████████████████████" $(TMP2) ' ' $(I) $(NO_OF_FILES) $<;\
					printf "╰────────────────────╯\n";\
				fi
				$(CC) $(FLAGS) -c $< -o $(<:.c=.o)
				$(eval TMP=$(shell echo $$(($(I) * 20 / $(NO_OF_FILES) * 3))))
				$(eval TMP2=$(shell echo $$((20 - $(TMP) / 3))))

$(NAME):		init_i $(OBJS)
				@ar rc $(NAME) $(OBJS)
				@ranlib $(NAME)

init_i:
				$(eval I=$(shell echo $$(find -name "*.o" | wc -l)))

all:			$(NAME)

clean:
				$(RM) $(OBJS)

fclean:			
				$(RM) $(NAME)
				$(RM) $(OBJS)

re:				fclean all


.PHONY:			all clean fclean re
