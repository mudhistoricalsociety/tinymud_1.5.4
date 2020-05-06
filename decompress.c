#include <stdio.h>

const char *uncompress(const char *s);

int main()
{
    char buf[16384];

    while(gets(buf)) {
	puts(uncompress(buf));
    }
    return 0;
}
