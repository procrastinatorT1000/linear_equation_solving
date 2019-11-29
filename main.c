#include "stdio.h"
#include "string.h"
#include "ctype.h"
#include "stdbool.h"
#include <stdarg.h>

int is_unknown( char symb )
{
    if( symb == 'x' || symb == 'X' )
        return true;
    else
        return false;
}

int is_space( char symb )
{
    if( symb == ' ' )
        return true;
    else
        return false;
}

int is_action( char symb )
{
    if( symb == '+' || symb == '-' ||
        symb == '*' || symb == '/' ||
        symb == '=' )
        return true;
    else
        return false;
}

char *check_unknown_and_equality_symb( char *str )
{
    char buf[100] = {0};
    int buf_idx = 0;
    int sign = 1;
    int i = 0;

    for( i = 0; i < strlen(str); i++ )
    {
        if( is_unknown(str[i]) ||
            str[i] == ' ' || str[i] == '*' )
        {
            /* move pointer */
        }
        else if( str[i] == '=' )
        {
            i++; /* next character */
            break;
        }
        else
        {
            printf("Format error-> [%s]\n", str + i );
            break;
        }

    }

    return &str[i];
}

char *get_number( char *str, float *num )
{
    char buf[100] = {0};
    int buf_idx = 0;
    int sign = 1;
    int i = 0;

    for( i = 0; i < strlen(str); i++ )
    {
        if( isdigit(str[i]) || str[i] == '.' ) /* fractional */
        {
            // printf("digit\n");
            buf[buf_idx++] = str[i];
        }
        else if( is_action(str[i]) || str[i] == ' ' ) /* separator of number*/
        {
            printf("sign\n");

            if( buf_idx == 0 )  /* symbol is sign of number */
            {
                if( str[i] == '-' )
                {
                    sign = -1;
                }
                else if( str[i] == '+' )
                {
                    sign = 1;
                }
            }
            else    /* buffer contain number, scan it */
            {
                break;
            }

        }
        else
        {
            printf("Format error-> [%s]\n", str + i );
            break;
        }

    }
    printf("scan: %s\n", buf);
    sscanf( buf, "%f", num );
    *num *= sign;

    return &str[i];
}

int parse_equation( char* eq, float *a, float *b, float *c )
{
    //equation of this form: a + b*x = c
    // x = (c - a) / b
    char *work_ptr = NULL;

    printf( "The equation: [%s]\n", eq );

    
    work_ptr = get_number( eq, a );

    printf("work: %s\n",  work_ptr);

    work_ptr = get_number( work_ptr, b );

    printf("work: %s\n",  work_ptr);

    work_ptr = check_unknown_and_equality_symb( work_ptr );

    printf("work: %s\n",  work_ptr);

    work_ptr = get_number( work_ptr, c );

    printf("work: %s\n",  work_ptr);

    printf("values: a=%f, b=%f, c=%f\n", *a, *b, *c);

    return 1;
}

int solve_equation( float a, float b, float c )
{
    float x = 0;

    if( b != 0 )
    {
        x = (c - a) / b;

        printf("The root of equation\n");
        printf("X = %f\n", x);
    }
    else
    {
        printf("Some error. b can't be zero\n");
    }

    return 1;
}

void print_help()
{
    printf( "Help: Input the equation like this: 45.5+7*x=12\n" );
}


int main( int argc, char* argv[] )
{
    if(argc != 2)
    {
        print_help();
    }
    else
    {
        float a, b, c = 0;
        parse_equation( argv[1], &a, &b, &c );

        solve_equation( a, b, c );
    }

return 1;
}
