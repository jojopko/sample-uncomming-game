#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    char *str;
    str = "asd";
    // str = "$$$/" argv[0];
    str = strcat( str, "asdas" );

    printf("%s", str);

    return 0;
}