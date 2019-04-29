#include <stdio.h>
#include <time.h>

int main(void)
{
    time_t secondes;
    struct tm instant;

    time(&secondes);
    instant=*localtime(&secondes);

    printf("%d/%d ; %d:%d:%d\n", instant.tm_mday+1, instant.tm_mon+1, instant.tm_hour, instant.tm_min, instant.tm_sec);
    return 0;
}

