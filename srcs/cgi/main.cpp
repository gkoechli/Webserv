#include "cgi.hpp"
#include <stdio.h>
#include <unistd.h>




int main(int ac, char **av, char **env)
{
	cgi test("ls");
	return (0);
}