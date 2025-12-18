/*
 * Cook process for the dining savages problem.
 * Waits on a semaphore from hungry savages, refills the shared pot with M
 * servings stored in shared memory, and signals that food is ready. Handles
 * SIGINT/SIGTERM to exit the loop cleanly and removes IPC resources on exit.
 */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>
#include <sys/mman.h>
#include <signal.h>

#define M 10

int finish = 0;

/* Set a flag so the cook can stop after receiving a termination signal. */
void handler(int signo) {
    printf("Signal received %d.\n", signo);
    finish = 1;
}

void cocina(int* raciones, sem_t* cocinero, sem_t* salvajes){
   while(!finish){
        /* Wait until a savage asks for a refill. */
        if(sem_wait(cocinero)== -1){
            perror("Error al hacer el wait del cocinero");
            return;
        }
        printf("El cocinero repone %d raciones.\n",M);
        *raciones +=M;
        /* Wake the waiting savages so they can start eating. */
        sem_post(salvajes);
   }
}



int main(int argc, char *argv[])
{
    /* Configure signal handling for clean shutdown. */
    struct sigaction act;
    act.sa_handler = handler;
    sigemptyset(&act.sa_mask);
    sigaddset(&act.sa_mask, SIGTERM);
    sigaddset(&act.sa_mask, SIGINT);
    act.sa_flags = 0; //sa_restart disabled so blocking calls can return
    sigaction(SIGTERM, &act,NULL); //SIGTERM es kill -15 pid
    sigaction(SIGINT,&act,NULL);


    int shd = shm_open("/RACIONES", O_CREAT|O_EXCL|O_RDWR,S_IRUSR|S_IWUSR);
    ftruncate(shd,sizeof(int));
    int* raciones= (int*) mmap(NULL, sizeof(int),PROT_WRITE|PROT_READ, MAP_SHARED,shd,0);
    *raciones=M;
    sem_t* cocinero= sem_open("/COCINERO", O_CREAT|O_TRUNC, 0755,0);
    if(cocinero==SEM_FAILED){
       perror("Fallo el semaforo de los cocineros");
       exit(1);
    }
     sem_t* caldero= sem_open("/CALDERO", O_CREAT|O_TRUNC, 0755,1);
     sem_t* salvajes= sem_open("/SALVAJES", O_CREAT|O_TRUNC, 0755,0);

     cocina(raciones,cocinero,salvajes);
     munmap(raciones, sizeof(int));
     close(shd);
     shm_unlink("/RACIONES");
     sem_close(cocinero);
     sem_unlink("/COCINERO");
     sem_close(salvajes);
     sem_unlink("/SALVAJES");
     sem_close(caldero);
     sem_unlink("/CALDERO");
     return 0;
}
