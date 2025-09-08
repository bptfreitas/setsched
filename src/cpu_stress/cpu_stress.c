#include <unistd.h>
#include <stdio.h>

#include <stdlib.h>

#include <signal.h>
#include <syslog.h>

#include <sys/stat.h>
#include <sys/types.h>

#include <sys/prctl.h>

#include <limits.h>
#include <string.h>

#include <cpu_stress/cpu_stress.h>

int main(int argc, char **argv ){

    int opt;
    
    // put ':' in the starting of the
    // string so that program can 
    //distinguish between '?' and ':' 
    int n_processes = 1;

    while((opt = getopt(argc, argv, ":n:")) != -1) 
    { 
        switch(opt) 
        { 
            case 'n': 
                n_processes = atoi( optarg );

                // printf("filename: %s\n", optarg); 
                break; 
            case ':': 

                printf("option needs a value\n"); 
                break;

            case '?': 
                printf("unknown option: %c\n", optopt);
                break; 
        } 
    }

    fprintf( stdout , "\nNumber of processes to create: %d", n_processes);

    fflush( stdout ); 

    for ( int i = 0; i < n_processes; i ++ ){

        pid_t pid;
        pid = fork();
        if (pid < 0) {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        }
        if (pid > 0) {
            exit(EXIT_SUCCESS);
        }

        if (setsid() < 0) {
            perror("Failed to create a new session");
            exit(EXIT_FAILURE);
        }

        pid = fork();
        if (pid < 0) {
            perror("Second fork failed");
            exit(EXIT_FAILURE);
        }

        if (pid > 0) {
            exit(EXIT_SUCCESS);
        }

        if ( pid = fork( ) ){

            char pname[ 16 ];
            int retval;
            int n_bytes;
            
            n_bytes = sprintf( pname, "stress%hd", i);

            retval = prctl( PR_SET_NAME, pname );

            openlog(pname, LOG_PID, LOG_DAEMON);
            syslog(LOG_INFO, "Daemon started.");

            //syslog(LOG_INFO, "\n[Child %d] PID: %d", i, pid);

            CPU_intensive( ( (long)INT_MAX << 2) );
            exit( 0 );

        }        
    
    }

    fprintf( stdout, "\n");
    return 0;
}