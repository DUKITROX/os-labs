#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define CAPACITY 5
#define VIPSTR(vip) ((vip) ? "  vip  " : "not vip")

typedef struct{
		int id;
		int isvip;
	} info;

pthread_mutex_t mutexcap;
pthread_cond_t cv;
int inside;
int ticket_vip=0;
int serving_vip=0;
int ticket_normal=0;
int serving_normal=0;


void enter_normal_client(int id) {

	pthread_mutex_lock(&mutexcap);
	int ticket;
	ticket = ticket_normal;
	ticket_normal++;
	
	while (ticket != serving_normal || serving_vip != ticket_vip || inside >= CAPACITY){
		pthread_cond_wait(&cv,&mutexcap);
	}
	inside++;
	serving_normal++;
	//printf("Normal client entering with id %d\n",id);
	pthread_mutex_unlock(&mutexcap);

}

void enter_vip_client(int id) {

	pthread_mutex_lock(&mutexcap);
	int ticket;
	ticket = ticket_vip;
	ticket_vip++;
	
	while (ticket != serving_vip || inside >= CAPACITY){
		pthread_cond_wait(&cv,&mutexcap);
	}
	inside++;
	serving_vip++;
	//printf("Vip client entering with id %d \n",id);
	pthread_mutex_unlock(&mutexcap);


}

void dance(int id, int isvip)
{
	printf("Client %2d (%s) dancing in disco\n", id, VIPSTR(isvip));
	sleep((rand() % 3) + 1);
}

void disco_exit(int id, int isvip) {
	pthread_mutex_lock(&mutexcap);

	inside--;
	pthread_cond_broadcast(&cv);
	pthread_mutex_unlock(&mutexcap);

}

void *client(void *arg) {

	info *a = (info*) arg;
	int id = a->id;
	int isvip= a-> isvip;
	free(a);

	if (isvip){
		enter_vip_client(id);
	}
	else{
		enter_normal_client(id);
	}
	dance(id,isvip);
	disco_exit(id,isvip);

	return NULL;

}



int main(int argc, char *argv[]) {

	
	//getting the member data from the file
	FILE* f;
	int memnum=0;
	pthread_mutex_init(&mutexcap,NULL);
	pthread_cond_init(&cv,NULL);
	
	

	f = fopen(argv[1], "r");
	if (!f){
		printf("Couldnt open file");
		exit(1);
	}
	int fout=0;
	int counter = 0;

	while(fscanf(f,"%d",&fout) != EOF){
		memnum = fout;
		break;
	}

	pthread_t threads[memnum];
	inside = 0;

	while(fscanf(f,"%d",&fout) != EOF){
		info* a = malloc(sizeof(*a));
		a->id = counter;
		a ->isvip = fout;
		pthread_create(&threads[counter],NULL,client,a);
		if (counter == memnum) break;
		counter++;
	
	}


	for (int i=0; i<memnum; i++){

		pthread_join(threads[i],NULL);
	}

	pthread_mutex_destroy(&mutexcap);
	pthread_cond_destroy(&cv);
	

	

	return 0;
}
