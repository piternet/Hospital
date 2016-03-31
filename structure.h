/*
 * structure.h
 *
 *  Created on: 17 mar 2016
 *      Author: piternet
 */

#ifndef STRUCTURE_H_
#define STRUCTURE_H_

typedef struct Disease {
	char *description;
	int refCounter;
} Disease;

typedef struct DiseaseList {
	Disease *disease;
	struct DiseaseList *next;
} DiseaseList;

typedef struct Patient {
	char *name;
	DiseaseList *diseases;
	DiseaseList *lastDisease;
} Patient;

typedef struct PatientList {
	Patient *patient;
	struct PatientList *next;
} PatientList;

extern int amountOfDiseases;

int addNewDiseaseDescription(char[], char[]);
int copyDiseaseDescription(char[], char[]);
int changeDiseaseDescription(char[], int, char[]);
const char* getPatientDescription(char[], int);
int deletePatient(char[]);

void freeMemory();

#endif /* STRUCTURE_H_ */
