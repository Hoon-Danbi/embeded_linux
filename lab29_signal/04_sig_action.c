/*******************************************************************************
**  File:
**
**      04_sig_action.c
**
**  Contents:
**      LINUX system programming
**      
**  History:
**      Date        Name              Description
**      ------------------------------------------------------------------------
**
*******************************************************************************/
/*
    요점 정리
--------------------
1)시그널 block/unblock
2)시그널은 안정적인 통신방식을 제공해 주지는 못함
*/
#include <signal.h> 
#include <unistd.h> 
#include <string.h> 
#include <stdio.h> 
#include <stdlib.h>

void sig_int(int signo);
void sig_usr(int signo);

int main()
{
    int i = 0;
    struct sigaction intsig, usrsig;

    printf("PID=%d\n", getpid());

    usrsig.sa_handler = sig_usr;
    sigemptyset(&usrsig.sa_mask);
    usrsig.sa_flags = 0;

    intsig.sa_handler = sig_int;
    sigemptyset(&intsig.sa_mask);
    intsig.sa_flags = 0;

    if (sigaction(SIGINT, &intsig, 0) == -1)
    {
        printf ("signal(SIGINT) error");
        return -1;
    }    

    if (sigaction(SIGUSR2, &usrsig, 0) == -1)
    {
        printf ("signal(SIGUSR2) error");
        return -1;
    }    

    while(1)
    {
        printf("%d\n", i);
        i++;
        sleep(1);
    }
}

void sig_int(int signo)
{
    sigset_t sigset, oldset;
    sigfillset(&sigset);
#if 0
    // 새로들어오는 모든 시그널에 대해서 block 한다. 
    if (sigprocmask(SIG_BLOCK, &sigset, &oldset) < 0)
    {
        printf("sigprocmask %d block error \n", signo);
    }
#endif
    fprintf(stderr, "  sleep 5 secs !!!!\n");
    sleep(5);
    fprintf(stderr, "  wakeup !!!!\n");
}

void sig_usr(int signo)
{
    printf("sig_usr2\n");
}

