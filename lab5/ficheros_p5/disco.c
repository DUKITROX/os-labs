#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define CAPACITY 5
#define VIPSTR(vip) ((vip) ? "  vip  " : "not vip")

void enter_normal_client(int id)
{

}

void enter_vip_client(int id)
{

}

void dance(int id, int isvip)
{
	printf("Client %2d (%s) dancing in disco\n", id, VIPSTR(isvip));
	sleep((rand() % 3) + 1);
}

void disco_exit(int id, int isvip)
{

}

void *client(void *arg)
{

}

int main(int argc, char *argv[])
{
	//getting the member data from the file
	FILE* f;
	int memnum=0;

	f = fopen(argv[1], "r");
	if (!f){
		printf("Couldnt open file");
	}

	int fout=0;
	int counter = 0;
	while(fscanf(f,"%d",&fout) != EOF){
		printf("%d\n",fout);
		if (counter == 0) memnum = fout;
		counter++;

	}

	

	

	return 0;
}
