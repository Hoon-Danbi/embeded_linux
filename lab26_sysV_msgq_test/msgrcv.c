#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/ipc.h> 
#include <sys/msg.h> 
#include <sys/stat.h> 

struct msgbuf  
{
    long msgtype;
    char mtext[256];
    char myname[16];
    int  seq;
};

int main(int argc, char **argv)
{
    key_t key_id;
    struct msgbuf mybuf;
    int msgtype;

    if (argc != 2)
    {
	printf(" Usage: msgsnd 번호(3 혹은 4)\n");
	exit(-1);
    }
    msgtype = atoi(argv[1]);

    key_id = msgget(1234, IPC_CREAT|0666);
    if (key_id < 0)
    {
        perror("msgget error : ");
        exit(0);
    }
    while(1)
    {
        if (msgrcv( key_id, /* msgq 식별자 */
		(void *)&mybuf, /* 데이터 구조체 */
		sizeof(struct msgbuf), /* 구조체의 크기 */
		msgtype, /* 가져올 메시지 타입 */
		0) == -1) /* 세부 조정 옵션 */
        {
            perror("msgrcv error : ");
            exit(0);    
        }
/* msgtyp == 0 메시지 큐의 첫번째 데이타를 돌려준다. 
   msgtyp > 0 메시지의 mtype 가 msgtyp 와 같은 첫번째 데이타를 돌려준다. 
   msgtyp < 0 메시지의 mtype 이 msgtyp 의 절대값보다 작거나 같은 첫번째 데이타를 돌려준다. 
*/
        printf("%d\n", mybuf.seq);
    }
    exit(0);
}

