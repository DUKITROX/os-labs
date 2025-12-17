// tienes que saber manejar se√ales de forma nice
// SI ENTRA ALGO EN EL EXAMEN DE SERA DE ESTO Y YA

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

/*programa que temporiza la ejecuci√≥n de un proceso hijo */

int pid;

// este tipo de la funcion lo hemos sacado de sigaction(2), que dice que uno de los parametros
// del struct sea un puntero a una funcion que recibe un int y devuelve un void
void handler(int signum){
	printf("Senal recibida: %d\n", signum);
	kill(pid, SIGKILL);
	// enviar al hijo la senal kill para que los ojos se cierren
}


//Lanzar un proceso hijo con lo que se ha recibido del padre
int main(int argc, char **argv)
{
	//esto para "ignorar" el ctrl+C
	sigset_t grupo; //se√ales a enmascarar
	sigemptyset(&grupo);
	sigaddset(&grupo, SIGINT);
	sigprocmask(SIG_SETMASK, &grupo, NULL);

	// lanzamos un proceso hijo con el command que nos hayan pasado como argumento y nos olvidamos de el
	pid = fork();
	if(pid<=0){ // proceso hijo
		// runs another program, and if success, current "code running STOPS" bomboclat
		execvp(argv[1], argv+1);
		perror("execvp");
		exit(1);
	}

	struct sigaction sa; // mirarla en man
	sa.sa_handler = (void*)handler;
	sa.sa_flags=0;
	sigaction(SIGALRM, &sa, NULL);
	alarm(5);

	int status;
	pid_t err = wait(&status);
	//mientras no funcione porque es un interrupcion, se ejecuta eso
	do{
		err = wait(&status);
		printf("El codigo de salida de wait es err=%d, y errno=%d\n", err, errno);
	}while(err<0 && EINTR);

	// macros que encuentras buscando
	if(WIFEXITED(status)){
		printf("El hijo ha salido con estado %d\n", WEXITSTATUS(status));
	}
	else if(WIFSIGNALED(status)){
		printf("El hijo ha recibido la senal %d\n", WTERMSIG(status));
	}

	return 0;
}
