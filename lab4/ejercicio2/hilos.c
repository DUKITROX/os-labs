#include <stdlib.h>
#include <stdio.h>
#include<pthread.h>
#include<unistd.h>
#define N 10

typedef struct{
  int index;
  char prioritario;
}tData;


void *thread_usuario(void *arg)
{
	//El i está metido a lo bruto, le pasas un puntero a una función pero le hago un casting al int
	tData dato=*((tData*)arg);
	free(arg); 
	printf("Soy el hilo %lu con id %d con prioridad %c \n", pthread_self(),dato.index,dato.prioritario);
	sleep(1);
	pthread_exit(NULL);
}

int main(int argc, char* argv[])
{
	pthread_t thread[N];
	tData* values[N];
	for(int i=0;i<N;++i){
	  values[i]=malloc(sizeof(tData));
	  values[i]->index=i;
          if(i%2==0)values[i]->prioritario='P';
	  else values[i]->prioritario='N';
	  pthread_create(&thread[i],NULL,thread_usuario,values[i]);
	}
	for(int j=0;j<N;++j){
	 pthread_join(thread[j],NULL);
	}
	return 0;
}

