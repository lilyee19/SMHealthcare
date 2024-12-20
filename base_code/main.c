//
//  main.c
//  Calorie Diary
//
//  Created by Eunju Cha
//  Edited by Seoin Jhee

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cal_exercise.h"
#include "cal_diets.h"
#include "cal_healthdata.h"

#define EXERCISEFILEPATH "exercises.txt"
#define DIETFILEPATH "diets.txt"
#define HEALTHFILEPATH "health_data.txt"

static int choice;

int main() {
	// To initialize the health data object
    HealthData health_data = {0};
    
    // Tocode: to read the list of the exercises and diets
    loadExercises(EXERCISEFILEPATH); //reading name and calories_burned_per_minute for every exercises from EXERCISEFILEPATH
    loadDiets(DIETFILEPATH); //reading name and calories_intake for every diets from EXERCISEFILEPATH

    // ToCode: to run the "Healthcare Management Systems" until all calories are used up or the user wants to exit the system
    do {
    	//system exit condition2: when remaining calorie = 0
    	if ((health_data.total_calories_intake)-(BASAL_METABOLIC_RATE)-(health_data.total_calories_burned) == 0 ){ 
            printf("You have consumed all your calories for today! \n"); //recommendation when remaining calorie = 0
            saveData(HEALTHFILEPATH, &health_data); //saving data in health_data.txt
            break; //break from do-while loop since it exit condition2 was made
		}
		//allow user to choose options in Healthcare Management Systems
		else{
			printf("\n=======================================================================\n");
        	printf("[Healthcare Management Systems] \n");
        	printf("1. Exercise \n");
        	printf("2. Diet \n");
        	printf("3. Show logged information \n");
        	printf("4. Exit \n");
        	printf("Select the desired number: ");
        	scanf("%d", &choice);
        	printf("=======================================================================\n");
        }
        
		// ToCode: to run the sysmtem based on the user's choice
        switch (choice) {
            //When user chose Exercise option
			case 1:
            	inputExercise(&health_data); //allow user to choose option and put selected exercises and calories burned in the health data
            	saveData(HEALTHFILEPATH, &health_data); //saving data in health_data.txt
                break;
            //When user chose Diet option    
            case 2:
            	inputDiet(&health_data); //allow user to choose option and put selected diets and calories intake in the health data
            	saveData(HEALTHFILEPATH, &health_data); //saving data in health_data.txt
                break;
            //When user chose Show logged information option    
            case 3:
            	printHealthData(&health_data); //printing out history of exercises and diets and calories and recommendations matched with condition
                break;
            //system exit condition1: when user chose Exit option    
            case 4:
            	saveData(HEALTHFILEPATH, &health_data); //saving data in health_data.txt
    			printf("Exit the system.\n");
    			printf("=======================================================================\n");
                break;
            //When user put invalid option    
            default:
                printf("[Error] Invalid option. \n");
                printf("Please try again! \n");
        }
    } while (choice != 4); //execute do-while loop until user chose Exit option(when met the exit condition1)

    return 0;
}

