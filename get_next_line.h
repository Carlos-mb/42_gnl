#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	char			text [BUFFER_SIZE + 1];
	size_t			pos;
	struct s_list	*next;		
}					t_list_gnl;

char	*get_next_line(int fd);


#endif