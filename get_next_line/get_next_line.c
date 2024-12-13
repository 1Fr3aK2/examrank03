#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

char	*free_gnl(char *gnl)
{
	if (gnl)
		free(gnl);
	return (NULL);
}
size_t	ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	if (!s1)
		return (NULL);
	if (!s2)
		return (free_gnl(s1));
	i = -1;
	j = 0;
	str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (free_gnl(s1));
	while (s1[++i])
		str[i] = s1[i];
	while (s2[j] && s2[j] != '\n')
		str[i++] = s2[j++];
	if (s2[j] == '\n')
		str[i++] = s2[j];
	str[i] = '\0';
	if (s1)
		free(s1);
	return (str);
}

int	check_and_clear(char *line)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	j = 0;
	flag = 0;
	if (!line)
		return (0);
	while (line[i])
	{
		if (flag == 1)
			line[j++] = line[i];
		if (line[i] == '\n')
			flag = 1;
		line[i++] = '\0';
	}
	return (flag);
}


char	*get_next_line(int fd)
{
	static char	line[BUFFER_SIZE + 1];
	char		*gnl;
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	gnl = malloc(1 * sizeof(char));
	if (!gnl)
		return (NULL);
	gnl[0] = '\0';
	gnl = ft_strjoin(gnl, line);
	if (check_and_clear(line) == 1)
		return (gnl);
	bytes_read = read(fd, line, BUFFER_SIZE);
	if (bytes_read <= 0 && (!*gnl))
		return (free_gnl(gnl));
	while (bytes_read > 0)
	{
		line[bytes_read] = '\0';
		gnl = ft_strjoin(gnl, line);
		if (check_and_clear(line) == 1)
			break ;
		bytes_read = read(fd, line, BUFFER_SIZE);
	}
	return (gnl);
}