#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define FIFO_FILE "/tmp/fifo"

int main(void)
{
	int fd;
	char *str = "forum.falinux.com";
	if ( -1 == ( fd = open( FIFO_FILE, O_WRONLY)))
	{
		perror( "open() 실행에러");
		exit( 1);
	}
	write( fd, str, strlen(str));
	close( fd);
}
