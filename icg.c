#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

char in[25], post[25], stack[25], st[25][25], three[10][10], u[5];
int i, s, p, r, item, top, b, th = 0, tr = 0;

// Function to assign precedence
int pre(char t) {
    int r;
    if ((t == '+') || (t == '-'))
        r = 1;
    else if ((t == '*') || (t == '/'))
        r = 2;
    else if (t == '^')
        r = 3;
    else if ((t == '(') || (t == ')'))
        r = 0;
    return r;
}

int main() {
    int j, k, q, a, b;
    char *buff;
    r = 1;

    printf("\t\tOUTPUT\n");
    printf("\n");
    printf("Enter the expression: \n");
    scanf("%s", in);

    s = 1;
    p = 0;
    stack[0] = '(';

    for (i = 0; in[i] != '\0'; i++) {
        // If operand, add to postfix
        if ((in[i] != '+') && (in[i] != '*') && (in[i] != '/') && (in[i] != '^') && (in[i] != '(') && (in[i] != ')')) {
            post[p] = in[i];
            p++;
        } else {
            // If left parenthesis, push to stack
            if (in[i] == '(') {
                stack[s] = in[i];
                s++;
            } else if (in[i] == ')') {
                // Pop until left parenthesis
                while (stack[s - 1] != '(') {
                    post[p] = stack[s - 1];
                    s--;
                    p++;
                }
                s--;  // Discard '('
            } else {
                // Operator precedence check
                a = pre(in[i]);
                b = pre(stack[s - 1]);
                j = p;
                while (a <= b) {
                    post[p] = stack[s - 1];
                    stack[s - 1] = ' ';
                    s--;
                    j++;
                    p = j;
                    b = pre(stack[s - 1]);
                }
                stack[s] = in[i];
                s++;
            }
        }
    }

    // Pop remaining stack items
    for (i = s - 1; i > 0; i--) {
        if (stack[i] != '(') {
            post[p] = stack[i];
            p++;
        }
    }

    // Null-terminate the postfix expression
    post[p] = '\0';

    // Output postfix
    printf("\n\nThe postfix notation for the given expression:\n\n");
    for (p = 0; post[p] != '\0'; p++)
        printf("%c", post[p]);

    // Generate three-address code
    printf("\n\nThree-address code:\n\n");
    top = 0;

    for (p = 0; post[p] != '\0'; p++) {
        if ((post[p] != '+') && (post[p] != '-') && (post[p] != '*') && (post[p] != '/') && (post[p] != '^')) {
            st[top][0] = post[p];
            st[top][1] = '\0';
            top++;
        } else {
            printf("t%d = %s %c %s\n", tr, st[top - 2], post[p], st[top - 1]);
            top--;
            top--;
            snprintf(u, sizeof(u), "%d", tr);
            strcpy(st[top], "t");
            strcat(st[top], u);
            tr++;
            top++;
        }
    }

    return 0;
}
