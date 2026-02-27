/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nehuen <nehuen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 15:39:31 by nehuen            #+#    #+#             */
/*   Updated: 2026/02/24 15:39:32 by nehuen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINISHELL_H
#define MINISHELL_H

#include <unistd.h>
#include <stdlib.h>


typedef struct s_env
{
    char            *name;
    char            *value;
    struct s_env    *next;
}   t_env;

typedef struct s_token
{
    char            *name;
    char            *value;
    struct s_token    *next;
}   t_token;

typedef struct s_dir
{
    char            *name;
    char            *value;
    struct s_dir    *next;
}   t_dir;

typedef struct s_cmd
{
    char            *name;
    char            *value;
    struct s_cmd    *next;
}   t_cmd;

int ft_skip_quote(char *str, int i);
int ft_op_valid(char *str, int i);
int	ft_syntaxe_op(char *str, int i);
int	ft_ispace(int s);
int word_is_ok(char c);

/*
structure a ajouter pour : 

tokens

redirections

commandes*/

#endif