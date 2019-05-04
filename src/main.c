/**
 * @file main.c
 * @Duvinage Thomas (thomas.duvinage@utbm.fr)
 * @brief 
 * @version 0.1
 * @date 2019-05-04
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "../lib/generate_timetable/generation_timetable.h"
#include "../lib/recherche_salle/recherche_salle.h"
#include "../lib/Validation/validation.h"
#include "../lib/identification/function_identification.h"
#include "../coucou.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>


// ****** MAIN ******
int main() {
    if(identification(nom_pswd) == true){
        printf("BIENVENUE SUR NOTRE PLATFORME \n");
    }
    
    return 0;
}


