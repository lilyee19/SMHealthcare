//
//  cal_diets.c
//  Diets for Calorie Diary
//
//  Created by Eunju Cha
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cal_exercise.h"
#include "cal_diets.h"
#include "cal_healthdata.h"

#define MAX_DIETS 100      			// Maximum number of diets
#define MAX_FOOD_NAME_LEN 50		// Maximum length of the name of food


// list of diets 
static Diet diet_list[MAX_DIETS];
static int diet_list_size = 0;

/*
    description : read the information in "diets.txt"
*/

void loadDiets(const char* DIETFILEPATH) {
    FILE *file = fopen(DIETFILEPATH, "r");
    if (file == NULL) {
        printf("There is no file for diets! \n");
        return;
    }

    // ToCode: to read a list of the diets from the given file
    // reading name and calories_intake for every diets by taking 2 elements(s,d) for each diet from diets.txt
    while (fscanf(file, "%s %d", diet_list[diet_list_size].food_name, &diet_list[diet_list_size].calories_intake) == 2) {
		diet_list_size++;  //Increasing diet_list_size since this num is alrelady done
    	
        if (diet_list_size >= MAX_DIETS){
        	break;
		}
    }
    fclose(file);
}

/*
    description : to enter the selected diet and the total calories intake in the health data
    input parameters : health_data - data object to which the selected diet and its calories are added 
    return value : No
    
    operation : 1. provide the options for the diets to be selected
    			2. enter the selected diet and the total calories intake in the health data
*/

void inputDiet(HealthData* health_data) {
    int choice, i;
    health_data->diet_count = 0; //Initialization of diet_count variable in structure HealthData
	health_data->total_calories_intake = 0; //Initialization of total_calories_intake variable in structure HealthData
    
    // ToCode: to provide the options for the diets to be selected
    while (1)
	{
		printf("The list of diets:\n");  //printing out the list of diets taken by diets.txt
		for (i=0; i<diet_list_size; i++)
		{
			printf("%d. %s (%d kcal)\n", i+1, diet_list[i].food_name, diet_list[i].calories_intake); //printing the list of diets with numbering(i+1 since it starts with 1)
		}
		printf("%d. Exit\n", i+1); //option for Exit
    
	// ToCode: to enter the diet to be chosen with exit option
    	printf("Select the desired number: ");
    	scanf("%d", &choice);
    
    	if (choice == 7){ //When user chose option for Exit
    		break;
		}
	
		if (choice < 1 || choice > 7){ //If user put unvalid option
			printf("try again with valid option number\n");
			continue;
		}
		
		else{ //when valid option was chosen
			// ToCode: to enter the selected diet in the health data
			health_data->diet[health_data->diet_count] = diet_list[choice-1]; //put the selected diet(diet_list[choice-1]) in health data structure. [choice -1] since choice number was made with i+1
	
    		// ToCode: to enter the total calories intake in the health data
			health_data->total_calories_intake += diet_list[choice-1].calories_intake; //put the total calories of selected diets(by adding diet_list[choice-1].calories_intake) in health data structure
    		health_data->diet_count++; //Increasing diet_count since this num is alrelady done
    		break;
		}

	}
}

