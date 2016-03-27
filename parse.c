/*
 * parse.c
 *
 *  Created on: 17 mar 2016
 *      Author: piternet
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"
#include "parse.h"

void printAmountOfDiseases() {
	fprintf(stderr, "DESCRIPTIONS: %d\n", amountOfDiseases);
}

void parseLine(char buffer[], int parametr) {
	char *command = strtok(buffer, " "); // first word in the line, which indicates what operation needs to be done
	if(strcmp(command, NEW_DISEASE_ENTER_DESCRIPTION) == 0) {
		char *name = strtok(NULL, " ");
		char *diseaseDescription = strtok(NULL, ""); // just the rest of buffer, i.e. description of the disease
		if(addNewDiseaseDescription(name, diseaseDescription) == 0) {
			printf("%s", CMD_DONE);
		}
		else {
			printf("%s", CMD_IGNORED);
		}
		//printf("%s choruje na chorobe: %s", name, diseaseDescription);
	}
	else if (strcmp(command, NEW_DISEASE_COPY_DESCRIPTION) == 0) {
		char *name1 = strtok(NULL, " "), *name2 = strtok(NULL, "");
		if(copyDiseaseDescription(name1, name2) == 0) {
			printf("%s", CMD_DONE);
		}
		else {
			printf("%s", CMD_IGNORED);
		}
		//printf("kopiuje od %s do %s ", name2, name1);
	}
	else if(strcmp(command, CHANGE_DESCRIPTION) == 0) {
		char *name = strtok(NULL, " "), *chNumOfDisease = strtok(NULL, " ");
		char *diseaseDescription = strtok(NULL, ""); // just the rest of buffer, i.e. description of the disease
		//printf("zmieniam ziomkowi %s chorobe nr %s na %s", name, chNumOfDisease, diseaseDescription);
		int numOfDisease = atoi(chNumOfDisease);
		if(changeDiseaseDescription(name, numOfDisease, diseaseDescription) == 0) {
			printf("%s", CMD_DONE);
		}
		else {
			printf("%s", CMD_IGNORED);
		}
	}
	else if(strcmp(command, PRINT_DESCRIPTION) == 0) {
		char *name = strtok(NULL, " "), *chNumOfDisease = strtok(NULL, "");
		int numOfDisease = atoi(chNumOfDisease);
		const char *patientDescription = getPatientDescription(name, numOfDisease);
		if(patientDescription == NULL) {
			printf("%s", CMD_IGNORED);
		}
		else {
			printf("%s", patientDescription);
		}
	}
	else if(strcmp(command, DELETE_PATIENT_DATA) == 0) {
		char *name = strtok(NULL, "");
		if(deletePatient(name) == 0) {
			printf("%s", CMD_DONE);
		}
		else {
			printf("%s", CMD_IGNORED);
		}
		//printf("usuwam ziomka o imieniu %s", name);
	}
	else {
		printf("UNKNOWN COMMAND");
	}
	printf("\n");
	if(parametr == 1) {
		printAmountOfDiseases();
	}
}

void getInput(int parametr) {
	int i = 0; // iterator for buffer
	char buffer[MAX_BUFF_SIZE];
	char c;
	while((c = getchar()) != EOF) {
		if(c == EOL) {
			if(i != 0) { // check if it's not just EOL - then nothing to happen
				buffer[i] = '\0'; // terminates string
				parseLine(buffer, parametr);
				memset(buffer, 0, sizeof(buffer)); // clears buffer
				i = 0; // sets iterator for buffer to 0
			}
		}
		else {
			buffer[i++] = c;
		}
	}
}
