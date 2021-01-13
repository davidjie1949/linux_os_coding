#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>

static void structure_daemon(){
    pid_t pid;
    pid = fork();

    if (pid < 0){
        exit(EXIT_FAILURE);
    }else if (pid > 0){
        exit(EXIT_SUCCESS);
    }

    if (setsid() < 0){
        exit(EXIT_FAILURE);
    }

    signal(SIGCHLD, SIG_IGN);
    signal(SIGHUP, SIG_IGN);

    pid = fork();

    if (pid < 0){
        exit(EXIT_FAILURE);
    }else if (pid > 0){
        exit(EXIT_SUCCESS);
    }

    umask(0);
    chdir("/");

    int x;
    for(x = sysconf(_SC_OPEN_MAX); x >=0; x--){
        close(x);
    }

    openlog("DaemonHere", LOG_PID, LOG_DAEMON);
}


int main()
{
    structure_daemon();

    for(;;){
        syslog(LOG_NOTICE, "DAEMON HAS STARTED");
        sleep(20);
        break;
    }

    syslog(LOG_NOTICE, "DAEMON HAS TERMINATED");
    closelog();

    return EXIT_SUCCESS;
}
