/***************************************
 * Filename: posix_sem_test.c
 * Title: Semaphore
 * Desc: POSIX Semaphore simple test
 ***************************************/
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

sem_t sem;  /*TODO: semaphore variable - sem */
pthread_t task1, task2;
pthread_attr_t attr;
struct sched_param param;
//----------------------------------------
void get_thread( void ) {
    int i = 0;
    int val;
  
    while(1) {
        i++;
        sem_wait( &sem ); /* TODO: obtains semaphore, reduce it by 1 */
        sem_getvalue( &sem, &val ); /* obtains the semaphore value */
        printf( "WAIT!\tsem count = %d\n" ,val );
        if ( i > 5 ) break;
    }
}
//----------------------------------------
void put_thread(void) {
	int i = 0;
	int val;

    while(1) {
        i++;
        sem_post( &sem ); /* TODO: semaphore post */
		sleep(1);
		sem_getvalue( &sem, &val ); /* obtains the semaphore value */
        printf( "POST!\tsem count = %d\n", val );
        if ( i > 5 ) break;
	}
}
//----------------------------------------
int main( void ) {
    int i = 0, j, val;

    sem_init( &sem, 0, 3 ); /* TODO: initialize unnamed semaphore */
	sem_getvalue(&sem, &val);
    printf( "INIT!\tsem count = %d\n", val );

	pthread_attr_init(&attr);
	param.sched_priority = 20;
	pthread_attr_setschedparam(&attr, &param);
	pthread_attr_setschedpolicy( &attr, SCHED_FIFO );

	pthread_create( &task1, &attr, (void*(*)(void*))get_thread, NULL );
    pthread_create( &task2, &attr, (void*(*)(void*))put_thread, NULL );
 
        (void) pthread_join(task1, NULL);
        (void) pthread_join(task2, NULL);
    
	pthread_exit(0);
}
