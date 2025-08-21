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

	mutex = sem_open(SEM_NAME,O_CREAT,0644,1);
	if(mutex == SEM_FAILED){
		perror("unable to create semaphore");
		sem_unlink(SEM_NAME); 
		exit(-1);
	}
	//이 key로 공유메모리 생성
	shmid = shmget(key,SHMSZ,IPC_CREAT|0666);
	if(shmid<0){
		perror("failure in shmget"); 
		exit(-1);
	}
	//이 조각을 가상메모리에 덧붙인다.
	shm = shmat(shmid,NULL,0);

	//메모리에 쓰기 시작
	s = shm;
	for(ch='A';ch<='Z';ch++){
		sem_wait(mutex);
		*s++ = ch;
		sem_post(mutex);
	}
	//아래 루프는 이진세마포어로 대체 가능하다
	while(*shm != '*'){
		sleep(1);
	}
	sem_close(mutex); // 세마포어는 여전히 시스템에 남아 있슴
	sem_unlink(SEM_NAME); // 참조 카운트가 0이 될 때만 시스템에서 제거됩니다
	shmctl(shmid, IPC_RMID, 0); 
	exit(0);
}
