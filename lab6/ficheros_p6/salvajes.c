#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include "common.h"

#define NUMITER 3

sem_t *mutex = sem_open(MUTEX_NAME,0);

int getServingsFromPot(void) {


}

void eat(void) {

	unsigned long id = (unsigned long) getpid();
	printf("Savage %lu eating\n", id);
	sleep(rand() % 5);
}

void savages(void) {

}

int main(int argc, char *argv[])
{

	return 0;
}
