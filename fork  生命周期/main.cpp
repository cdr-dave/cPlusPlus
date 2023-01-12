//
//  main.cpp
//  fork  生命周期
//
//  Created by cdr on 2022/7/19.
//

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
 
void catchalarm(int signo)
{
    printf("Caught signal: %d\n", signo);
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        printf("Please enter a second.\n");
        exit(1);
    }
    if (signal(SIGALRM, catchalarm) == SIG_ERR)
    {
        perror("signal");
        exit(1);
    }
    alarm(atoi(argv[1]));
    if (pause() == -1 && errno == EINTR)
    {
        printf("Pause finished..\n");
        return 0;
    }
    alarm(0);

    printf("end proc!!!!\n");
    
    return 1;
}


