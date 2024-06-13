/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maagosti <maagosti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 04:57:07 by maagosti          #+#    #+#             */
/*   Updated: 2024/05/29 03:28:27 by maagosti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>
# include "color.h"
# include "ft_printf.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

typedef struct s_list
{
	void				*content;
	struct s_list		*next;
	struct s_list		*prev;
}						t_list;

/*
**			CHAR
*/

int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_iswhitespace(int c);
int				ft_isdigit(int c);
int				ft_isprint(int c);
int				ft_strmap(char *str, int (*f)(int));
int				ft_tolower(int c);
int				ft_toupper(int c);

/*
**			LST
*/

char			**ft_lst_to_tab(t_list *lst);
void			ft_lstadd_back(t_list **alst, t_list *new);
void			ft_lstadd_front(t_list **alst, t_list *new);
void			ft_lstclear(t_list **lst, void (*del)(void*));
void			ft_lstdelone(t_list *lst, void (*del)(void*));
void			ft_lstfirst(t_list **list);
void			ft_lstiter(t_list *lst, void (*f)(void *));
void			ft_lstlast(t_list **lst);
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *),
					void (*del)(void *));
void			ft_lstrmone(t_list *lst, void (*del)(void*));
t_list			*ft_lstnew(void *content);
int				ft_lstsize(t_list *lst);
t_list			**ft_lstsplit(t_list *lst, int (*cmp)(void *),
					void (*del)(void *));
char			**ft_lsttotab_if(t_list *lst, int (*cmp)(void *),
					char *(*conv)(void *));
void			ft_lstrm_if(t_list **lst, int (*cmp)(void *),
					void (*del)(void*));

/*
**				FILE
*/

char			*get_next_line(int fd);
char			*store_file(int fd);

/*
**				MATH
*/

int				ft_atoi(const char *str);
char			*ft_itoa(int n);
int				ft_max(int a, int b);
int				ft_min(int a, int b);
int				ft_pow(int a, int b);
void			ft_swap(int *a, int *b);

/*
**				MEM
*/

void			ft_bzero(void *s, size_t n);
void			*ft_calloc(size_t count, size_t size);
void			ft_free_tab(char **strs);
void			*ft_memccpy(void *dst, const void *src, int c,
					size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memset(void *b, int c, size_t len);

/*
**				PRINT
*/

void			ft_lstprint(t_list *lst);
void			ft_print_tab(char **strs);
void			ft_putchar(char c);
void			ft_putendl(char *s);
void			ft_putnbr(int n);
void			ft_putstr(char *s);

void			ft_lstprint_fd(t_list *lst, int fd);
void			ft_print_tab_fd(char **strs, int fd);
void			ft_putchar_fd(char c, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_putstr_fd(char *s, int fd);

/*
**				STRS
*/

char			**ft_sort_strs(char **strs);
void			ft_sort_strs_to(char ***strs);
char			**ft_split(char const *s, char c);
char			*ft_strchr(const char *s, int c);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strdup(const char *s1);
int				ft_strisint(char *str);
char			*ft_strjoin(char const *s1, char const *s2);
void			ft_strjoin_to(char **dest, char *s2);
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);
int				ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t			ft_strlen(const char *s);
char			*ft_strmapi(char const *s,
					char (*f)(unsigned int, char));
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strndup(char *str, int start, int len);
char			*ft_strnstr(const char *haystack, const char *needle,
					size_t len);
char			*ft_strrchr(const char *s, int c);
char			*ft_substr(char const *s,
					unsigned int start, size_t len);
char			**ft_strs_to_tab(int n, ...);
char			*ft_strtrim(char const *s1, char const *set);
char			**ft_tabrmi(char **strs, int index);
int				ft_strtrunc(char **line, int n);
char			**ft_tabjoin(char **s1, char **s2);
int				ft_tablen(char **strs);
char			**ft_tabcpy(char **strs);

#endif
