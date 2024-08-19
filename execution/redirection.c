/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkaoukin <mkaoukin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:33:16 by mkaoukin          #+#    #+#             */
/*   Updated: 2024/08/18 19:23:55 by mkaoukin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ex_minishell.h"

void	check_ambiguous_ch(t_m_list *lst, t_fd *fd, int i, int l)
{
	int	j;

	j = -1;
	if (l != 2)
		close (fd->id2);
	else
		close (fd->id3);
	while (lst->file[i][++j])
	{
		if (lst->file[i][j] == '$' && lst->file[i][j + 1] != '\0'
			&& ft_strcmp(lst->d_h[i], ">>)") && ft_strcmp(lst->d_h[i], ">)"))
			ft_exit(1, lst->file[i], "ambiguous redirect\n", NULL);
	}
	if (l == 0)
		fd->id2 = open(lst->file[i], O_CREAT | O_WRONLY | O_APPEND, 0777);
	else if (l == 1)
		fd->id2 = open(lst->file[i], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	else
		fd->id3 = open(lst->file[i], O_RDONLY, 0777);
}

void	ft_redirection_ch(t_m_list *lst, t_fd *fd, int i)
{
	while (lst->d_h[++i])
	{
		if (lst->d_h[i][0] == '>' && lst->d_h[i][1] == '>')
			check_ambiguous_ch(lst, fd, i, 0);
		else if (lst->d_h[i][0] == '<' && lst->d_h[i][1] == '<')
			fd->id3 = lst->r_h;
		else if (lst->d_h[i][0] == '<')
			check_ambiguous_ch(lst, fd, i, 2);
		else
			check_ambiguous_ch(lst, fd, i, 1);
		if (fd->id2 == -1 || fd->id3 == -1)
		{
			if (access(lst->file[i], F_OK) == 0)
				ft_exit(1, lst->file[i], "Permission denied\n", NULL);
			ft_exit(1, lst->file[i], "No such file or directory\n", NULL);
		}
	}
}

void	check_ambiguous_par(t_m_list *lst, t_fd *fd, int i, int l)
{
	int	j;

	j = -1;
	if (l != 2)
		close (fd->id2);
	else
		close (fd->id3);
	while (lst->file[i][++j])
	{
		if (lst->file[i][j] == '$' && lst->file[i][j + 1] != '\0'
			&& ft_strcmp(lst->d_h[i], ">>)") && ft_strcmp(lst->d_h[i], ">)"))
		{
			fd->id3 = -5;
			fd->ex_c = 1;
			printf ("minishell: %s: ambiguous redirect\n", lst->file[i]);
			return ;
		}
	}
	if (l == 0)
		fd->id2 = open(lst->file[i], O_CREAT | O_WRONLY | O_APPEND, 0777);
	else if (l == 1)
		fd->id2 = open(lst->file[i], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	else
		fd->id3 = open(lst->file[i], O_RDONLY, 0777);
}

void	ft_redirection_par(t_m_list *lst, t_fd *fd, int i)
{
	while (lst->d_h[++i])
	{
		if (lst->d_h[i][0] == '>' && lst->d_h[i][1] == '>')
			check_ambiguous_par(lst, fd, i, 0);
		else if (lst->d_h[i][0] == '<' && lst->d_h[i][1] == '<')
			fd->id3 = lst->r_h;
		else if (lst->d_h[i][0] == '<')
			check_ambiguous_par(lst, fd, i, 2);
		else
			check_ambiguous_par(lst, fd, i, 1);
		if (fd->id2 == -1 || fd->id3 == -1)
		{
			fd->ex_c = 1;
			if (access(lst->file[i], F_OK) == 0)
			{
				printf ("minishell: %s: Permission denied\n", lst->file[i]);
				break ;
			}
			printf ("minishell: %s: No such file or directory\n", lst->file[i]);
			break ;
		}
	}
}

void	ft_redirection(t_m_list *lst, t_fd *fd, int i)
{
	fd->id = 1;
	fd->id2 = -2;
	fd->id3 = -2;
	if (i == 0)
		ft_redirection_ch(lst, fd, -1);
	else
		ft_redirection_par(lst, fd, -1);
	if (fd->id2 != -2)
	{
		fd->id = 0;
		dup2(fd->id2, STDOUT_FILENO);
		close(fd->id2);
	}
	if (fd->id3 != -2)
	{
		dup2(fd->id3, STDIN_FILENO);
		close(fd->id3);
	}
}
