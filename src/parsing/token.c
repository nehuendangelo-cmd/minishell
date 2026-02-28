#include "minishell.h"

void ft_add_op_token(t_token **head, char *line, int *i)
{
    if (line[*i] && line[*i + 1] && 
       ((line[*i] == '<' && line[*i + 1] == '<') ||
        (line[*i] == '>' && line[*i + 1] == '>')))
        ft_add_double_op_token(head, line, i);
    else
        ft_add_single_op_token(head, line, i);
}

void ft_add_double_op_token(t_token **head, char *line, int *i)
{
    t_token *token = malloc(sizeof(t_token));
    if (!token)
        return;

    token->next = NULL;

    if (line[*i] == '<' && line[*i + 1] == '<')
    {
        token->type = HEREDOC;
        token->value = ft_strdup("<<");
        *i += 2;
    }
    else if (line[*i] == '>' && line[*i + 1] == '>')
    {
        token->type = APPEND;
        token->value = ft_strdup(">>");
        *i += 2;
    }
    else
    {
        token->type = WORD; 
        token->value = ft_strdup(""); 
    }
    ft_lstadd_back(head, token);
}

void ft_add_single_op_token(t_token **head, char *line, int *i)
{
    t_token *token = malloc(sizeof(t_token));
    if (!token)
        return;

    token->next = NULL;

    char c;
    c = line[*i];
    if (c == '|')
        token->type = PIPE;
    else if (c == '<')
        token->type = REDIR_IN;
    else if (c == '>')
        token->type = REDIR_OUT;

    token->value = malloc(2);
    token->value[0] = c;
    token->value[1] = '\0';

    (*i)++;
    ft_lstadd_back(head, token);
}

void ft_add_word_token(t_token **head, char *line, int *i)
{
    int start = *i;
    int len = 0;
    t_token *token;

    while (line[*i] && !ft_ispace(line[*i]) && !ft_is_op(line[*i]))
    {
        (*i)++;
        len++;
    }

    token = malloc(sizeof(t_token));
    if (!token)
        return;
    token->next = NULL;
    token->type = WORD;

    char buffer[len + 1];
    ft_strncpy(buffer, &line[start], len);
    buffer[len] = '\0';
    token->value = ft_strdup(buffer);

    ft_lstadd_back(head, token);
}



 