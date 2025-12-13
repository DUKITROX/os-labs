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

void handler(int signo) {
	printf("Señal recibida %d. \n ", signo); 
	finish= 1; 
}


void cocina(int* raciones, sem_t* cocinero, sem_t* salvajes){
   while(!finish){
	if(sem_wait(cocinero)== -1){ //si no hay una señal, espera no activa. Si hay señal, devuelve -1, se ha recibido el handler
		perror("Error al hacer el wait del cocinero"); 
		return; 
	}
	printf("El cocinero repone %d raciones.\n",M);
	*raciones +=M;
	sem_post(salvajes);
   }
}



int main(int argc, char *argv[])
{
	//configuración de la señal 
	struct sigaction act; 
	act.sa_handler = handler; 
	sigemptyset(&act.sa_mask); 
	sigaddset(&act.sa_mask, SIGTERM); 
	sigaddset(&act.sa_mask, SIGINT); 
	act.sa_flags = 0; //se pone a 0 para que dé error, si se pusiera sa_restart se reiniciarían los semáforos, y putada 
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

