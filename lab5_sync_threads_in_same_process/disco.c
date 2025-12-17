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
pro tip : siempre haz "lock" y "unlock" y luego ves dnd los mueves
para esto piensa en el eg. de coger un ticket en la pescaderia y esperar tu turno
mirando la pantalla (las pantallas seran variables globales, pues todos tiene que leerlas)
*/

void arrive_client(client_t* client) {
	pthread_mutex_lock(&m);

	client->myturn = (client->is_vip) ? counter_vip++ : counter++;

	printf("Client %d (%s) recieves his turn (%d)\n", client->id, VIPSTR(client->is_vip), client->myturn);
	fflush(stdout); // fuerza al OS a imprimir YA, como tenemos varias hebras queremos que salga cuanto antes

	// while en vez de wait para evitar efectos de carrera
	if(client->is_vip){
		// podrias poner clients_inside == CAPACITY, pero los "==" tardan mas que un "<=", manias internas de jlrisco...
		vips_waiting++;
		while((client->myturn != vip_turn) || (clients_inside >= CAPACITY)) { 
			// intentamos de primeras usar solo 1 vairable, todos van a la misma cola y se van peleando
			// los vips adelantan (esto en vez de tener 2 colas).
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
		vips_waiting--; // de momento lo ponemos aqui, luego vemos dnd lo dejamos
		vip_turn++;
	}
	else{
		normal_turn++;
	}
	int seconds = rand()%6 + 3; // [3,9) segundos bailados

	printf("Client %d (%s) is inside and is dancing for %d seconds.\n", client->id, VIPSTR(client->is_vip), seconds);
	fflush(stdout); // fuerza al OS a imprimir YA, como tenemos varias hebras queremos que salga cuanto antes
	pthread_cond_broadcast(&myturn); // IMPORTANTE!! MUCHO OJO CON ESTO, usar broadcast y NO signal, porque consignal despertaria solo a 1 de los encolados, puedes freir el sistema
	pthread_mutex_unlock(&m);
	sleep(seconds); // esta es la parte paralela para que bailen todos a la vez punchi punchi!
}

void exit_client(client_t* client) {
	pthread_mutex_lock(&m);
	clients_inside--;
	printf("Client %d (%s) leaves the local.\n", client->id, VIPSTR(client->is_vip));
	fflush(stdout);
	pthread_cond_broadcast(&myturn); // vuelves a hacer un broadcast para despertar a todos y que se vuelvan a pegar para ver quien entra
	pthread_mutex_unlock(&m);
}

void *client(void *arg) {
	client_t* client = (client_t*) arg; // parseamos cliente

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

		// creo un thread con este cliente intentando bailar
		pthread_create(th_clients + i, NULL, client, (void*)(clients + i)); 
	}

	/*
	Si te dan libertad, tienes que dicidir si usar mutex + variables condicionales o semaforos.
	Aqui como tenemos tantas condiciones, mejor mutex + variables condicionales. Mas easy es esto
	pero la forma pro de hacerlo es con semaforos.
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
