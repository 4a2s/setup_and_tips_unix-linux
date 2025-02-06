#include "../../include/my_zsh.h"

int my_getnbr(char const *str)
{
    int my_case = 0;
    long res = 0;
    int sign = 1;

    for (; str[my_case] == '-' || str[my_case] == '+'; my_case++)
        if (str[my_case] == '-')
            sign = sign * -1;
    for (; str[my_case] >= '0' && str[my_case] <= '9'; my_case++) {
        res = res * 10 + (str[my_case] - '0');
        if (res * sign > 2147483647 || res * sign < -2147483648)
            return 0;
    }
    return (int)(res * sign);
}
