# ft_printf

During this project I learnt about representation of floating point numbers in a computer
and how printf function works.

# Usage

	make
	gcc <file.c> libftprintf.a libft/libft.a -I libft/ -I ./

You are supposed to call ft_printf function from <file.c>. In order to get rid of warnings
prototype:

	#include "ft_printf.h"

at the top of <file.c>

**Conversions and flags that has been managed in ft_printf:** 

- Conversions: `s`, `p`, `d`, `i`, `o`, `u`, `x`&`c` with flags:
- `hh`, `h`, `l`, `ll`.
- `%%`
- flags: `#`, `0`, `-`, `+` & `space`
- minimum field-width
- precision
