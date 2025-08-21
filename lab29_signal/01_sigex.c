/*******************************************************************************
**	File:
**
**		01_sigex.c
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
2)SIG_IGN, SIG_DFL
3)SIG_HUP/SIG_INT/SIG_KILL/SIG_TERM/SIG_USR1/SIG_USR2/SIG_SEGV/SIG_ALRM
(단말기종료/인터럽트키/어떤경우에도동작/소프트웨어/사용자정의1/사용자정의2/포인터오류/알람)
*/
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

// SIGINT와 사용할 함수 fn 을 정의
void catchint(int signo);

int main(void)
{
	int i;

	// 이 위치에서 시그널이 발생될 경우 SIGINT에 의해 프로세스 터미네이트
	signal(SIGINT, catchint);
//	signal(SIGINT, SIG_IGN);
//	signal(SIGINT, SIG_DFL);

	for(i=10; i>0; i--)
	{
		printf("%d seconds remain till process's terminated\n", i);
		sleep(1);
	}

	printf("Exiting\n");
	return(0);
}

// trivial function to handle SIGINT
void catchint(int signo)
{
	printf("\nCATCHINT: signo=%d\n", signo);
	printf("CATCHINT: returning\n\n");
}

/* 01_sigex.c */
