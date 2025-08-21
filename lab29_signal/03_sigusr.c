/*******************************************************************************
**	File:
**
**		03_sigusr.c
**
**  Contents:
**		LINUX system programming
**
**	History:
**		Date        Name              Description
**		------------------------------------------------------------------------
**
*******************************************************************************/
/*
	요점 정리
--------------------
1)SIGUSR1/SIGUSR2( using this command $kill -12 PID )
*/
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

static void	sig_usr(int);	/* one handler for both signals */

int main(void)
{
	if (signal(SIGUSR1, sig_usr) == SIG_ERR)
		perror("can't catch SIGUSR1");
	if (signal(SIGUSR2, sig_usr) == SIG_ERR)
		perror("can't catch SIGUSR2");

	for ( ; ; )
		pause();
}

static void
sig_usr(int signo)		/* argument is signal number */
{
	if (signo == SIGUSR1)
		printf("received SIGUSR1\n");
	else if (signo == SIGUSR2)
		printf("received SIGUSR2\n");
	else
		printf("received signal %d\n", signo);
	return;
}

/* 03_sigusr.c */
