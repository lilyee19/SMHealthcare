//
//  cal_healthdata.c
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


/*
    description : enter the exercise and diet history in "health_data.txt" 
    input parameters : health_data - data object in which the selected exercise and diet is stored
    return value : No
    
    operation : 1. save the chosen exercise and total calories burned 
    			2. save the chosen diet and total calories intake 
    			3. save the total remaining calrories
*/

//Function that saves data(history of chosen exercises, diets and calculated calories) in health_data.txt
void saveData(const char* HEALTHFILEPATH, const HealthData* health_data) {
	int i; //variable for for loop
    FILE* file = fopen(HEALTHFILEPATH, "w");
    if (file == NULL) {
        printf("There is no file for health data.\n");
        return;
    }

    // ToCode: to save the chosen exercise and total calories burned 
    fprintf(file, "[Exercises] \n"); //Category for Exercises
    for(i=0;i<health_data->exercise_count;i++)
    {
    	//Put chosen exercise name and final calories burned by that exercise in health_data.txt
    	fprintf(file, "%s - %d kcal\n", health_data->exercises[i].exercise_name, health_data->finalcalofex[i]);  
	}
	 //Put total calories burned by all chosen exercises in health_data.txt
	fprintf(file, "Total calories burned: %d kcal\n", health_data->total_calories_burned);
    
    // ToCode: to save the chosen diet and total calories intake 
    fprintf(file, "\n[Diets] \n"); //Category for Diets
    for(i=0;i<health_data->diet_count;i++)
    {
    	//Put chosen food name and calories taken by that food in health_data.txt 
    	fprintf(file, "%s - %d kcal\n", health_data->diet[i].food_name, health_data->diet[i].calories_intake);  
	}
	//Put total calories intake by all chosen diets in health_data.txt
	fprintf(file, "Total calories intake: %d kcal\n", health_data->total_calories_intake); 
	
    // ToCode: to save the total remaining calrories
    fprintf(file, "\n[Total] \n"); //Category for Total
    //Put Basal metabolic rate in health_data.txt
    fprintf(file, "Basal metabolic rate - %d kcal\n", BASAL_METABOLIC_RATE); 
    //Put the remaining calories in health_data.txt by caculating total_caloreis_intake and Basal_metabolic_rate and total_calories_burned 
    fprintf(file, "The remaining calories - %d kcal\n", (health_data->total_calories_intake)-(BASAL_METABOLIC_RATE)-(health_data->total_calories_burned));
   
    fclose(file);
}

/*
    description : print the history of exercised and diets
    input parameters : health_data - data object in which the history of the exercise and diet is to be printed
    return value : No
    
    operation : 1. print out the saved history of exercises
    			2. print out the saved history of diets
    			3. print out the saved history of calories
*/

//Function that allows users to see the history of exercises, diets and calculated calories and the recommendations matched with each condition
void printHealthData(const HealthData* health_data) {
	int i; //variable for for loop
	
	// ToCode: to print out the saved history of exercises
	printf("=========================== History of Exercise =======================\n");
	for(i=0;i<health_data->exercise_count;i++)
    {
    	//Printing out list of exercises chosen and final calories burned by each exercise
    	printf("Exercise: %s, Calories burned: %d kcal\n", health_data->exercises[i].exercise_name, health_data->finalcalofex[i]); 
	}
    printf("=======================================================================\n");

    // ToCode: to print out the saved history of diets
    printf("============================= History of Diet =========================\n");
    for(i=0;i<health_data->diet_count;i++)
    {
    	//Printing out list of diets chosen and calories intake by each diet
    	printf("Food: %s, Calories intake: %d kcal\n", health_data->diet[i].food_name, health_data->diet[i].calories_intake); 
	}
    printf("=======================================================================\n");

	// ToCode: to print out the saved history of calories including basal metabolic rate, 
	// total calories burned, total calories intake, and the remaining calories
	printf("============================== Total Calories =========================\n");
	//Printing out Basal Metabolic Rate
	printf("Basal Metabolic Rate: %d kcal\n", BASAL_METABOLIC_RATE); 
	//Printing out Total Calories Burned by adding all chosen exercises' final burned calories
	printf("Total calories burned: %d kcal\n", health_data->total_calories_burned); 
	//Printing out Total Calories Intake by adding all chosen diets' calories
	printf("Total calories intake: %d kcal\n", health_data->total_calories_intake); 
	//Printing out the ramaining calories by calculating total_caloreis_intake and Basal_Metabolic_Rate and total_calories_burned 
	printf("The remaining calories: %d kcal\n", (health_data->total_calories_intake)-(BASAL_METABOLIC_RATE)-(health_data->total_calories_burned));
    		
	// ToCode: to print out the recommendation depending on the current total calories burned and intake    
	printf("=======================================================================\n");
	//When remaining calorie = 0
	if((health_data->total_calories_intake)-(BASAL_METABOLIC_RATE)-(health_data->total_calories_burned) == 0){ 
		printf("\nYou have consumed all your calories for today!"); //recommendation for remaining calorie = 0

	//When remaining calories < 0
	}else if ((health_data->total_calories_intake)-(BASAL_METABOLIC_RATE)-(health_data->total_calories_burned) < 0){ 
		printf("\n[Warning]Too few calories!\n"); //recommendation for remaining calories < 0
		// When calories intake == Daily Calorie goal
		if ((health_data->total_calories_intake)==(DAILY_CALORIE_GOAL)){ 
			printf("Your total calorie intake for today has reached your goal!"); //recommendation for calories intake == Daily Calorie goal
		// When calories intake < Daily Calorie goal
		}else if((health_data->total_calories_intake)<(DAILY_CALORIE_GOAL)){ 
			printf("Your total calorie intake for today has not reached your goal, remember to eat more!"); //recommendation for calories intake < Daily Calorie goal
		// When calories intake > Daily Calorie goal
		}else{ 
			printf("You have eaten more calories than planned today, but you have exercised too much!"); //recommendation for calories intake > Daily Calorie goal
		}
	
	//When remaining calories > 0 	
	}else{ 
		printf("\nPlease exercise for your health!\n"); //recommendation for remaining calories > 0
		// When calories intake == Daily Calorie goal
		if ((health_data->total_calories_intake)==(DAILY_CALORIE_GOAL)){
			printf("Your total calorie intake for today has reached your goal!"); //recommendation for calories intake == Daily Calorie goal
		// When calories intake < Daily Calorie goal
		}else if((health_data->total_calories_intake)<(DAILY_CALORIE_GOAL)){
			printf("Your total calorie intake for today has not reached your goal, remember to eat more!"); //recommendation for calories intake < Daily Calorie goal
		}
	}
}
