#include "../lib/identification/identification.h"
#include "../lib/recherche_salle/recherche_salle.h"
#include "../lib/generate_timetable/generation_timetable.h"
#include "../lib/buffer.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>


// ****** MAIN ******
int main() {

	if (identification()) {
		printf("nombre agent = %d",nombre_agent);
		printf("BIENVENUE SUR NOTRE PLATFORME \n");
	}

	generate();

	return 0;
}

