
#include "philo.h"

void error_handling(char *str, char *error_msg)
{
    printf("Error: ");
    if (str)
        printf("%s: ", str);
    printf("%s\n", error_msg);
}
