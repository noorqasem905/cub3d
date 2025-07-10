CC =  cc
CFLAGS =  -g#-Wextra -Wall -Werror -g
NAME = cub3d

SRCS = 	srcs/parsing.c				\
		srcs/cub3d_handling.c		\
		srcs/main.c					\
		srcs/utils.c				\
		# srcs/cub3d.c
all: $(NAME)

OBJS_DIR =includes/build
OBJS = $(SRCS:srcs/%.c=$(OBJS_DIR)/%.o)

LIBFT = libft
HEADERS = includes/cub3d.h
HIDE = $(if $(set),, @)
HIDED = $(if $(DIR),, --no-print-directory)

$(NAME): $(OBJS) $(HEADERS) $(LIBFT)
	$(HIDE)make $(HIDED) -C libft/printf
	$(HIDE)make $(HIDED) -C libft
	$(HIDE)make $(HIDED) -C libft bonus
	$(HIDE)$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -Llibft/printf -lftprintf -Llibft -lft -g

$(OBJS_DIR)/%.o: srcs/%.c $(HEADERS)
	$(HIDE)mkdir -p $(OBJS_DIR)
	$(HIDE)$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(HIDE)make $(HIDED) -C libft/printf clean
	$(HIDE)make $(HIDED) -C libft clean
	$(HIDE)rm -f $(OBJS)

fclean: clean
	$(HIDE)rm -f $(NAME)
	$(HIDE)make $(HIDED) -C libft/printf fclean
	$(HIDE)make $(HIDED) -C libft fclean
	$(HIDE)rm -df $(OBJS_DIR)

re: fclean all

.PHONY: all clean fclean re