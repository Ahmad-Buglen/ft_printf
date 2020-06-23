
#include "../includes/ft_printf.h"

int ft_printf(char * format, ...);

int main()//int ac, char **av)
{
  // char a = 0;
  // while (a < 41)
   // printf("%.0p, %.p\n", 0, 0);
  // printf("%.p, %.0p\n", 0, 0);
  // ft_printf("%.0p, %.p\n", 0, 0);
  // ft_printf("%.p, %.0p\n", 0, 0);
  //  printf("%d", SHRT_MAX );
  // printf("%hhu / %hhu\n", SHRT_MAX - 42, SHRT_MAX - 4200);
  // ft_printf("%hhu / %hhu", SHRT_MAX - 42, SHRT_MAX - 4200);
  
  // int i = 0;
  // while(++i < 1000)
  //   printf("%llu ", ft_pow(10, i));
  // printf("this %f float", 1.5);
  // ft_printf("{%f}{%lf}{%Lf}", 1.42, 1.42, 1.42l);
  // ft_printf("{%f}{%lf}{%Lf}", -1.42, -1.42, -1.42l);
  // ft_printf("{%f}{%lf}{%Lf}", 1444565444646.6465424242242, 1444565444646.6465424242242, 1444565444646.6465424242242l);
    // ft_printf("{%f}{%lf}{%Lf}", -1444565444646.6465424242242454654, -1444565444646.6465424242242454654, -1444565444646.6465424242242454654l);
  //     ft_printf

  // char c = 't';
  // int l[100];
  // ft_printf("%.2s", "notall");
  // ft_printf("%u", 878023);
  // printf("%.24lu\n", 0ull);

  // ft_printf("%.24lu", 0ull);
    //   ui_pos_1 = 878023;
    // l_pos_1 = 22337203685477
//  sh_neg_1 = -8875;
//  ull_pos_1 = 22337203685477;
//  ll_neg_1 = -22337203685477;
//  ush_pos_1 = 3047;
    // ul_pos_1 = 22337203685477;

// static char 		ch_pos_1 = 100, ch_neg_1 = -87;
// static short		sh_pos_1 = 3047, sh_neg_1 = -8875;
// static int			i_pos_1 = 878023;
// static long		l_pos_1 = 22337203685477, l_neg_1 = -22337203685477;
// static long long	ll_pos_1 = 22337203685477, ll_neg_1 = -22337203685477;
// static long		lmax	= 9223372036854775807;
// static long		lmin	= -9223372036854775807;
// static long long llmax = 9223372036854775807;
// static long long	llmin = -9223372036854775807ll;
// static unsigned char 		uch_pos_1 = 100;
// static unsigned short		ush_pos_1 = 3047;
// static unsigned int		ui_pos_1 = 878023;
// static unsigned long		ul_pos_1 = 22337203685477;
// static unsigned long long	ull_pos_1 = 22337203685477;
// static unsigned long long  ullmax = 9223372036854775807;
// static unsigned long  		ulmax = 9223372036854775807;
//     printf("%s%hihello%-17.14llu%lli%08hu%s%17ssomestuff%s%hi%i%.24lu%llu%u%.2s%li\n",
//     "abc",sh_neg_1,ull_pos_1,ll_neg_1,ush_pos_1,"wassup","nope","",(short)32767,0,
//     ul_pos_1,0ull,ui_pos_1,"notall",l_pos_1);
//  ft_printf("%s%hihello%-17.14llu%lli%08hu%s%17ssomestuff%s%hi%i%.24lu%llu%u%.2s%li\n",
//     "abc",sh_neg_1,ull_pos_1,ll_neg_1,ush_pos_1,"wassup","nope","",(short)32767,0,
//     ul_pos_1,0ull,ui_pos_1,"notall",l_pos_1);

    // ft_printf("%7i", -14);
    // printf("%s%hihello%-17.14llu%lli%08hu%s%17ssomestuff%s%hi%i%.24lu%llu%u%.2s%li\n",
    // "abc", -8875, 22337203685477, -22337203685477, 3047, "wassup", "nope", "",  (short)32767, 0,
    // 22337203685477, 0ull, 878023 ,"notall", 22337203685477);
//  ft_printf("%s%hihello%-17.14llu%lli%08hu%s%17ssomestuff%s%hi%i%.24lu%llu%u%.2s%li",
//     "abc", -8875,	22337203685477, -22337203685477, 3047, "wassup", "nope", "",  (short)32767, 0, 22337203685477, 0ull, 878023 ,"notall", 22337203685477);
// printf("%.24llu%llu%u%.2s%li", 0ull, 878023ull, "notall", 22337203685477l);
  // ft_printf("%.24lu%llu%u%.2s", 0ull, 878023, "notall"); //, 22337203685477);
  // ft_printf("%.24lu%llu%u%.2s%li", 0ull, 878023, "notall", 22337203685477);

//   printf("%10.10000d\n", 10);
//    printf("%10.10f\n", 10.10);
//     printf("%10.10ld\n", 99999999999);f
//      printf("%10.10s\n", "asdfasfasfasfasfasdfasdf");
//  ft_printf("%1000000c\n", &c);

  // ft_printf("this %f float", 1.5);
    // fix it !
//     double  n;
//     n = 1.5;
//     long temp;
//     temp = n;
//     printf("%f\n", (n - temp) * pow(10.0, 6.0));
// // (n - n * 1.0) * pow(10, 6)

//     printf("%d", (int)(n / 1)); //10000000000000000000.0000000000000000001
    // printf("this %19.19f float", 10000000000000000000.0000000000000000001);

    // printf("0.1234567891234567891 %.19e\n", 0.1234567891234567891);
    // ft_printf("this %.19f float\n", 0.1234567891234567891);
    // printf("pow(10.0, 19) = %e\n", pow(10.0, 19));

    // printf("1 %e\n", 0.0);
    // printf("2 %e\n", 1.0);
    // printf("3 %e\n", -1.0);
    // printf("4 %e\n", -1234567890.0);
    // printf("4.1 %.19e\n", 1234567890.0);
    // printf("5 %.19e\n", -0.000001);
    // printf("6 %.5e\n", -0.123456789);
    // printf("7 %.10e\n", -0.123456789);
    // printf("8 %.15e\n", -0.123456789);
    // printf("9 %.20e\n", -0.123456789);
    // printf("10 %e\n\n", 0.000001);

    // ft_printf("1 %e\n", 0.0);
    // ft_printf("2 %e\n", 1.0);
    // ft_printf("3 %e\n", -1.0);
    // ft_printf("4 %e\n", -1234567890.0);
    // ft_printf("4.1 %.19e\n", 1234567890.0);
    // ft_printf("5 %.19e\n", -0.000001);
    // ft_printf("6 %.5e\n", -0.123456789);
    // ft_printf("7 %.10e\n", -0.123456789);
    // ft_printf("8 %.15e\n", -0.123456789);
    // ft_printf("9 %.20e\n", -0.123456789);
    // ft_printf("10 %e\n", 0.000001);

    // printf(" %.20e\n", -0.123456789);

    // ft_printf("this %d number", 17);




    // ft_printf("this %19.19f float", 0.0000000000000000001);

// int i = 0;
// ft_printf("%x", 4294967296);
// ft_printf("%d\n", 2147483648);
// printf("%*.*d\n",100, 10, -2);
// printf(RED, "Красный Текст\n");



//  ft_printf(UNDERLINED RED_BACK PURPLE  " RED_BACK UNDERLINED BLACK_BACK Текст %d\n", 123456789);
//  ft_printf(NORM BLUE_BACK  "NORM Текст %d\n", 123456789);
//  ft_printf(BOLD  GREEN_BACK "BOLD Текст %d\n", 123456789);
//  ft_printf(FLASHING   "FLASHING Текст %d\n", 123456789);
//  ft_printf(INVERSION   "INVERSION Текст %d\n", 123456789);

//  ft_printf(  "Красный Текст %d", 1);
// ft_printf("%d\n", 2147483647);
    //printf("%ull\n %ull\n", rounding(9239999, 6), rounding(9240000, 6));

    // printf("1.025978542436587568678 %.20e\n", 1.025978542436587568678);
    // printf("1.025978542436587568678 %.20e\n", 1.025978542436587568678);
    // ft_printf("%.20e\n",        1.025978542436587568678);
    // ft_printf("%.20e\n",        1.025978542436587568678);

    // printf("0.125978548534310421 %.18e\n", 0.125978548534310421);
    // printf("0.125978548534310421 %.20e\n", 0.125978548534310421);
    // ft_printf("%.18e\n",        0.125978548534310421);
    // ft_printf("%.19e\n",        0.125978548534310421);

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

  // ft_printf("%-2c%-3c%-4c%-1c%-2c%-3c", c, c, c, c, c, c);
  // printf("%+5c\n", c);
  // ft_printf("%-5c\n", c);
  // ft_printf("%+5c\n", c);
  // ft_printf(%-5c);("%1c%2c%3c%4c%1c%2c%3c%4c%1c%2c%3c%4c%1c%2c%3c%4c%1c%2c%3c%4c%1c%2c%3c%4c%1c%2c%3c%4c%1c%2c%3c%4c%1c%2c%3c%4c%1c", c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c);
  // ft_printf("c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c);
  // ft_printf("1 %10b\n", 1);
  // ft_printf("2 %09b\n", 2);
  // ft_printf("3 %7b\n", 3);
  // ft_printf("4 %3b\n", 4);
  // ft_printf("5 %12b\n", 5);
  // ft_printf("6 %#13b\n", 6);
  // ft_printf("7 %.3b\n", 7);
  // ft_printf("8 %6b\n", 8);
  // ft_printf("9 %9b\n", 9);
  // ft_printf("10 %10b\n", 10);
  // ft_printf("11 %.21b\n", 11);
  // ft_printf("12 %.23b\n", 12);
  // printf(" %o\n", 18446744073709551611l);
  // ft_printf(" %o\n", 18446744073709551611l);
  return 0;
}
