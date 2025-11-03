#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <limits.h>
#include <sys/prctl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <string.h>

#include <pthread.h>


int main( int argc, const char **argv){

    pid_t pid;
    int retval, prio, sched_type;

    if ( argc != 4  ){
        printf("Usage: %s <PID> <SCHED_TYPE> <PRIO>\n", argv[0]);
        return -1;
    }

    pid = atoi( argv[ 1 ] );

    if ( ! strcmp( argv[ 2 ] , "SCHED_FIFO" ) ) {
        sched_type = SCHED_FIFO;
    } else {
        fprintf(stderr, "Invalid scheduler policy\n");
        return -1;
    }

    prio = atoi( argv[ 3 ] );

    struct sched_param param;

    param.sched_priority = prio;

    retval = sched_setscheduler( pid , sched_type, &param);

    if (retval != 0 ){
        perror("");
        exit(retval);
    }

    return 0;
}