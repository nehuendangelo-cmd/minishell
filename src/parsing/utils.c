#include "minishell.h"

int is_redirection(int type)
{
    if (type == TOK_REDIR_IN
        || type == TOK_REDIR_OUT
        || type == TOK_APPEND
        || type == TOK_HEREDOC)
        return (1);
    return (0);
}
//avant : t_env *env, 
//apres : char **envp
//cela me permet de recuperer envp en tableau de char pour execve
char *expand_variable(char *str, int *i, char **envp, int last_status)
{
    char *tmp;
    char *var;
    int start;

    (*i)++;
    if (str[*i] == '?')
        return (tmp = ft_itoa(last_status), (*i)++, tmp);
    if (str[*i] == '$')
        return (tmp = ft_itoa(getpid()), (*i)++, tmp);
    if (!ft_isalnum(str[*i]) && str[*i] != '_')
        return (ft_strdup("$"));
    start = *i;
    while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
        (*i)++;
    var = ft_substr(str, start, *i - start);
    tmp = ft_get_env_value(envp, var);
    free(var);
    return (tmp ? ft_strdup(tmp) : ft_strdup(""));
}
char *ft_expand_word(char *str, char **envp, int last_status)
{
    int i;
    char *res;
    char *tmp;

    i = 0;
    res = ft_strdup("");
    while (str[i])
    {
        if (str[i] == '$')
        {
            tmp = expand_variable(str, &i, envp, last_status);
            res = ft_strjoin_free(res, tmp);
            free(tmp);
        }
        else
            res = ft_charjoin(res, str[i++]);
    }
    return res;
}
// fonction get_env_value qui parcourt envp en mode tableau
// recupere la valeur de la variable 
char    *ft_get_env_value(char **envp, char *name)
{

    int        i;

    i = 0;
    while (envp[i])
    {
        if (envp[i] && ft_strncmp(name, envp[i], ft_strlen(name)) == 0
                && envp[i][ft_strlen(name)] == '=')
            return (&envp[i][ft_strlen(name) + 1]);
        i++;
    }
    return (NULL);
}
char *ft_strjoin_free(char *s1, char *s2)
{
    char *res = ft_strjoin(s1, s2);
    free(s1);
    return res;
}
char *ft_charjoin(char *s, char c)
{
    char *res;
    int len = ft_strlen(s);

    res = malloc(len + 2);
    ft_strcpy(res, s);
    res[len] = c;
    res[len + 1] = '\0';
    free(s);
    return res;
}

int is_redirection_prev(t_token *token)
{
    if (!token || !token->prev)
        return (0);
    if (token->prev->type == TOK_REDIR_IN
        || token->prev->type == TOK_REDIR_OUT
        || token->prev->type == TOK_APPEND
        || token->prev->type == TOK_HEREDOC)
        return (1);
    return (0);
}