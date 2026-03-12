/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nd-angel <nd-angel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 17:20:19 by nehuen            #+#    #+#             */
/*   Updated: 2026/03/12 18:36:37 by nd-angel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_pipes(t_pipe *p, t_cmd *cmd)
{
	p->nb_pids = ft_cmd_count(cmd);
	p->prev_read_pipe = -1;
	p->status = 0;
	p->pids_array = malloc(sizeof(int) * (ft_cmd_count(cmd)));
	if (!p->pids_array)
		exit(EXIT_FAILURE);
}

static void	set_child(t_pipe *p, t_cmd *cmd, t_shell *shell)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = SIG_DFL;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	if (p->prev_read_pipe == -1)
		set_first_child(p, cmd, shell);
	else if (cmd->next)
		set_middle_child(p, cmd, shell);
	else
		set_last_child(p, cmd, shell);
}

static void	wait_all_pids(t_pipe *p, t_shell *shell)
{
	int		i;

	i = 0;
	while (i < p->nb_pids - 1)
	{
		waitpid(p->pids_array[i], &p->status, 0);
		i++;
	}
	waitpid(p->pids_array[i], &p->status, 0);
	if (WIFEXITED(p->status))
		shell->last_exit = WEXITSTATUS(p->status);
	else
		shell->last_exit = 128 + WTERMSIG(p->status);
	free(p->pids_array);
}

void	execute_pipeline(t_cmd *cmd, t_shell *shell)
{
	int					i;
	t_pipe				p;

	init_pipes(&p, cmd);
	i = 0;
	while (cmd)
	{
		if (cmd->next)
			pipe(p.pipe_fd);
		p.pids_array[i] = fork();
		if (p.pids_array[i] == 0)
			set_child(&p, cmd, shell);
		if (cmd->next)
			close(p.pipe_fd[1]);
		if (p.prev_read_pipe != -1)
			close(p.prev_read_pipe);
		if (cmd->next)
			p.prev_read_pipe = p.pipe_fd[0];
		cmd = cmd->next;
		i++;
	}
	wait_all_pids(&p, shell);
}
