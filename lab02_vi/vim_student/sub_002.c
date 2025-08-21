void output_file(FILE *fp)
{
   int ch, line=1;

// TODO 오타의 수정( fllag -> flag )
   if(fllag)
      printf("1   ");

   while((ch=getc(fp)) != EOF) {
      putc(ch, stdout);

      if(flag && ch=='\n')
         printf("%-4d", ++line);
   }
}
