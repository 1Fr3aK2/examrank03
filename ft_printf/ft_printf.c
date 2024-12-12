#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

#define FLAGS "sdx"

static void ft_putstr(char *str, int *counter)
{
    if (!str)
    {
        write(1, "(null)", 6);
        *counter += 6;
        return ;
    }
    while (*str)
    {
        write(1, str++, 1);
        (*counter)++;
    }
}

static void ft_putnbr(long int nb, int *counter)
{
    if (nb < 0)
    {
        write(1, "-", 1);
        (*counter)++;
        nb = -nb;
        ft_putnbr(nb, counter);
    }
    else if (nb <= 9)
    {
        char nbr = nb + 48;
        write(1, &nbr, 1);
        (*counter)++;
    }
    else
    {
        ft_putnbr(nb / 10, counter);
        ft_putnbr(nb % 10, counter);
    }
}

static void ft_putnbr_x(unsigned int nb, int *counter)
{
    char *symbols = "0123456789abcdef";

    if (nb < 16)
    {
        write(1, &symbols[nb], 1);
        (*counter)++;
    }
    else
    {
        ft_putnbr_x(nb / 16, counter);
        ft_putnbr_x(nb % 16, counter);
    }
}

static int printf_format(char c, va_list *ap)
{
    int chars;
    chars = 0;
    if (c == 's')
        ft_putstr(va_arg(*ap, char *), &chars);
    if (c == 'd')
        ft_putnbr((va_arg(*ap, int)), &chars);    
    if (c == 'x')
        ft_putnbr_x(va_arg(*ap, unsigned int), &chars);
    return (chars);
}

static int verify(char *str, char c)
{
    while (*str)
    {
        if (*str == c)
            return (1);
        str++;
    }
    return (0);
}


int	ft_printf(const char *str, ...)
{
    va_list ap;
    int counter;

    if (!str)
        return (-1);
    va_start(ap, str);
    counter = 0;
    while(*str)
    {
        if (*str == '%')
        {
            if (verify(FLAGS, *(str + 1)) == 1)
            {
                str++;
                counter += printf_format(*str, &ap);
            }
            else if (*(str + 1) == '\0')
                return (-1);
        }
        else
            counter += write(1, str, 1);
        str++;
    }
    va_end(ap);
    return (counter);
}
