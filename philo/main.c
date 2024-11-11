
#include "philo.h"

int main(int argc, char *argv[])
{
    t_table table;

    if (argc == 5 || argc == 6)
    {
        if (parser(&table, argv) == -1)
            return (-1);
        

        // creating everything
        //  looping
        //  clean if 1 philo dies or everyone is full
    }
    else
        error_handling(NULL, "wrong number of arguments");
    return (0);
}

// might have to implement return statements to the main function as exit is not allowed
