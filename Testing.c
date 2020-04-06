#include <stdio.h>
#include <string.h>

int main()
{
    int i = 12345;
    char buf[100];
    char name[100] = "Hammer";

    printf("i is %d\n", i);
    snprintf(buf, sizeof(buf), "%d", i);
    printf("buf is now: %s\n", buf);
    
    strcat(name, buf);
    printf("%s\n", name);

    return 0;
}