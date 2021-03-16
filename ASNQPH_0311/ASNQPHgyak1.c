
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int	status;

    printf("\n\n");

	if ( (status = system("date")) < 0)
		perror("system() error");

	if (WIFEXITED(status))
		printf("Az első eset normális befejeződés, visszaadott érték = %d\n", WEXITSTATUS(status));


    if ( (status = system("alma")) < 0)
		perror("system() error");

	if (WIFEXITED(status))
		printf("A második eset nem normális befejeződés, visszaadott érték = %d\n", WEXITSTATUS(status));

    printf("\n\n");

	exit(0);
}
