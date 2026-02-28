#include "minishell.h"

int ft_check_debut_fin(char *line)
{
    int i = 0;

    if (!line || !line[0])
        return 0; 
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;

    if (line[i] == '|')
        return 0; 
    int j = 0;
    while (line[j])
        j++;
    j--;
    while (j >= 0 && (line[j] == ' ' || line[j] == '\t'))
        j--;

    if (j >= 0 && line[j] == '|')
        return 0; 

    return 1; 
}

int ft_check_pipe(char *line)
{
    int i = 0;

    while (line[i])
    {
        if (line[i] == '|')
        {
            int j = i + 1;
            while (line[j] && ft_ispace(line[j]))
                j++;
            if (line[j] == '|')
                return 0; 
        }
        i++;
    }
    return 1;
}

int ft_check_redirection(char *line)
{
    int i = 0;
    while(line[i])
    {
        if (line[i] == '<' || line[i] == '>')
        {
            int j = i + 1;
            if ((line[i] == '<' && line[j] && line[j] == '<') ||
                (line[i] == '>' && line[j] && line[j] == '>'))
                j++;
            while(line[j] && ft_ispace(line[j]))
                j++;
            if (!line[j] || !word_is_ok(line[j]))
                return 0;

            i = j - 1; 
        }
        i++;
    }
    return 1;
}

int ft_syntax_error(char *line)
{
    if (!ft_check_debut_fin(line))
        return 0;
    if (!ft_check_redirection(line))
        return 0;
    if(!ft_check_pipe(line))
        return 0;
    return 1; // syntaxe ok
}
