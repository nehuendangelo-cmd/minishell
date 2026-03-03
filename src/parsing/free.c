#include "minishell.h"

void free_cmds(t_cmd *cmd)
{
    t_cmd *tmp;

    while (cmd)
    {
        tmp = cmd->next;
        free_tab(cmd->cmd_and_args);
        free_redirs(cmd->redirs);
        free(cmd);
        cmd = tmp;
    }
}

void free_tokens(t_token *t)
{
    t_token *tmp;
    while (t)
    {
        tmp = t->next;
        free(t->value);
        free(t);
        t = tmp;
    }
}





