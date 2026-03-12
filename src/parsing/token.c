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

t_token *ft_create_double_op_token(char *line, int *i)
{
    t_token *token;

    token = malloc(sizeof(t_token));
    if (!token)
        return (NULL);
    token->next = NULL;
    if (line[*i] == '<' && line[*i + 1] == '<')
    {
        token->type = TOK_HEREDOC;
        token->value = ft_strdup("<<");
        *i += 2;
    }
    else if (line[*i] == '>' && line[*i + 1] == '>')
    {
        token->type = TOK_APPEND;
        token->value = ft_strdup(">>");
        *i += 2;
    }
    return (token);
}

void    ft_add_double_op_token(t_token **head, char *line, int *i)
{
    t_token *token;
    t_token *tmp;

    token = ft_create_double_op_token(line, i);
    if (!token)
        return ;
    if (!*head)
        *head = token;
    else
    {
        tmp = *head;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = token;
    }
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
        token->type = TOK_REDIR_IN;
    else if (c == '>')
        token->type = TOK_REDIR_OUT;
    token->value = malloc(2);
    token->value[0] = c;
    token->value[1] = '\0';
    (*i)++;   
    if (!*head)
        *head = token;
    else
    {
        t_token *tmp = *head;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = token;
    }
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
    token->quote_type = NO_QUOTE;
    token->value = ft_substr(line, start, len);  
    if (!*head)
        *head = token;
    else
    {
        t_token *tmp = *head;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = token;
    }
}



 