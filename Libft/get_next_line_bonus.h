/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablogon <pablogon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 23:33:36 by pablogon          #+#    #+#             */
/*   Updated: 2025/01/23 19:04:50 by pablogon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10000
# endif

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>

char			*ftg_strjoin(const char *str1, const char *str2);
size_t			ftg_strlen(const char *s);
char			*ftg_strdup(const char *s1);
char			*ftg_substr(const char *s, unsigned int start, size_t len);
char			*ft_readifdonthavenewline(char *storage, int fd);
int				ft_searchnewline(char *str);
char			*get_next_line(int fd);
char			*ft_freestorage(char **storage);

#endif 