/***************************************
 * Filename: thread_attr.c
 * Title: Thread Attributes(1)
 * Desc: 쓰레드 속성 예제
 * Revision History & Comments
 ***************************************/
#include <stdio.h>
#include <pthread.h>
#include <sched.h>
#include <unistd.h>
#include <sys/types.h>

int thread_args[3] = { 0, 1, 2 };
pthread_t threads[3];
int buffer[3];
int seq=0;

//
// ps command for thread check
// $ ps -elLf | grep a.out
// $ (./a.out &) && ps -elLf | grep a.out > ~/Desktop/elp/lab10_thread_attr/log
//
//------------------------------------------------------------------------------
void* Thread( void *arg )
{
    int i;
    int ret;
    int no = *(int*)arg;

    // struct sched_param is used to store the scheduling priority
    struct sched_param  param;

     // Now verify the change in thread priority
     int policy = 0;
     ret = pthread_getschedparam(threads[no], &policy, &param);
     if (ret != 0) {
         printf("Couldn't retrieve real-time scheduling paramers\n");
         return;
     }

     // We'll set the priority to the maximum.
     //param.sched_priority = sched_get_priority_max(SCHED_RR);
     //param.sched_priority = 30;
     param.sched_priority = 30 - no;
     //param.sched_priority = 30 + no;
     printf("MAX PRIO(SCHED_RR) : %d\n", param.sched_priority);
     
     // Attempt to set thread real-time priority to the SCHED_RR policy
     ret = pthread_setschedparam(threads[no], SCHED_RR, &param);
     if (ret != 0) {
         // Print the error
         printf("Unsuccessful in setting thread realtime prio[ERR %d]\n", ret);
         return;     
     }

     ret = pthread_getschedparam(threads[no], &policy, &param);
     if (ret != 0) {
         printf("Couldn't retrieve real-time scheduling paramers\n");
         return;
     }
 
     // Check the correct policy was applied
     if(policy != SCHED_RR) {
         printf("Scheduling is NOT SCHED_RR!\n");
     } else {
         printf("SCHED_RR OK\n");
     }

	for ( i=0; i<10000000; i++ ){
       // if ((i%1000)==0)
       //     printf( "%d",  *(int*)arg);
       //     fflush(stdout);
        ;
    }
    printf("쓰레드를 종료합니다[ID:%d]\n", no);
    fflush(stdout);

    //buffer[seq]=no;
    //seq++;
    
    pthread_exit(0);  
}

//------------------------------------------------------------------------------
int main( void ) {
    int i;
    int ret;
    
    /*쓰레드 속성지정을 위한 변수 */
    pthread_attr_t  thread_attrs;
    // struct sched_param is used to store the scheduling priority
    struct sched_param  param;

    for ( i=0; i<3; i++ ) {
        /* 쓰레드 속성 초기화 */
        pthread_attr_init( &thread_attrs );
        pthread_attr_getschedparam( &thread_attrs, &param );
        /* 생성할 쓰레드의 우선순위 설정 */
        param.sched_priority = 0;
        /* 스케줄링 정책 속성 설정 */
        pthread_attr_setschedpolicy( &thread_attrs, SCHED_RR );
        pthread_attr_setschedparam( &thread_attrs, &param );

		/* 쓰레드 생성 */
        pthread_create( &threads[i], 
                        &thread_attrs, 
                        ( void* (*)(void*) )Thread, 
                        &thread_args[i] );

    }
         (void) pthread_join(threads[0], NULL);
         (void) pthread_join(threads[1], NULL);
         (void) pthread_join(threads[2], NULL);
    
    printf("%d, %d, %d\n", buffer[0], buffer[1], buffer[2]);
    pthread_exit(0); /*메인 쓰레드 종료 */
}

