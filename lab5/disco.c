/*
 * Nightclub simulation with VIP priority. Clients take turns based on a
 * ticketing system, enter only when capacity allows, dance for a random
 * duration, and then leave. VIP clients are allowed to jump the queue
 * ahead of normal clients waiting with higher ticket numbers.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define CAPACITY 2
#define N 30
#define VIPSTR(vip) ((vip) ? "  vip  " : "not vip")

typedef struct client_data {
	int id;
	int myturn;
	int is_vip; // 0 normal, 1 vip
} client_t;

int counter = 0;
int counter_vip = 0;
int vip_turn = 0; // "pantalla" de los vip's
int normal_turn = 0; // "pantalla" de los normales
int clients_inside = 0;
int vips_waiting = 0;

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t myturn = PTHREAD_COND_INITIALIZER;

/*
 * Think of this as a deli counter: everyone grabs a ticket and waits for
 * their number on the screen. The screen counters are shared globals and
 * every thread must lock around reads/writes to avoid races.
 */

void arrive_client(client_t* client) {
	pthread_mutex_lock(&m);
	client->myturn = (client->is_vip) ? counter_vip++ : counter++;

	printf("Client %d (%s) recieves his turn (%d)\n", client->id, VIPSTR(client->is_vip), client->myturn);
	fflush(stdout); // flush promptly so interleaved threads are readable

	// while en vez de wait para evitar efectos de carrera
	if(client->is_vip){
		// Could be == CAPACITY; <= is slightly cheaper and equivalent here.
		vips_waiting++;
		while((client->myturn != vip_turn) || (clients_inside >= CAPACITY)) { 
			// VIPs wait for their ticket and capacity, then cut ahead of normals.
			pthread_cond_wait(&myturn , &m);
		}
	}
	else{
		while(vips_waiting || (client->myturn != normal_turn) || (clients_inside >= CAPACITY)) {
			pthread_cond_wait(&myturn, &m);
		}
	}

	pthread_mutex_unlock(&m);
}

void enter_and_dance(client_t* client) {
	pthread_mutex_lock(&m);

	clients_inside++;
	if(client->is_vip) {
		vips_waiting--; // decrement VIP queue once admitted
		vip_turn++;
	}
	else{
		normal_turn++;
	}
	int seconds = rand()%6 + 3; // [3,9) segundos bailados

	printf("Client %d (%s) is inside and is dancing for %d seconds.\n", client->id, VIPSTR(client->is_vip), seconds);
	fflush(stdout); // flush promptly so prints from all threads are visible
	pthread_cond_broadcast(&myturn); // wake everyone so the next eligible client can enter
	pthread_mutex_unlock(&m);
	sleep(seconds); // simulate dancing concurrently
}

void exit_client(client_t* client) {
	pthread_mutex_lock(&m);
	clients_inside--;
	printf("Client %d (%s) leaves the local.\n", client->id, VIPSTR(client->is_vip));
	fflush(stdout);
	pthread_cond_broadcast(&myturn); // notify others that a spot freed up
	pthread_mutex_unlock(&m);
}

void *client(void *arg) {
	client_t* client = (client_t*) arg;

	arrive_client(client);
	enter_and_dance(client);
	exit_client(client);

	return NULL;
}

int main(int argc, char *argv[])
{
	int n = 0;
	pthread_t th_clients[N];
	client_t clients[N];

	FILE *file = fopen("ejemplo.txt", "r");
	fscanf(file, " %d", &n);
	n %= N;

	printf("There are %d people in the queue ready to party! punchi punchi.\n", n);

	for(int i = 0; i < n; i++){
		clients[i].id = i;
		clients[i].myturn = -1;
		fscanf(file, " %d", &clients[i].is_vip);

		// Spawn a thread representing this client trying to enter.
		pthread_create(th_clients + i, NULL, client, (void*)(clients + i)); 
	}

	/*
	If given a choice between mutex/condition variables and semaphores,
	conditional variables are clearer here because of the multiple wait
	conditions (turn number, VIP precedence, and capacity).
	*/

	// cierro los threads
	for(int i = 0; i < n; i++){
		pthread_join(th_clients[i], NULL);
	}

	pthread_cond_destroy(&myturn);
	pthread_mutex_destroy(&m);

	fclose(file);

	return 0;
}
