# main for ft_printf test about bonus params 

#include "includes/ft_printf.h"
#include <stdio.h> 
int ft_printf(char * format, ...);

int main()//int ac, char **av)
{
// Test print non printable symbols (-r) 
// int d = 0;
// while (d < 32)
//   ft_printf("%r", d++);


// Test print bits symbols (-b) 
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


// Test -e flag 
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


// Test * argument 
// printf("%*.*d\n",100, 10, -2);


// Test text color
// ft_printf(RED "Красный Текст\n");
// ft_printf(GREEN "Зеленый Текст\n");
// ft_printf(BLUE "Синий Текст\n");


// Test background color
// ft_printf(CYAN_B "Сине-зелёный фон\n");
// ft_printf(PURPLE_B "Пурпурный фон\n");
// ft_printf(BROWN_B "Коричневый фон\n");

// Test font type
// ft_printf(UNDERLINED "Подчеркнутый текст\n");
// ft_printf(FLASHING "Мерцающий текст\n");
// ft_printf(INVERSION "Инверсия текста\n");

// Test mix 
// ft_printf(UNDERLINED RED_B PURPLE  "Текст разных цветов и стилей\n");
// ft_printf(FLASHING RED GREEN_B "Текст разных цветов и стилей\n");
// ft_printf(BOLD  LIGRAY_B BLUE "Текст разных цветов и стилей\n");

  return 0;
}
