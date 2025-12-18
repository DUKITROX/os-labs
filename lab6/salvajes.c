/*
 * Part of the classic dining savages problem.
 * A savage process eats from a shared pot of servings; when the pot is
 * empty it wakes the cook and waits for the cook to refill it. Shared
 * semaphores coordinate access across processes.
 */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>
#include <sys/mman.h>

#define NUMITER 30


void salvaje(int * raciones, sem_t * cocinero, sem_t * salvajes, sem_t* caldero) {
	for(int i = 0; i < NUMITER; ++i) {
		sem_wait(caldero);  /* Take exclusive access to the cauldron. */
		if(*raciones== 0) {

			sem_post(cocinero);  /* Wake the cook to refill. */
			sem_wait(salvajes);  /* Wait until the cook signals servings are ready. */
		}
		int seconds = 1 + rand() % 5 ; 
		printf("Salvaje %lu comiendo durante %d segundos, porciones restantes%d\n", getpid(), seconds, --(*raciones)); 
		sem_post(caldero);  /* Release the pot for another savage. */
		sleep(seconds); //simula cómo el salvaje come 
	}
}

int main(int argc, char *argv[])
{
	int shd = shm_open("/RACIONES", O_RDWR, 0); 
	int * raciones = (int *) mmap (NULL, sizeof(int), PROT_WRITE|PROT_READ, MAP_SHARED, shd, 0); 
	sem_t * cocinero = sem_open("/COCINERO", 0); 
	sem_t* caldero = sem_open("/CALDERO", 0); 
	sem_t * salvajes = sem_open("/SALVAJES",0); 
	salvaje(raciones, cocinero, salvajes,caldero); 
	munmap(raciones, sizeof(int)); 
	close(shd); 
	sem_close(cocinero); 
	sem_close(salvajes); 
	sem_close(caldero); 
	return 0;
}
