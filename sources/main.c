
#include "../includes/ft_printf.h"

int ft_printf(char * format, ...);

int main()//int ac, char **av)
{
  char c = 't';
  int l[100];
  //ft_printf("%c %s %% ", 't', "strint");
//   printf("%10.10000d\n", 10);
//    printf("%10.10f\n", 10.10);
//     printf("%10.10ld\n", 99999999999);
//      printf("%10.10s\n", "asdfasfasfasfasfasdfasdf");
//  ft_printf("%1000000c\n", &c);

    // fix it !
//     double  n;
//     n = 1.5;
//     long temp;
//     temp = n;
//     printf("%f\n", (n - temp) * pow(10.0, 6.0));
// // (n - n * 1.0) * pow(10, 6)

//     printf("%d", (int)(n / 1)); //10000000000000000000.0000000000000000001
    // printf("this %19.19f float", 10000000000000000000.0000000000000000001);

    // printf("this %.19f float\n", 0.1234567891234567891);
    // ft_printf("this %.19f float\n", 0.1234567891234567891);
    // printf("pow(10.0, 19) = %f", pow(10.0, 19));


    printf("%f\n", 0.000039);
    ft_printf("%f", 0.000039);
    
    // ft_printf("this %19.19f float", 0.0000000000000000001);

// int i = 0;

    //printf("%ull\n %ull\n", rounding(9239999, 6), rounding(9240000, 6));

    // printf("%.20f\n",        1.025978542436587568678);
    //  printf("%.20f\n",        1.025978542436587568678);
    // ft_printf("%.20f\n",        1.025978542436587568678);
    //   ft_printf("%.20f\n",        1.025978542436587568678);

    //   printf("%.18f\n",        0.125978548534310421);
    //  printf("%.20f\n",        0.125978548534310421);
    // ft_printf("%.18f\n",        0.125978548534310421);
    //   ft_printf("%.19f\n",        0.125978548534310421);

  // printf("%#.5o", 21);
  // ft_printf("%#.5o", 21);
  // ft_printf("%5\n");
  // ft_printf("%-5\n");
  // ft_printf("%05\n");
  // ft_printf("%999\n");

  //ft_printf("%");

    // printf("1 %10s\n", NULL);
    // printf("2 %09s\n", NULL);
    // printf("3 %-7s\n", NULL);
    // printf("4 %+3s\n", NULL);
    // printf("5 % 12s\n", NULL);
    // printf("6 %#13s\n", NULL);
    // printf("7 %033s\n", NULL);
    // printf("8 %+-6s\n", NULL);
    // printf("9 % #9s\n", NULL);
    // printf("10 %0-10s\n", NULL);
    // printf("11 %+021s\n", NULL);
    // printf("12 %#-23s\n", NULL);
    // printf("13 %#13.0s\n", NULL);
    // printf("14 %033.109s\n", NULL);
    // printf("15 %+-6.8s\n", NULL);
    // printf("16 % #9.2s\n", NULL);
    // printf("17 %0-10.3s\n", NULL);
    // printf("18 %+021.6s\n", NULL);
    // printf("19 %#-23.s\n", NULL);

  //printf("---");
  // while (i < 100)
  // {
  //   printf("%p ", &l[i]);
  //   ++i;
  // // }
  //   printf("%p\n", &c);

  //ft_printf("%-2c%-3c%-4c%-1c%-2c%-3c", c, c, c, c, c, c);
  // printf("%+5c\n", c);
  // ft_printf("%-5c\n", c);
  // ft_printf("%+5c\n", c);
  //ft_printf(%-5c);("%1c%2c%3c%4c%1c%2c%3c%4c%1c%2c%3c%4c%1c%2c%3c%4c%1c%2c%3c%4c%1c%2c%3c%4c%1c%2c%3c%4c%1c%2c%3c%4c%1c%2c%3c%4c%1c", c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c);
  //ft_printf("c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c);
//   ft_printf("1 %10c\n", c);
//   ft_printf("2 %09c\n", c);
//   ft_printf("3 %-7c\n", c);
//   ft_printf("4 %+3c\n", c);
//   ft_printf("5 % 12c\n", c);
//   ft_printf("6 %#13c\n", c);
//   ft_printf("7 %033c\n", c);
//   ft_printf("8 %+-6c\n", c);
//   ft_printf("9 % #9c\n", c);
//   ft_printf("10 %0-10c\n", c);
//   ft_printf("11 %+021c\n", c);
//   ft_printf("12 %#-23c\n", c);

  return 0;
}