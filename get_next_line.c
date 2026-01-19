#include "get_next_line.h"

char	ft_read_char(int fd, char *buffer)
{
	char	output;
	ssize_t	bytes_read;
	size_t	i;

	if (buffer[0] == '\0')
	{
		bytes_read = read (fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			buffer[0] = '\0';
		else
			buffer[bytes_read] = '\0';
	}
	output = buffer[0];
	if (buffer[0] != '\0')
	{
		i = 0;
		while (buffer[i] != '\0')
		{
			buffer[i] = buffer [i + 1];
			i++;
		}
	}
	return (output);
}

t_list_gnl	*ft_lst_new(void)
{
	t_list_gnl	*output;

	output = malloc(sizeof(t_list_gnl));
	if (!(output))
		return (NULL);
	output->text[0] = '\0';
	output->pos = 0;
	output->next = NULL;
	return (output);
}

void	ft_add_char(char c_read, t_list_gnl **p_current_text)
{
	t_list_gnl	*new_text;

	if ((*p_current_text)->pos == BUFFER_SIZE)
	{
		new_text = ft_lst_new();
		if (!new_text)
			return ;
		(*p_current_text)->next = new_text;
		(*p_current_text) = new_text;
	}
	(*p_current_text)->text[(*p_current_text)->pos] = c_read;
	(*p_current_text)->text[((*p_current_text)->pos) + 1] = '\0';
	(*p_current_text)->pos += 1;
	(*p_current_text)->next = NULL;
}

void	ft_lst_clear(t_list_gnl *lst)
{
	void	*tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst);
		lst = tmp;
	}
}

static int	ft_getsize (t_list_gnl *current)
{
	size_t	i;

	i = 0;
	while (current && current->text[0] != '\0')
	{
		i += current->pos;
		current = (current)->next;
	}
	return (i);
}
char	*ft_create_output(t_list_gnl *out_list)
{
	size_t		i;
	size_t		j;
	t_list_gnl	*current;
	char		*output;

	i = ft_getsize(out_list);
	if (i > 0)
	{
		output = malloc ((sizeof(char *) * i) + 1);
		i = 0;
		current = out_list;
		while (output && current)
		{
			j = 0;
			while ((current->text)[j])
				output [i++] = (current->text)[j++];
			output[i] = '\0';
			current = (current)->next;
		}
	}
	else
		output = NULL;
	ft_lst_clear(out_list);
	return (output);
}

char	*get_next_line(int fd)
{
	char		c_read;
	static char	buffer [BUFFER_SIZE + 1];
	t_list_gnl	*out_list;
	t_list_gnl	*current_text;

	if (fd <= 0)
		return (NULL);
	out_list = ft_lst_new ();
	if (!out_list)
		return (NULL);
	current_text = out_list;
	c_read = ' ';
	while (c_read != '\n' && c_read != '\0' && current_text != NULL)
	{
		c_read = ft_read_char(fd, buffer);
		ft_add_char(c_read, &current_text);
	}
	return (ft_create_output(out_list));
}
/*
#include <stdio.h>
#include <fcntl.h>

int printa (int f)
{
	char	*c;

	c = get_next_line(f);
	if (c)
		printf(c);
	else
		printf("**NULL**");
	free(c);
	return (c != NULL);
}

int main (int argn, char **argv)
{
	int 	f;

	// (void) argn;
	// (void) argv;

//	printf("StdIn:\n");
//	while (printa(1));
	while (--argn)
	{
		printf("%s\n", argv[argn]);
		f = open(argv[argn], 0);
		while (printa(f));
		close(f);
		printf("\n");
	}

	return (1);
}
	*/
	/*
	f = open("prueba_fin_EOF.txt", 0);	
	while (printa(f));
	close(f);
	printf("\n-----\n");
	f = open("prueba_fin_null.txt", 0);	
	while (printa(f));
	close(f);

	return (1);
}
*/