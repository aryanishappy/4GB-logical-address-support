#include "types.h"
#include "stat.h"
#include "user.h"

int main(void) {
    char* c = sbrk(4096);
    if(c == (char *) -1) {
        printf(1, "Memory allot na ho payi\n");
        exit();
    }

    if(remove_mapping(c)) {
        printf(1, "Mapping could not be modified\n");
        exit();
    }

    printf(1, "Present bit deleted successfully\n");
    printf(1, "Accessing the page to cause page fault...\n");
    if(c[0] == 0) {
        printf(1, "WHAT??\n");
    }
    exit();
}