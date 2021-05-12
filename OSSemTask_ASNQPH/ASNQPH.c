#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<time.h>
#include<sys/sem.h>

int main()
{
    int id; /* Szemafor azonosító */
    int KEY=0,PERM=0;
    struct sembuf up[1] = {0,1, SEM_UNDO};
    struct sembuf down[1] = {0,-1, SEM_UNDO};
    pid_t pid= getpid();
    char szoveg[42];

    if((id = semget(KEY,1,0)) < 0 )
    {
        if((id = semget(KEY,0,PERM | IPC_CREAT)) < 0)
        {
            perror("A szemafor nem nyitható meg. ");
            exit(-1);
        }
    }
    else
    {
        perror("Mar letezik a szemafor. ");
    }
    if(semctl(id,0,SETVAL, 1) < 0)
    {
        puts("Kesz es inicializalva van a szemafor.");
    }
    else
    {
        perror("Nem lehet inicializalni. ");

    }

    semop(id, down,1); /* A belépési szakasz */

    sprintf(szoveg, " Itt fut a kritikus szakasz. (%d B", pid);
    puts(szoveg);

    FILE* fp;
    fp = fopen("beadando.txt", "wt");
    if (fp != NULL) {

        fprintf(fp, "%d",167);
        sleep(3);
        fclose(fp);

    }
    else {
        perror("Nem sikerült megnyitni a fajlt!");
        }

    semop(id,up,1); /*Ez a kilépési szakasz */

    if((id = semget(KEY,1,0)) < 0)
    {
        perror("Mar nem létezik a szemafor. ");
        exit(-1);
    }

    if(semctl(id,0,IPC_RMID,0) < 0)
    {
        perror("Nem sikerult torolni a szemafort. ");
        exit(-1);
    }

    puts(" A  szemafort megszuntettuk. ");
    exit(0);

}

