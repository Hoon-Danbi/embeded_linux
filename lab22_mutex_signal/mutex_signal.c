/***************************************
 * Filename: mutex_signal.c
 * Title: Mutex
 * Desc: 잠금 대기에 관한 예제 
 ***************************************/
#include <stdio.h>
#include <pthread.h>

pthread_t  thread;

/* 뮤텍스 초기화 */
pthread_mutex_t  mutex = PTHREAD_MUTEX_INITIALIZER;
/* TODO: 조건 변수의 초기화 */
pthread_cond_t  cond = PTHREAD_COND_INITIALIZER;

/* 전역 변수 */
int count = 0;
//------------------------------------------------
void* Thread ( void* arg ) {
    
    pthread_mutex_lock ( &mutex ); 
    
    /* TODO: count가 5가 될 때까지 기다림, 블록될 경우에는 뮤텍스를 푼다 */
    while ( count < 5 ) {
        printf( "count = %d: wait...\n", count );
        pthread_cond_wait ( &cond, &mutex );
    }
    printf( "count = %d: condition true.\n", count );
    
    pthread_mutex_unlock ( &mutex );
}
//------------------------------------------------
void main ( void ) {
    int i;
    pthread_create( &thread, NULL, (void*(*)(void*))Thread, NULL );
    
    for ( i = 0; i < 10; i++ ) {
        sleep(1);
        pthread_mutex_lock( &mutex );

        count++;
        /* TODO: 쓰레드에 시그널 보내기 */
        pthread_cond_signal( &cond );
        printf( "condition signal %d\n", i );

        pthread_mutex_unlock( &mutex );
    }
	(void) pthread_join(thread, NULL);
    pthread_exit(0);
}
/****************************************
 Run:
*****************************************
count = 0: wait...
condition signal 0
count = 1: wait...
condition signal 1
count = 2: wait...
condition signal 2
count = 3: wait...
condition signal 3
count = 4: wait...
condition signal 4
count = 5: condition true.
condition signal 5
condition signal 6
condition signal 7
condition signal 8
condition signal 9
*****************************************/
