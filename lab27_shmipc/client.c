#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define SHMSZ 27

char SEM_NAME[]= "vik";

int main()
{
	char ch;
	int shmid;
	key_t key;
	char *shm,*s;
	sem_t *mutex;	//name the shared memory segment
	
	key = 1000;

	//세마포어 생성 초기화
	mutex = sem_open(SEM_NAME,0,0644,0);
	if(mutex == SEM_FAILED){
		perror("reader:unable to execute semaphore");
		sem_close(mutex);
		exit(-1);
	}
	//이 key를 사용하여 공유메모리 생성
	shmid = shmget(key,SHMSZ,0666);
	if(shmid<0){
		perror("reader:failure in shmget");
		exit(-1);
	}
	//이 조각을 가상메모리에 덧붙인다.
	shm = shmat(shmid,NULL,0);
	//start reading
	s = shm;
	for(s=shm;*s!=NULL;s++){
		sem_wait(mutex);
		putchar(*s);
		sem_post(mutex);
	}
	//다른 세마포어로 대체 가능
	*shm = '*';
	sem_close(mutex); // 세마포어는 여전히 시스템에 남아 있슴
	shmctl(shmid, IPC_RMID, 0);
	exit(0);
}
