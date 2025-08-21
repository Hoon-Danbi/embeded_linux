#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#define BUFSIZE 15

//--------------------------------------
// Create a pipe, write to it, and read from it.
int main( int argc, char **argv )
{
	static const char mesg[] = "Don't Panic!";
	char buf[BUFSIZE];
	ssize_t rcount, wcount;
	int pipefd[2]; /*pipe에서 사용할 파일기술자*/
	size_t len; /* TODO: pipe 를생성한다. (에러 처리할 것) */

	if ( pipe(pipefd) < 0 ) 
	{
		fprintf(stderr, "%s: pipe failed : %s\n", argv[0], strerror(errno));
		exit(1);
	}
	printf( "Read end = fd %d, write end = fd %d\n",pipefd[0], pipefd[1]);/* write에사용할message의길이*/
	len = strlen(mesg);
	wcount = write( pipefd[1], mesg, len);
	rcount = read( pipefd[0], buf, BUFSIZE);

	/* 읽은 데이터를 보통의 문자열로 만들기 위해*/
	buf[rcount] = '\0';

	printf( "Read <%s> from pipe \n", buf );

	close( pipefd[0] );
	close( pipefd[1] );

	return 0;
}
