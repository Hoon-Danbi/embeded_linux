#include <stdio.h>
#include <unistd.h>

// TODO 두개의 소스 코드 합치기(sub_002.c 파일내의 코드를 이곳으로 가져오시오)

int flag=0;

// TODO 바꾸기( printout -> printf )

main(int argc, char *argv[])
{
   FILE *fp;
   int opt;

   if (argc == 1) {
      printout("Usage : a.out [-n] filename ...\n");
      exit(1);
   }
	// TODO 단어의 추가("VI EDITOR exercise code"가 출력되도록 하시오)
	printout("VI EDITOR code\n");

	// TODO 아래 라인을 5줄 추가 하시요
	printf("insert this line\n");i

   while((opt = getopt(argc, argv, "n")) != -1) {
      switch(opt) {
         case 'n':
            flag = 1;
            break;
         default:
            printout("unknown option : %c\n", optopt);
      }
   }
   
   if(argc != 2)
      argv++;
 
   while (*++argv) {
      printout("\n[filename : %s]\n", *argv);
      if((fp = fopen(*argv, "r")) == NULL) {
         perror("fopen failed");
         exit(2);
      }
      output_file(fp);
      fclose(fp);
   }
   exit(0);
}
	
