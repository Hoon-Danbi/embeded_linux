#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>

// 컴파일 요령
// gcc mmap.c -lpthread

int main(int argc, char **argv)
{
	int fd, i, count=0, nloop=10, zero=0, *ptr;
	sem_t mutex;
	
	if ( (fd = open("/dev/zero", O_RDWR)) < 0)
		perror("open error");
	if ( (ptr = mmap(0, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)) == (int*)-1)
		perror("mmap error");
	close(fd);		/* can close /dev/zero now that it's mapped */
	
	if ( sem_init(&mutex,1,1) < 0)
	{
		perror("semaphore initialization");
		exit(0);
	}

	if ( fork() == 0 )
	{ /* child */
		for (i=0; i < nloop; i++)
		{
			sem_wait(&mutex);
			printf("child: %d\n", (*ptr)++);
			sem_post(&mutex);
		}
		exit(0);
	}/* return to parent */
	
	for (i=0; i < nloop; i++)
	{
		sem_wait(&mutex);
		printf("parent: %d\n", (*ptr)++);
		sem_post(&mutex);
	}
	exit(0);
}

