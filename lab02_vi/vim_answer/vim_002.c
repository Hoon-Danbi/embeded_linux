#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int flag=0;

// TODO 두개의 소스 코드 합치기(sub_002.c 파일내의 코드를 이곳으로 가져오시오)
void output_file(FILE *fp)
{
   int ch, line=1;

// TODO 오타의 수정( fllag -> flag )
   if(flag)
      printf("1   ");

   while((ch=getc(fp)) != EOF) {
      putc(ch, stdout);

      if(flag && ch=='\n')
         printf("%-4d", ++line);
   }
}

// TODO 바꾸기( printf -> printf )

main(int argc, char *argv[])
{
   FILE *fp;
   int opt;

   if (argc == 1) {
      printf("Usage : a.out [-n] filename ...\n");
      exit(1);
   }
	// TODO 단어의 추가("VI EDITOR exercise code"가 출력되도록 하시오)
	printf("VI EDITOR exercise code\n");

	// TODO 아래 라인을 5줄 추가 하시요
	printf("insert this line\n");
	printf("insert this line\n");
	printf("insert this line\n");
	printf("insert this line\n");
	printf("insert this line\n");
	printf("insert this line\n");

   while((opt = getopt(argc, argv, "n")) != -1) {
      switch(opt) {
         case 'n':
            flag = 1;
            break;
         default:
            printf("unknown option : %c\n", optopt);
      }
   }
   
   if(argc != 2)
      argv++;
 
   while (*++argv) {
      printf("\n[filename : %s]\n", *argv);
      if((fp = fopen(*argv, "r")) == NULL) {
         perror("fopen failed");
         exit(2);
      }
      output_file(fp);
      fclose(fp);
   }
   exit(0);
}

