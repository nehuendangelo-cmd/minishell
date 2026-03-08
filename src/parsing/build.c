#include "minishell.h"

 static t_redir_type token_to_redir(int token_type)
  {
    if (token_type == TOK_REDIR_IN)
        return (REDIR_IN);
    else if (token_type == TOK_REDIR_OUT)
        return (REDIR_OUT);
    else if (token_type == TOK_APPEND)     
        return (REDIR_APPEND);
    else if(token_type == TOK_HEREDOC)
        return (REDIR_HEREDOC); 
  }
t_cmd *new_cmd(void)
{
    t_cmd *cmd;

    cmd = malloc(sizeof(t_cmd));
    if (!cmd)
        return NULL;
    cmd->cmd_and_args = NULL;
    cmd->redirs = NULL;
    cmd->next = NULL;
    return cmd;
}

void ft_add_arg(t_cmd *cmd, char *word)
{
    int i;
    char **new;

    i = 0;
    while (cmd->cmd_and_args && cmd->cmd_and_args[i])
        i++;

    new = malloc(sizeof(char *) * (i + 2));
    if (!new)
        return;

    i = 0;
    while (cmd->cmd_and_args && cmd->cmd_and_args[i])
    {
        new[i] = cmd->cmd_and_args[i];
        i++;
    }
    new[i] = ft_strdup(word);
    new[i + 1] = NULL;

    free(cmd->cmd_and_args);
    cmd->cmd_and_args = new;
}

void ft_add_redir(t_cmd *cmd, int type, char *file)
{
    t_redir *new;
    t_redir *tmp;

    new = malloc(sizeof(t_redir));
    new->type = type;
    new->file = ft_strdup(file);
    new->next = NULL;

    if (!cmd->redirs)
        cmd->redirs = new;
    else
    {
        tmp = cmd->redirs;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new;
    }
}

t_cmd *ft_build_command(t_token *tokens)
{
    t_cmd *head;
    t_cmd *current;

    head = new_cmd();
    current = head;
    while (tokens)
    {
        if (tokens->type == WORD)
            ft_add_arg(current, tokens->value);
        else if (is_redirection(tokens->type))
        {
            if (!tokens->next || tokens->next->type != WORD)
                return (error("missing filename"));
            token->type = token_to_redir(token->type);
            ft_add_redir(current, tokens->type, tokens->next->value);
            tokens = tokens->next; 
        }
        else if (tokens->type == PIPE)
        {
            current->next = new_cmd();
            current = current->next;
        }
        tokens = tokens->next;
    }
    return head;
}
