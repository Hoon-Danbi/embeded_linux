#include <stdlib.h>
#include <fcntl.h>
#include <mqueue.h>
#include <stdio.h>

// 컴파일 요령
// gcc mq_client.c -lrt

/*
struct mq_attr {
    long mq_flags; // 플래그 (mq_open ()에 대해 무시 됨)
    long mq_maxmsg; // MAX. 대기열 메시지 수
    long mq_msgsize; // MAX. 메시지 크기 (바이트)
    long mq_curmsgs; // 현재 대기중인 메시지 수
                     (mq_open ()에서 무시 됨)
};
*/
// ls /proc/sys/fs/mqueue
// cat /etc/security/limits.conf 
int main(int argc, char **argv)
{
    struct mq_attr attr;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = 4;
    int value = 0;

    mqd_t mfd;

    mfd = mq_open("/my_mq", O_WRONLY, 0666, &attr);
    if(mfd == -1)
    {
        perror("open error");
        exit(0);
    }

    while(1)
    {
        if((mq_send(mfd, (char *)&value, attr.mq_msgsize, 1)) == -1)
        {
            perror("send error");
            exit(-1);
        }
        sleep(1);
        value ++;
    }
}

