/*******************************************************************************
**	File:
**
**		upper.c
**
**  Contents:
**		LINUX system programming
**
**	History:
**		Date        Name              Description
**		------------------------------------------------------------------------
**
*******************************************************************************/
/*
	요점 정리
--------------------
1)filesize(by lseek)
2)file read
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>

main(int argc, char *argv[])
{
    int fd, i;
    off_t filesize;
	char	*ptr;
	unsigned long count= 0;

    if ((fd = open(argv[1], O_RDWR)) == -1) {
       perror("open failed");
       exit(1);
    }

    /* 읽기/쓰기 포인터가 파일의 끝을 가리키게 되고, 
       변경된 읽기/쓰기 포인터가 반환되는데 이는 파일의 크기가 된다. */
    if ((filesize=lseek(fd, 0L, SEEK_END)) == -1) {
       perror("lseek failed");
       exit(1);
    }

    if (lseek(fd, 0, SEEK_SET) == -1) {
       perror("lseek failed");
       exit(1);
    }

	// 메모리 할당
	if ( (ptr = malloc(filesize)) == NULL)
	{
		perror("malloc error"); return(-1);
	}

	/* 내용 읽기 */
	read(fd, ptr, filesize);

	/* 알파벳 소문자는 대문자로 변경한다 */
	for(i=0; i<filesize; i++)
	{
		if( (ptr[i] >= 'a') && (ptr[i] <= 'z') )
		{
			ptr[i] = ptr[i] - 0x20; // to upper character
			count++;
		}
	}

	if (lseek(fd, 0, SEEK_SET) == -1) {
	   perror("lseek failed");
	   exit(1);
	}

	/* 내용 쓰기 */
	write(fd, ptr, filesize);
    close(fd);

	printf("Total %ld alphabet character is converted\n", count);

    exit(0);
}

/* upper.c */
