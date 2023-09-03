#include "cgi.hpp"
int ft_strlen(char *str)
{
	int i;

	i = 0;
	if (!str)
		return 0;
	while (str[i])
		i++;
	return (i);
}

char * ft_strdup(char *str)
{
	int i;
	int max;
	char *ret;

	i = 0;
	if (!str)
		return NULL;
	max = ft_strlen(str);
	ret = (char *)malloc(sizeof(char) * (max + 1));
	while (i < max)
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

cgi::cgi(std::string obj):fct(obj)
{
	this->path = "/bin/" + this->fct;
	std::cout << getFunction() << "   " << getPath() << std::endl;
	char **str;
	int n;
	int i;

	n = 1;
	i = 0;
	str = (char **)malloc(sizeof(char *) * (n + 1));
	str[n] = NULL;
	while (i < n)
	{
		str[i] = ft_strdup(this->getFunctionInChar());
		printf("str[%d] = %s\n", i, str[i]);
		i++;
	}
	int pip[2];
	pipe(pip);

	pid_t pid = fork();
	if (pid == 0)
	{
		close(pip[1]);
		std::cout << this->getPathInChar() << std::endl;
		execve(this->getPathInChar(), str, NULL);
	}
	else
	{
		close(pip[0]);
		close(pip[1]);
	}
	for (int x = 0; x < n; x++)
	{
		free (str[x]);
	}
	free (str);
}

cgi::~cgi()
{

}

std::string	cgi::getFunction()
{
	return (this->fct);
}

std::string	cgi::getPath()
{
	return (this->path);
}

char *cgi::getFunctionInChar()
{
	return ((char *)this->fct.c_str());
}

char *cgi::getPathInChar()
{
	return ((char *)this->path.c_str());
}