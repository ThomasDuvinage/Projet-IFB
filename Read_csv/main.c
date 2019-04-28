#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BSIZE 80

int main()
{
	char filename[] = "main.csv";
	char buffer[BSIZE];
	FILE *f;
	char *field;
	int DISPO0,DISPO15,DISPO30,DISPO45;

    int n =8;

	/* open the CSV file */
	f = fopen(filename,"r");
	if( f == NULL)
	{
		printf("Unable to open file '%s'\n",filename);
		exit(1);
	}

	while(fgets(buffer,BSIZE,f))
	{
		/* get year */
		field=strtok(buffer,",");
		DISPO0=atoi(field);

		field=strtok(NULL,",");
		DISPO15=atoi(field);

		field=strtok(NULL,",");
		DISPO30=atof(field);

        field=strtok(NULL,",");
		DISPO45=atof(field);


		/* display the result in the proper format */
		printf("Pour %dh les dispos sont %d -- %d -- %d -- %d\n",n,DISPO0,DISPO15,DISPO30,DISPO45);

        n++;
	}

	/* close file */
	fclose(f);

	return(0);
}
