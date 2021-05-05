#include <stdio.h>
#include <stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<time.h>
#include<pthread.h>
#include<semaphore.h>

sem_t sem;
void * fajlbairas ()
{
    FILE* fp;
    fp = fopen("beadando.txt", "wt");
    if (fp != NULL) {

        fprintf(fp, "%d",167);
        sleep(3);
        fclose(fp);
        sem_post(&sem);

    }
    else {
        perror("Nem siker�lt megnyitni a fajlt!");
    }
}

int main()
{

    sem_init(&sem,1,0);
    pthread_t thread1;
    pthread_create(&thread1,NULL,fajlbairas(), NULL);
    pthread_join(&thread1,NULL);
    printf("A f�jlba �r�s sikeres volt!");


    sem_destroy(&sem);


    return 0;
}

