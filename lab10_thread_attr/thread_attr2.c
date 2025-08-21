#include <stdio.h>
#include <pthread.h>
#include <sched.h>
//#include <sys/param.h>

int thread_args[3] = { 0,1,2 };
pthread_t threads[3];

void* Thread(void *arg)
{
	int i;
	for(i=0; i< 10000; i++)
		printf("thread %d: %dth ineration \n", *(int*)arg,i);
	pthread_exit(0);
}

int main(void *arg)
{
	int i;
	struct sched_param param;
	pthread_t threads[3];						// 스레드 속성 지정을 위한 변수
	pthread_attr_t thread_attrs;					// 스케줄링 정책 지정을 위한 구조체

	for(i=0; i<3; i++)
	{
		pthread_attr_init(&thread_attrs);			// 스레드 속정 초기화
		
		
		/* 스케줄링 정책 속성을 라운드 로빈으로 설정 */
		pthread_attr_setschedpolicy(&thread_attrs, SCHED_RR);


		param.sched_priority = 50;				// 생성할 스레드의 우선순위 설정
		pthread_attr_setschedparam(&thread_attrs, &param);	// ?
		
		
		/*  스레드 생성 */
		pthread_create(&threads[i],&thread_attrs,(void* (*)(void*))Thread,&thread_args[i]);
		
		
	}
	pthread_exit(0);						// 메인 스레드 종료
}