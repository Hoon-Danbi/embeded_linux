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
	���� ����
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

    /* �б�/���� �����Ͱ� ������ ���� ����Ű�� �ǰ�, 
       ����� �б�/���� �����Ͱ� ��ȯ�Ǵµ� �̴� ������ ũ�Ⱑ �ȴ�. */
    if ((filesize=lseek(fd, 0L, SEEK_END)) == -1) {
       perror("lseek failed");
       exit(1);
    }

    if (lseek(fd, 0, SEEK_SET) == -1) {
       perror("lseek failed");
       exit(1);
    }

	// �޸� �Ҵ�
	if ( (ptr = malloc(filesize)) == NULL)
	{
		perror("malloc error"); return(-1);
	}

	/* ���� �б� */
	read(fd, ptr, filesize);

	/* ���ĺ� �ҹ��ڴ� �빮�ڷ� �����Ѵ� */
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

	/* ���� ���� */
	write(fd, ptr, filesize);
    close(fd);

	printf("Total %ld alphabet character is converted\n", count);

    exit(0);
}

/* upper.c */
