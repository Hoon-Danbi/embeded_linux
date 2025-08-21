/*****************************************
 * Filename: sched_param.c
 * Title: Scheduling
 * Desc: Set and get scheduling parameters
 *
 * int sched_setparam(pid_t pid, const struct sched_param *p);
 * int sched_getparam(pid)t pid, struct sched_param *p);
 * 
 * ****************************************/ 
#include <stdio.h>
#include <sys/types.h>
#include <sched.h> // sched_getparam()
#include <stdlib.h>
#include <unistd.h>

//
// Root privileges are required to reduce the priority level.
// PS command prio[0~58]:RT, prio[60~99]:other
int main(void)
{
	struct sched_param param;
	int policy;
	char *policy_name;

	pid_t current_pid = getpid();

	sched_getparam(current_pid, &param);
 param.sched_priority = 1; // 1~59(HIGHEST)
	sched_setscheduler(current_pid, SCHED_RR, &param);
	sched_setparam(current_pid, &param);
	sched_getparam(current_pid, &param);
	policy = sched_getscheduler(current_pid);

	if (policy == 0) 		policy_name = "SCHED_OTHER";
	else if (policy == 1) 	policy_name = "SCHED_FIFO";
	else if (policy == 2) 	policy_name = "SCHED_RR";
	else 			 		policy_name = "Unknown";
	printf("Current PID: %d\n", (int)current_pid);
	printf("Scheduling Policy: %d, %s\n", policy, policy_name);
	printf("RT Sched Priority: %d\n", param.sched_priority);

	while(1) sleep(1);

	return 0;
}

