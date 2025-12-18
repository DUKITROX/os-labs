/*
 * Launch a child process, mask Ctrl+C in the parent, and kill the child
 * after an alarm expires. Demonstrates sigaction, alarm, and inspecting
 * wait status to see whether the child exited normally or by signal.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>

int pid;

/* Signal handler triggered by the alarm to terminate the child process. */
void handler(int signum) {
    printf("Signal received: %d\n", signum);
    kill(pid, SIGKILL);
}

int main(int argc, char **argv)
{
    /* Ignore Ctrl+C in the parent by masking SIGINT. */
    sigset_t grupo; /* signals to mask */
    sigemptyset(&grupo);
    sigaddset(&grupo, SIGINT);
    sigprocmask(SIG_SETMASK, &grupo, NULL);

    pid = fork();
    if (pid <= 0) { /* child process */
        execvp(argv[1], argv + 1);
        perror("execvp");
        exit(1);
    }

    /* Configure SIGALRM to invoke our handler. */
    struct sigaction sa;
    sa.sa_handler = (void*)handler;
    sa.sa_flags = 0;
    sigaction(SIGALRM, &sa, NULL);
    alarm(5);

    int status;
    pid_t err = wait(&status);
    /* Retry wait if it was interrupted by a signal. */
    do {
        err = wait(&status);
        printf("El codigo de salida de wait es err=%d, y errno=%d\n", err, errno);
    } while (err < 0 && EINTR);

    /* Report how the child finished. */
    if (WIFEXITED(status)) {
        printf("El hijo ha salido con estado %d\n", WEXITSTATUS(status));
    } else if (WIFSIGNALED(status)) {
        printf("El hijo ha recibido la senal %d\n", WTERMSIG(status));
    }

    return 0;
}
