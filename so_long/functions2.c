#include "so_long.h"

static char	*ft_join(char *ptr, const char *s1, const char *s2)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	while (s2[y])
	{
		ptr[i + y] = s2[y];
		y++;
	}
	ptr[i + y] = '\0';
	return (ptr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	ptr_len;

	if (!s1 || !s2)
		return (NULL);
	ptr_len = ft_strlen(s1) + ft_strlen(s2);
	ptr = (char *)malloc(ptr_len + 1);
	if (!ptr)
		return (NULL);
	if (ptr_len == 0)
	{
		ptr[0] = '\0';
		return (ptr);
	}
	return (ft_join(ptr, s1, s2));
}

char	*fill_buffer(int fd, char *left, char *buffer)
{
	int		chr_read;
	char	*tmp;

	chr_read = 1;
	while ((chr_read))
	{
		chr_read = read(fd, buffer, BUFFER_SIZE);
		if (chr_read == -1)
		{
			free(left);
			left = NULL;
			break ;
		}
		if (chr_read == 0)
			break ;
		buffer[chr_read] = '\0';
		if (!left)
			left = ft_strdup("");
		tmp = left;
		left = ft_strjoin(tmp, buffer);
		free(tmp);
		if (ft_strchr(left, '\n'))
			break ;
	}
	return (free(buffer), buffer = NULL, left);
}

char	*make_line(char *left, char **line)
{
	int		i;
	char	*tmp;

	i = 0;
	while (left[i] != '\n' && left[i] != '\0')
		i++;
	if (left && left[i] == '\0')
	{
		if (left[0] == '\0')
			*line = NULL;
		else
			*line = ft_strdup(left);
		free(left);
		left = NULL;
	}
	else if (left)
	{
		*line = ft_substr(left, 0, i + 1);
		tmp = left;
		left = ft_substr(left, i + 1, ft_strlen(left) - i);
		free(tmp);
	}
	return (left);
}

char	*get_next_line(int fd)
{
	static char	*left;
	char		*line;
	char		*buffer;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free(left), left = NULL, NULL);
	buffer = (char *)malloc(((size_t)BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	left = fill_buffer(fd, left, buffer);
	if (!left)
		return (NULL);
	left = make_line(left, &line);
	return (line);
}