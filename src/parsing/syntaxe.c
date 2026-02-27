#include "minishell.h"

int ft_syntax_error(char *line)
{
    int i = 0;

    if (!line || !line[0])
        return 1; 
    while (line[i] && (line[i] == ' ' || line[i] == '\t'))
        i++;
    if (line[i] == '|')
        return 0; 
    i = 0;
    while (line[i])
    {
        if (line[i] == '|' && line[i + 1] == '|')
            return 0;
        if ((line[i] == '<' || line[i] == '>'))
        {
            int j = i + 1;
            if ((line[i] == '<' && line[i + 1] == '<') || 
                (line[i] == '>' && line[i + 1] == '>'))
                j++;
            while (line[j] && (line[j] == ' ' || line[j] == '\t'))
                j++;

            if (!is_word_ok(line[j]))
                return 0; 
        }
        i++;
    }
    i = 0;
    while (line[i])
        i++;
    i--;
    while (i >= 0 && (line[i] == ' ' || line[i] == '\t'))
        i--;
    if (line[i] == '|')
        return 0; 
    return 1; 
}
