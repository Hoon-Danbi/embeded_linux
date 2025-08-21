/***************************************
 * Filename: mutex_test.c
 * Title: Mutex
 * Desc: 뮤텍스를 이용한 예제 
 ***************************************/
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <sys/types.h>

/* TODO: 뮤텍스 변수 선언 mutex, 선언과 동시에 초기화 */
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int val=0;
int arg1 = 0, arg2 = 1;
//-------------------------------------------
void *Thread( void* arg ) 
{
    int i, j;
    
    for( i = 0; ; i++ ) {

    /* TODO: mutex 잠그기 */
    pthread_mutex_lock( &mutex );

	val = *(int*)arg;
	printf( "thread %d: %dth iteration: val=%d\n", *(int*)arg, i, val);

    /* TODO: mutex 풀기 */
    pthread_mutex_unlock( &mutex );

        //for ( j=0; j<1000000; j++ );
        sleep(1);
    }
}
//-------------------------------------------
int main( void ) {
    pthread_t  thread1, thread2;
    pthread_attr_t attr;
    
    struct sched_param param;
    int policy;
    
    pthread_getschedparam( pthread_self(), &policy, &param );
    param.sched_priority = 1;
    policy = SCHED_RR;
    if ( pthread_setschedparam( pthread_self(), policy, &param ) != 0 ) {
        printf("main\n");
        while(1);
    }
    pthread_attr_init( &attr );
    pthread_attr_setschedpolicy( &attr, SCHED_RR );
    
    pthread_create( &thread1, &attr, (void*(*)(void*))Thread, &arg1 );
    pthread_create( &thread2, &attr, (void*(*)(void*))Thread, &arg2 );
    
    (void) pthread_join(thread1, NULL);
    (void) pthread_join(thread2, NULL);

    pthread_exit(0);
    return 0;

}
/****************************************
 Run:
*****************************************
thread 0: 0th iteration: i = 0                                                  
thread 1: 0th iteration: i = 1                                                  
thread 0: 1th iteration: i = 0                                                  
thread 1: 1th iteration: i = 1                                                  
thread 0: 2th iteration: i = 0                                                  
thread 1: 2th iteration: i = 1                                                  
thread 0: 3th iteration: i = 0                                                  
thread 1: 3th iteration: i = 1                                                  
thread 0: 4th iteration: i = 0                                                  
thread 1: 4th iteration: i = 1                                                  
thread 0: 5th iteration: i = 0                                                  
thread 1: 5th iteration: i = 1                                                  
thread 0: 6th iteration: i = 0                                                  
thread 1: 6th iteration: i = 1                                                  
thread 0: 7th iteration: i = 0       
...
*****************************************/
