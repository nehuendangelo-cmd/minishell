#include "minishell.h"

int ft_is_op(char c)
{
    return (c == '|' || c == '<' || c == '>');
}

void ft_add_word_quote_token(t_token **head, char *line, int *i)
{
    int start = *i;
    int len = 0;
    char quote;
    t_token *token;

    quote = line[*i];
    (*i)++;
    start = *i;
    
    while (line[*i] && line[*i] != quote)
    {
        (*i)++;
        len++;
    }
    
    if (line[*i] == quote)
        (*i)++;

    token = malloc(sizeof(t_token));
    if (!token)
        return;
    
    token->next = NULL;
    token->type = WORD;
    token->quote_type = (quote == '\'') ? SINGLE_QUOTE : DUBBLE_QUOTE;
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

void free_tab(char **tab)
{
    int i;

    if (!tab)
        return;
    i = 0;
    while (tab[i])
    {
        free(tab[i]);
        i++;
    }
    free(tab);
}

void free_redirs(t_redir *redir)
{
    t_redir *tmp;

    while (redir)
    {
        tmp = redir->next;
        free(redir->file);
        free(redir);
        redir = tmp;
    }
}

char *ft_strcpy(char *dest, const char *src)
{
    int i;

    i = 0;
    while (src[i])
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return (dest);
}

t_cmd *error(char *msg)
{
    write(2, "Error: ", 7);
    write(2, msg, ft_strlen(msg));
    write(2, "\n", 1);
    return (NULL);
}
