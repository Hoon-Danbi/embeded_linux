#include <stdio.h>

void printbit(char ch);

// TODO 검색및 치환( "EOR" 을 찾아 "XOR" 로 수정하시오 )
// TODO 36행의 코드 오류(세미콜론)를 수정하시오.
main( )
{
   char a, b, c;
   int select;

   while (1) {
      printf("\nselect menu: 1.AND 2.OR 3.XOR 4.exit => ");
      scanf("%d", &select);

      if (select == 1) {              /* 비트 AND 연산 */   
         printf("input two characters => ");
         scanf("\n%c %c", &a, &b);
         c = a&b; 
         printbit(a);
         printf(" AND ");
         printbit(b);
         printf(" = ");
         printbit(c);
      } else if (select == 2) {        /* 비트 OR 연산 */ 
         printf("input two characters => ");
         scanf("\n%c %c", &a, &b);
         c = a|b; 
         printbit(a);
         printf(" OR ");
         printbit(b);
         printf(" = ");
         printbit(c);
      } else if (select == 3) {       /* 비트 XOR 연산 */   
         printf("input two characters => ");
         scanf("\n%c %c", &a, &b);
         c = a^b;
         printbit(a);
         printf(" XOR ");
         printbit(b);
         printf(" = ");
         printbit(c);
      } else if (select == 4) {       /* 종료 */        
         break;
      } else {                    /* 잘못된 선택 */   
         printf("select error\n");
      }
   }
}

void printbit(char ch)    /* ch에 저장된 8비트의 내용을 2진 코드로 출력 */   
{
   int i;
 
   for (i=0; i<8; i++) {
      printf("%d", (ch&0200) ? 1 : 0);   /* ch의 가장 좌측에 있는 비트를 출력 */
      ch = ch<<1;   /* 1비트 죄측으로 시프트 */
   }
}
