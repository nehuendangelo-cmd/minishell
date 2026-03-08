#include "minishell.h"

t_token *parse_principal(char *line)
{
    int i = 0;
    t_token *token = NULL;

    while (line[i])
    {
        if (ft_ispace(line[i]))
        {
            i++;
            continue;
        }
        if (ft_is_op(line[i]))
            ft_add_op_token(&token, line, &i);
        else if (ft_check_quote(line,&i))
            ft_add_word_quote_token(&token, line, &i);
        else
            ft_add_word_token(&token, line, &i);
    }
    return token;
}
