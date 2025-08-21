/***************************************
 * Filename: fork_test.c
 * Title: Process Management
 * Desc: Create the child process using execl
 * ***************************************/
#include <stdio.h>
#include <stdlib.h> // for system()
#include <unistd.h> // for execl(), fork()
#include <wait.h>	// for wait()

// 온라인 매뉴얼 "http://man7.org"

int main(int argc, char *argv[])
{
    int pid;

    /* fork another process */
    pid = fork(); //system call

    if(pid < 0) {			/* error occurred */
        fprintf(stderr,"Fork Failed");
        exit(-1);
    } else if (pid == 0) {	/* child process */
		//execl("/bin/ls", "ls", NULL);
		//execl("/bin/ps", "ps", "aux", NULL);
		printf("Child here!\n");
		for(;;) sleep(1);
		exit(0);
    } else {          /* parent process */
        wait(NULL); 
        printf("Child Complete!\n");
        exit(0);
    }
}
