#include "types.h"
#include "stat.h"
#include "user.h"

int
main(void)
{
    char *p = sbrk(3 * 4096);
    printf(1, "p = %x\n", p);

    if(p == (char*)-1) {
        printf(1, "sbrk failed\n");
        exit();
    }

    printf(1, "Allocated virtual memory\n");

    p[0] = 'A';
    p[8192] = 'B';

    printf(1, "Values: %c %c\n", p[0], p[8192]);

    int t = fork();
    if(t == -1) {
        printf(1, "Fork failed\n");
        exit();
    }
    else if(t == 0) {
        printf(1, "I am in child\n");
        p[0] = 'A';
        p[8192] = 'B';

        printf(1, "Values: %c %c\n", p[0], p[8192]);
        printf(1, "Addresses: %x %x\n", p, p + 8192);
    }
    else {
        wait();
        printf(1, "I am in parent\n");
        printf(1, "Addresses (P) : %x %x\n", p, p + 8192);

        int t2 = fork();
        if(t2 < 0) {
            printf(1, "Fork 2 failed\n");
            exit();
        }
        else if(t2 == 0) {
            printf(1, "I am in child2\n");
            p[-1] = 'D';
            printf(1, "ho did i access this??\n");
        }
        else {
            wait();
            printf(1, "Done\n");
            p[3 * 4096] = 'D';
        }
    }

    exit();
}