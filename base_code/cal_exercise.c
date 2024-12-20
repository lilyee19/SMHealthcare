//
//  cal_exercise.c
//  Excercise for Calorie Diary
//
//  Created by Eunju Cha
//  Edited by Seoin Jhee

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cal_exercise.h"
#include "cal_diets.h"
#include "cal_healthdata.h"

#define MAX_EXERCISES 100  			// Maximum number of exercises
#define MAX_EXERCISE_NAME_LEN 50	// Maximum length of the name of exercise


// To declare the structure of the exercises
static Exercise exercise_list[MAX_EXERCISES];
int exercise_list_size = 0;


/*
    description : read the information in "excercises.txt"
*/

//Function that loads exercise data(exercise_name, calories_burned_per_minute from EXERCISEFILEPATH)
void loadExercises(const char* EXERCISEFILEPATH) {
    FILE *file = fopen(EXERCISEFILEPATH, "r");
    if (file == NULL) {
        printf("There is no file for exercises! \n");
        return;
    }

    // ToCode: to read a list of the exercises from the given file
    // Reading exercise_name and calories_burned_per_minute for every exercises by taking 2 elements(s,d) for each exercise from exercises.txt
    while (fscanf(file, "%s %d", exercise_list[exercise_list_size].exercise_name, &exercise_list[exercise_list_size].calories_burned_per_minute) == 2) { 
    	exercise_list_size++; //Increasing exercise_list_size since this num is alrelady done
    	
        if (exercise_list_size >= MAX_EXERCISES){ //When exercise_list_size exceeds maximum num of exercise
        	break;
		}
    }
    fclose(file);
}


/*
    description : to enter the selected exercise and the total calories burned in the health data
    input parameters : health_data - data object to which the selected exercise and its calories are added 
    return value : No
    
    operation : 1. provide the options for the exercises to be selected
    			2. enter the duration of the exercise
    			3. enter the selected exercise and the total calories burned in the health data
*/

//Function that allows user to choose option for exercises and puts that chosen exercise data in health_data structure)
void inputExercise(HealthData* health_data) {
    int choice, duration, i; //variable for exercise option that user chose, duration of that exercise, for loop
    
    // ToCode: to provide the options for the exercises to be selected
    while (1)
    {
    	//Printing out the list of exercises taken by exercises.txt
    	printf("The list of exercises: \n"); 
		for (i=0; i<exercise_list_size; i++)
		{
			//printing the list of exercise_names and calories with numbering(i+1 since numbering starts with 1)
			printf("%d. %s (%d kcal burned per min.)\n", i+1, exercise_list[i].exercise_name, exercise_list[i].calories_burned_per_minute); 
		}
		printf("%d. Exit\n", i+1); //option for Exit

    // ToCode: to enter the exercise to be chosen with exit option
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
    		// To enter the duration of the exercise
    		printf("Enter the duration of the exercise (in min.): ");
    		scanf("%d", &duration);

    		// ToCode: to enter the selected exercise and total calcories burned in the health data
    		//Calculate the final burned calories of chosen exercise using variable int finalcalofex which is duration*calories_burned_per_minute. [choice -1] since choice number was made with i+1
    		int finalcalofex = duration * exercise_list[choice-1].calories_burned_per_minute;
    		//Put the final burned calories of chosen exercise in health_data structure using health_data.finalcalofex[health_data.exercise_count] : defined in cal_healthdata.h
			health_data->finalcalofex[health_data->exercise_count] = finalcalofex;
			//Put the selected exercise(exercise_list[choice-1]) in health_data structure. 
			health_data->exercises[health_data->exercise_count] = exercise_list[choice-1];
			//Put the total burned calories caused by selected exercises(by adding final burned calories of each exercise with existing total_calories_burned) in health_data structure
			health_data->total_calories_burned += finalcalofex;
    		health_data->exercise_count++; //Increasing exercise_count since this num is alrelady done
    		break;
		}
	}
}

