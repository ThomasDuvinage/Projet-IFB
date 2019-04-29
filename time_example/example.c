#include <stdio.h>
#include <time.h>

int main(void)
{
    time_t secondes;
    struct tm instant;

    time(&secondes);
    instant=*localtime(&secondes);
    //on affiche le jour et l'heure
    printf("%d/%d ; %d:%d:%d\n", instant.tm_mday+1, instant.tm_mon+1, instant.tm_hour, instant.tm_min, instant.tm_sec);

    char format[128];
    time_t temps;
    struct tm date;

    // On récupère la date et l'heure actuelles.
    time(&temps);
    date=*localtime(&temps);

    // On remplit la chaîne avec le format choisi, puis on l'affiche.
    strftime(format, 128, "%A", &date);
    puts(format);
    return 0;
}

