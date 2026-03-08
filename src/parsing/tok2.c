#include "minishell.h"

void ft_expand_tokens(t_token *tokens, char **envp, int last_status)
{
    char *expanded;

    while (tokens)
    {
        if (tokens->type == WORD
            && tokens->quote_type != SINGLE_QUOTE
            && !(tokens->prev && tokens->prev->type == TOK_HEREDOC
                 && tokens->quote_type == DUBBLE_QUOTE))
        {
            expanded = ft_expand_word(tokens->value, envp, last_status);
            free(tokens->value);
            tokens->value = expanded;
        }
        tokens = tokens->next;
    }
}
