/******************************************
 * Filename: prio.c 
 * Title: Scheduling
 * Desc: getpriority()
 * ****************************************/ 
#include <stdio.h>
#include <sys/types.h>		//getpriority()
#include <sys/resource.h>
#include <unistd.h>			//getpid()

int main(void)
{
	//현재 프로세스의 ID를 구함 
	pid_t current_pid = getpid();
	
	//현재 프로세스의 우선순위설정 및 가져오기 
	/* 
	 * PRIO_PROCESS: 해당 프로세스의 ID 내 
	 * PRIO_PGRP: 해당 프로세스가 속한 그룹
	 * PRIO_USER: 사용자 ID를 갖는 프로세스
	 */
	setpriority(PRIO_PROCESS, 0, 10);
	//setpriority(PRIO_PGRP, 1000, 0);
	//setpriority(PRIO_USER, 1000, 0);
	//nice(10);	// 현재 nice 값에 몇을 더할 것인지 결정
	int priority = getpriority(PRIO_PROCESS, current_pid);

	printf("Process: %d, Priority: %d\n", current_pid, priority);

	for(;;) sleep(1);

	return 0;
}

/* [Notice] SCHED_FIFO 또는 SCHED_RR을 사용하는 프로세스 또는 쓰레드는 
setpriority () 호출에 영향을받지 않습니다 */

