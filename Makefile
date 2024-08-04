SRCS		=	main.c									\
				mlx.c									\
				parsing/color.c							\
				parsing/map.c							\
				parsing/parsing.c						\
				parsing/player.c						\
				parsing/texture.c						\
				player/input.c							\
				player/move.c							\
				player/turn.c							\
				player/mouse.c							\
				raycasting/draw.c						\
				raycasting/draw_utils.c					\
				raycasting/raycasting.c					\

ALL_SRCS		=	$(SRCS)

INCLUDES		=	-Iincludes							\
					-Ilibft/includes					\
					-Imlx

OBJ_DIR			=	objs

OBJS			=	$(addprefix $(OBJ_DIR)/, $(ALL_SRCS:.c=.o))

LD_FLAGS		=	-Llibft -Lmlx -lm -lbsd -lmlx -lXext -lX11 -lft -ltermcap -lreadline -O2

NAME			=	Cub3D

NB_OF_FILES	=	0
FIRST_CALL	=	0
I			=	0
TMP			=	0
TMP2		=	20

CC				=	cc
RM				=	@rm -f

LIBFT			=	libft/libft.a

FLAGS			=	-Wall -Werror -Wextra $(INCLUDES) 
#-g -fsanitize=address

$(OBJ_DIR)/%.o: srcs/%.c
				@mkdir -p $(@D)
				@$(CC) $(FLAGS) -c $< -o $@
				@$(eval I=$(shell echo $$(($(I)+1))))
				@if [ "$(FIRST_CALL)" -eq "1" ]; then\
					printf "\033[1A\033[2K";\
					printf "\033[1A\033[2K";\
					printf "\033[1A\033[2K";\
				fi
				@$(eval FIRST_CALL=1)
				@if [ "$(I)" -eq "$(NB_OF_FILES)" ]; then\
					printf "╭─ cub3d ────────────╮\n";\
					printf "│\033[0;32m████████████████████\033[0m│ %2d/%d compiled!\n" $(I) $(NB_OF_FILES);\
					printf "╰────────────────────╯\n";\
				else\
					printf "╭─ cub3d ────────────╮\n";\
					printf "│\033[0;32m%.*s%*c\033[0m│ %2d/%d %s\n" $(TMP) "████████████████████" $(TMP2) ' ' $(I) $(NB_OF_FILES) $<;\
					printf "╰────────────────────╯\n";\
				fi
				$(eval TMP=$(shell echo $$(($(I) * 20 / $(NB_OF_FILES) * 3))))
				$(eval TMP2=$(shell echo $$((20 - $(TMP) / 3))))

$(NAME):			$(LIBFT) init $(OBJS)
					@$(CC) $(OBJS) $(FLAGS) -o $(NAME) $(LD_FLAGS)

init:
				$(eval I=$(shell echo $$(find -name "*.o" | grep srcs | wc -l)))
				$(eval NB_OF_FILES=$(shell echo $$(find -name "*.c" | grep srcs | wc -l)))

all:				$(NAME) norme

$(LIBFT):
					@make -s -C libft -f Makefile

clean:
					@make -s -C libft -f Makefile clean
					$(RM) $(OBJS) $(OBJS_bonus)
					$(RM) -r $(OBJ_DIR)

fclean:				clean
					@make -s -C libft -f Makefile fclean
					$(RM) $(NAME) $(Name_B)
					$(RM) -r $(OBJ_DIR)

re:					fclean all
					@$(CC) $(OBJS) $(FLAGS) -o $(NAME) $(LD_FLAGS)

bonus:			all

norme:
					@echo "\033[0;33mChecking \033[1;31mnorminette\033[0;33m\t\033[1;30m[\033[1;31m⌛\033[1;30m]\033[0m"
					@if norminette srcs includes libft > norm.tmp; then\
						echo -n "\033[1A\033[25C\033[1;32m✓\033[0m] \033[28D\033[1B";\
					else\
						echo -n "\033[1A\033[25C\033[1;31mX\033[0m] \033[28D\033[1B";\
						cat norm.tmp | grep Error;\
					fi;
					@rm norm.tmp

.PHONY:				all clean fclean re
