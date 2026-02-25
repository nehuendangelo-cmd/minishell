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

/*
structure a ajouter pour : 

tokens

redirections

commandes*/

#endif