#include <stdio.h>
#include <stdlib.h>

int main()
{


    FILE* fp;
    fp = fopen("beadando.txt", "r");
    char line[101];
    while(!feof(fp))
    {
        fgets(line,100,fp);
        puts(line);
    }
    fclose(fp);

    return 0;
}
