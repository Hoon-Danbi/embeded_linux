/*******************************************************************************
**	File:
**
**		02_reset.c
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
1)시그널의 종류(signum.h)
2)SIGINT
*/
#define _SIGNAL_MASK_IFDEF
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

int entered= 0;

void interrupt(int signo)
{
	// SIGINT 의 효과를 끈다
#if 0
	signal(SIGINT, SIG_IGN);
#endif
	entered++;
	printf("Interrupt entered(%d)\n", entered);
	sleep(2);
	printf("Interrupt exit(%d)\n", entered);

	// SIGINT 를 다시 활성화 한다
#if 0
	signal(SIGINT, interrupt);
#endif
}

int main(void)
{
	signal(SIGINT, interrupt);
	printf("Interrupt set for SIGINT\n");
	while(1);

	return 0;
}


/* 02_reset.c */
