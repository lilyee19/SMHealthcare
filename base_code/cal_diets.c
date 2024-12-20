//
//  cal_diets.c
//  Diets for Calorie Diary
//
//  Created by Eunju Cha
//  Edited by Seoin Jhee

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

//Function that loads diet data(food_name, calories_intake from DIETFILEPATH)
void loadDiets(const char* DIETFILEPATH) {
    FILE *file = fopen(DIETFILEPATH, "r");
    if (file == NULL) {
        printf("There is no file for diets! \n");
        return;
    }

    // ToCode: to read a list of the diets from the given file
    // Reading food_name and calories_intake for every diets by taking 2 elements(s,d) for each diet from diets.txt
    while (fscanf(file, "%s %d", diet_list[diet_list_size].food_name, &diet_list[diet_list_size].calories_intake) == 2) {
		diet_list_size++;  //Increasing diet_list_size since this num is alrelady done
    	
        if (diet_list_size >= MAX_DIETS){ //When diet_list_size exceeds maximum num of diets
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

//Function that allows user to choose option for diets and puts that chosen diet data in health_data structure)
void inputDiet(HealthData* health_data) {
    int choice, i; //variable for diet option that user chose and for loop
    
    // ToCode: to provide the options for the diets to be selected
    while (1)
	{
		//Printing out the list of diets taken by diets.txt
		printf("The list of diets:\n");  
		for (i=0; i<diet_list_size; i++)
		{
			//printing the list of food_names and calories with numbering(i+1 since numbering starts with 1)
			printf("%d. %s (%d kcal)\n", i+1, diet_list[i].food_name, diet_list[i].calories_intake); 
		}
		printf("%d. Exit\n", i+1); //option for Exit
    
	// ToCode: to enter the diet to be chosen with exit option
    	//Provide user of choosing options
		printf("Choose (1-7): ");
    	scanf("%d", &choice);
    	
    	//When user chose option for Exit
    	if (choice == 7){ 
    		break;
		}
		
		//When user put invalid option
		else if (choice < 1 || choice > 7){ 
			printf("try again with valid option number\n");
			continue;
		}
		
		//When valid option was chosen
		else{ 
			// ToCode: to enter the selected diet in the health_data
			//Put the selected diet(diet_list[choice-1]) in health_data structure. [choice -1] since choice number was made with i+1
			health_data->diet[health_data->diet_count] = diet_list[choice-1]; 
	
    		// ToCode: to enter the total calories intake in the health_data
    		//put the total calories of selected diets(by adding diet_list[choice-1].calories_intake with existing total_calories_intake) in health_data structure
			health_data->total_calories_intake += diet_list[choice-1].calories_intake; 
    		health_data->diet_count++; //Increasing diet_count since this num is alrelady done
    		break;
		}
	}
}

