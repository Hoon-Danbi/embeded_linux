#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>

int filestatus(int fd, char *file);

main()
{
    int fd, newfd, mode;

    if ((fd = open("aaa", O_RDWR)) == -1) {
       perror("open failed");
       exit(1);
    }
	// TODO 단어의 추가("VI EDITOR exercise code"가 출력되도록 하시오)
	printf("VI EDITOR exercise code\n");
	
	// TODO 오타의 수정( filstatus -> filestatus )
    if (filestatus(fd, "aaa") == -1) {
       exit(2);
    }
    close(fd);
    exit(0);
}

int filestatus(int fd, char *file)
{
    int flag;

    if ((flag=fcntl(fd, F_GETFL)) == -1) {
       perror("fcntl failed");
       return -1;
    }
	// TODO 아래 두문장의 출력 순서를 바꾸시오	
	printf("(1)bang, bang, bang\n");
	printf("(2)It's so hot, but I'm fine.\n");

	// TODO 아래 6라인을 출력이 되지 않도록 삭제하시오

    switch (flag & O_ACCMODE) {
	// TODO 바꾸기( ccaassee -> case )
       case O_RDONLY:
          printf("%s is read only file\n", file);
          break;
       case O_WRONLY:
          printf("%s is write only file\n", file);
          break;
       case O_RDWR:
          printf("%s is read-write file\n", file);
          break;
       default:
          printf("no such mode\n");
    }
    return 0;
}
