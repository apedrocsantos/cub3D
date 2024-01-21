#include "libft.h"

int ft_isspace(int c)
{
    if (c && ft_strchr(" \t\n\v\f\r", c))
        return (1);
    return (0);
}