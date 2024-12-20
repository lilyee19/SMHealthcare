//
//  cal_healthdata.c
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


/*
    description : enter the exercise and diet history in "health_data.txt" 
    input parameters : health_data - data object in which the selected exercise and diet is stored
    return value : No
    
    operation : 1. save the chosen exercise and total calories burned 
    			2. save the chosen diet and total calories intake 
    			3. save the total remaining calrories
*/

void saveData(const char* HEALTHFILEPATH, const HealthData* health_data) {
	int i;
    FILE* file = fopen(HEALTHFILEPATH, "w");
    if (file == NULL) {
        printf("There is no file for health data.\n");
        return;
    }

    // ToCode: to save the chosen exercise and total calories burned 
    fprintf(file, "[Exercises] \n"); //category for Exercises
    for(i=0;i<health_data->exercise_count;i++)
    {
    	fprintf(file, "%s - %d kcal\n", health_data->exercises[i].exercise_name, health_data->finalcalofex[i]); //put chosen exercise name and calories burned by exercise in health_data.txt 
	}
	fprintf(file, "Total calories burned - %d kcal\n", health_data->total_calories_burned); //put total calories burned by exercises in health_data.txt
    
    // ToCode: to save the chosen diet and total calories intake 
    fprintf(file, "\n[Diets] \n"); //category for Diets
    for(i=0;i<health_data->diet_count;i++)
    {
    	fprintf(file, "%s - %d kcal\n", health_data->diet[i].food_name, health_data->diet[i].calories_intake);  //put chosen food name and calories taken by diet in health_data.txt 
	}
	fprintf(file, "Total calories intake - %d kcal\n", health_data->total_calories_intake); //put total calories intake by diets in health_data.txt
	
    // ToCode: to save the total remaining calrories
    fprintf(file, "\n[Total] \n"); //category for Total
    fprintf(file, "Basal metabolic rate - %d kcal\n", BASAL_METABOLIC_RATE); //put Basal metabolic rate in health_data.txt
    //put the remaining calories by caculating total_caloreis_intake and Basal metabolic rate and total_calories_burned in health_data.txt
    fprintf(file, "The remaining calories - %d kcal\n", (health_data->total_calories_intake)-(BASAL_METABOLIC_RATE)-(health_data->total_calories_burned));
   
    fclose(file);
    printf("success \n");
}

/*
    description : print the history of exercised and diets
    input parameters : health_data - data object in which the history of the exercise and diet is to be printed
    return value : No
    
    operation : 1. print out the saved history of exercises
    			2. print out the saved history of diets
    			3. print out the saved history of calories
*/

void printHealthData(const HealthData* health_data) {
	int i;
	
	// ToCode: to print out the saved history of exercises
	printf("=========================== History of Exercise =======================\n");
	for(i=0;i<health_data->exercise_count;i++)
    {
    	printf("Exercise: %s, Calories burned: %d kcal\n", health_data->exercises[i].exercise_name, health_data->finalcalofex[i]); //printing out exercises chosen and final calories burned by each exercise
	}
    printf("=======================================================================\n");

    // ToCode: to print out the saved history of diets
    printf("============================= History of Diet =========================\n");
    for(i=0;i<health_data->diet_count;i++)
    {
    	printf("Food: %s, Calories intake: %d kcal\n", health_data->diet[i].food_name, health_data->diet[i].calories_intake); //printing out diets chosen and calories intake by each diet
	}
    printf("=======================================================================\n");

	// ToCode: to print out the saved history of calories including basal metabolic rate, 
	// total calories burned, total calories intake, and the remaining calories
	printf("============================== Total Calories =========================\n");
	printf("Basal Metabolic Rate: %d kcal\n", BASAL_METABOLIC_RATE); //printing out Basal Metabolic Rate
	printf("Total calories burned: %d kcal\n", health_data->total_calories_burned); //printing out total calories burned by adding all chosen exercises' final burned calories
	printf("Total calories intake: %d kcal\n", health_data->total_calories_intake); //printing out total calories intake by adding all chosen diets' calories
	//printing out the ramaining calories by calculating total_caloreis_intake and Basal metabolic rate and total_calories_burned 
	printf("The remaining calories: %d kcal\n", (health_data->total_calories_intake)-(BASAL_METABOLIC_RATE)-(health_data->total_calories_burned));
    printf("=======================================================================\n \n");
    
	
	// ToCode: to print out the recommendtaion depending on the current total calories burned and intake    
	printf("=======================================================================\n");
}
