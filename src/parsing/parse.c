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

int	parse_precheck(char *line)
{
    if (!ft_check_quote(line, NULL))
    {
        error("quote not closed");
        return (1);
    }
    if (!ft_syntax_error(line))
    {
        error("syntax error");
        return (1);
    }
    return (0);
}

int	parse_tokenize(char *line, t_token **tokens)
{
    *tokens = parse_principal(line);
    if (!*tokens && line && line[0])
    {
        error("tokenization failed");
        return (1);
    }
    return (0);
}

int	parse_build_cmds(t_token *tokens, t_cmd **cmd)
{
    *cmd = ft_build_command(tokens);
    if (!*cmd && tokens)
        return (1);
    return (0);
}

int appel_parse(char *line, t_cmd **cmd)
{
    t_token	*tokens;

    if (!cmd)
        return (1);
    *cmd = NULL;
    if (!line || !line[0])
        return (0);
    if (parse_precheck(line))
        return (1);
    if (parse_tokenize(line, &tokens))
        return (1);
    if (parse_build_cmds(tokens, cmd))
        return (free_tokens(tokens), 1);
    free_tokens(tokens);
    return (0);
}
