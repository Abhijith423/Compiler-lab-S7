// Experiment 3

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char ip_sym[15], stack[15];
int ip_ptr = 0, st_ptr = 0, len;

char temp[2], temp2[2];
char act[15];

void check();

int main()
{
    int i;

    printf("\n\t\tSHIFT REDUCE PARSER\n");

    printf("\nGRAMMAR\n");
    printf("\nE -> E+E\nE -> E/E\nE -> E*E\nE -> a/b\n");

    printf("\nEnter the input symbol: ");
    gets(ip_sym); // Unsafe, but kept as in original

    printf("\n\tStack Implementation Table");
    printf("\nStack\t\tInput Symbol\t\tAction");
    printf("\n----------------------------------------------");

    printf("\n$\t\t%s$\t\t--", ip_sym);

    strcpy(act, "shift");
    temp[0] = ip_sym[ip_ptr];
    temp[1] = '\0';
    strcat(act, temp);
    len = strlen(ip_sym);

    for (i = 0; i < len; i++)
    {
        stack[st_ptr] = ip_sym[ip_ptr];
        stack[st_ptr + 1] = '\0';

        ip_sym[ip_ptr] = ' ';
        ip_ptr++;

        printf("\n$%s\t\t%s$\t\t%s", stack, ip_sym, act);

        strcpy(act, "shift");
        temp[0] = ip_sym[ip_ptr];
        temp[1] = '\0';
        strcat(act, temp);

        check();
        st_ptr++;
    }

    st_ptr++;
    check();

    return 0;
}

void check()
{
    char temp_stack[15];

    // Reduce E -> a or b
    temp2[0] = stack[st_ptr];
    temp2[1] = '\0';

    if ((!strcmp(temp2, "a")) || (!strcmp(temp2, "b")))
    {
        stack[st_ptr] = 'E';
        stack[st_ptr + 1] = '\0';
        printf("\n$%s\t\t%s$\t\tE->%s", stack, ip_sym, temp2);
    }

    // Reduce E->E+E or E*E or E/E
    while (st_ptr >= 2)
    {
        temp_stack[0] = stack[st_ptr - 2];
        temp_stack[1] = stack[st_ptr - 1];
        temp_stack[2] = stack[st_ptr];
        temp_stack[3] = '\0';

        if (!strcmp(temp_stack, "E+E") || !strcmp(temp_stack, "E*E") || !strcmp(temp_stack, "E/E"))
        {
            stack[st_ptr - 2] = 'E';
            stack[st_ptr - 1] = '\0';
            stack[st_ptr] = '\0';
            st_ptr -= 2;
            printf("\n$%s\t\t%s$\t\tE->%s", stack, ip_sym, temp_stack);
        }
        else
        {
            break;
        }
    }
}
