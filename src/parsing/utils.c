#include "minishell.h"

int is_redirection(int type)
{
    if (type == REDIR_IN
        || type == REDIR_OUT
        || type == APPEND
        || type == HEREDOC)
        return (1);
    return (0);
}

char *expand_variable(char *str, int *i, t_env *env, int last_status)
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
    tmp = ft_get_env_value(env, var);
    free(var);
    return (tmp ? ft_strdup(tmp) : ft_strdup(""));
}
char *ft_expand_word(char *str, t_env *env, int last_status)
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
            tmp = expand_variable(str, &i, env, last_status);
            res = ft_strjoin_free(res, tmp);
            free(tmp);
        }
        else
            res = ft_charjoin(res, str[i++]);
    }
    return res;
}


char *ft_get_env_value(t_env *env, char *name)
{
    while (env)
    {
        if (ft_strncmp(env->name, name, ft_strlen(name)) == 0 
            && env->name[ft_strlen(name)] == '\0')
            return env->value;
        env = env->next;
    }
    return NULL;
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
    if (token->prev->type == REDIR_IN
        || token->prev->type == REDIR_OUT
        || token->prev->type == APPEND
        || token->prev->type == HEREDOC)
        return (1);
    return (0);
}