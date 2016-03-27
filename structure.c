/*
 * structure.c
 *
 *  Created on: 17 mar 2016
 *      Author: piternet
 */

#include "structure.h"
#include <stdlib.h>
#include <string.h>

PatientList *patientListHead = NULL; // list of all patients
PatientList *lastPatient = NULL; // pointer to last patient
int amountOfDiseases = 0;

PatientList* addPatient(char *name) {
	if(patientListHead == NULL) { // patientList if empty
		patientListHead = (PatientList*) malloc(sizeof(PatientList));
		patientListHead->patient = (Patient*) malloc(sizeof(Patient));
		patientListHead->patient->name = (char*) malloc((strlen(name)+1)*sizeof(char));
		strcpy(patientListHead->patient->name, name);
		patientListHead->patient->diseases = NULL;
		patientListHead->patient->lastDisease = NULL;
		patientListHead->next = NULL;
		lastPatient = patientListHead;
		return patientListHead;
	}
	else {
		PatientList *current = lastPatient;
		// current->next is pointer of our new patient
		current->next = (PatientList*) malloc(sizeof(PatientList));
		current->next->patient = (Patient*) malloc(sizeof(Patient));
		current->next->patient->name = (char*) malloc((strlen(name)+1)*sizeof(char));
		strcpy(current->next->patient->name, name);
		current->next->patient->diseases = NULL;
		current->next->patient->lastDisease = NULL;
		current->next->next = NULL;
		lastPatient = current->next;
		return current->next;
	}
}

PatientList* findPatient(char *name) {
	/* finds if there is patient with given  name
	 returns NULL if not */
	PatientList *ptr = patientListHead;
	while(ptr != NULL) {
		if(strcmp(ptr->patient->name, name) == 0)
			return ptr;
		ptr = ptr->next;
	}
	return NULL;
}

/*void printAllDiseases(Patient *patient) {
	printf("Wszystkie choroby pacjenta to: \n");
	DiseaseList *ptr = patient->diseases;
	while(ptr != NULL) {
		printf("%s, ", ptr->disease->description);
		ptr = ptr->next;
	}
}*/

// function adds disease to the end of patient's diseases list
void pushDisease(Patient *patient, char *description) {
	if(patient->diseases == NULL) { // list of diseases is empty
		patient->diseases = (DiseaseList*) malloc(sizeof(DiseaseList)); // makes space for list of diseases
		patient->diseases->disease = (Disease*) malloc(sizeof(Disease)); // makes space for first element on the list of diseases
		patient->diseases->disease->description = (char*) malloc((strlen(description)+1)*sizeof(char)); // makes space for description of disease, new pointer
		strcpy(patient->diseases->disease->description, description); // copies given description into the structer
		patient->diseases->disease->refCounter = 1; 
		patient->diseases->next = NULL;
		patient->lastDisease = patient->diseases;
	}
	else {
		DiseaseList *current = patient->lastDisease;
		// current->next is pointer of our new disease
		current->next = (DiseaseList*) malloc(sizeof(DiseaseList));
		current->next->disease = (Disease*) malloc(sizeof(Disease));
		current->next->disease->description = (char*) malloc((strlen(description)+1)*sizeof(char));
		strcpy(current->next->disease->description, description);
		current->next->disease->refCounter = 1;
		current->next->next = NULL;
		patient->lastDisease = current->next;
	}
}


//returns poiter to n-th disease of given patient or NULL if such disease is not found
DiseaseList* findDisease(Patient *patient, int n, DiseaseList **prev) { 
	DiseaseList *ptr = patient->diseases, *tmp = NULL; //tmp = NULL means no prev
	int it = 1; //iterator for counting disease descriptions
	while(ptr != NULL) {
		if(it == n)
		{
			*prev = tmp;
			return ptr;
		}
		tmp = ptr;
		ptr = ptr->next;
		it++;
	}
	return NULL;
}

Disease* getLastDisease(Patient *patient) {
	if(patient->diseases == NULL)
		return NULL;
	return patient->lastDisease->disease;
}

void pushCopiedDisease(Patient *patient, Disease *disease) {
	if(patient->diseases == NULL) { // list of diseases is empty
		patient->diseases = (DiseaseList*) malloc(sizeof(DiseaseList)); // makes space for list of diseases
		patient->diseases->disease = disease;
		patient->diseases->disease->refCounter = patient->diseases->disease->refCounter + 1; 
		patient->diseases->next = NULL;
		patient->lastDisease = patient->diseases;
	}
	else {
		DiseaseList *current = patient->lastDisease;
		// current->next is pointer of our new disease
		current->next = (DiseaseList*) malloc(sizeof(DiseaseList));
		current->next->disease = disease;
		current->next->disease->refCounter = current->next->disease->refCounter + 1;
		current->next->next = NULL;
		patient->lastDisease = current->next;

	}
}

int addNewDiseaseDescription(char name[], char description[]) {
	PatientList *current = findPatient(name);
	if(current == NULL)
		current = addPatient(name);
	Patient *patient = current->patient; // pointer for patient with given name
	pushDisease(patient, description);
	amountOfDiseases++;
	return 0;
}

int copyDiseaseDescription(char name1[], char name2[]) {
	PatientList *currentPatientList1 = findPatient(name1), *currentPatientList2 = findPatient(name2);
	if(currentPatientList2 == NULL)
		return 1; // error code, patient with name2 doesn't exist
	if(currentPatientList1 == NULL)
		currentPatientList1 = addPatient(name1);
	Disease *disease = getLastDisease(currentPatientList2->patient);
	if(disease == NULL)
		return 1; // error code, patient with name2 doesn't have any diseases, so nothing can be copied
	//printf(" %s ma teraz opis %s\n", currentPatientList1->patient->name, disease->description);
	pushCopiedDisease(currentPatientList1->patient, disease);
	//printf(" %s ma teraz opis %s\n", currentPatientList1->patient->name, currentPatientList1->patient->diseases->disease->description);
	/*if(getLastDisease(currentPatientList1->patient) != getLastDisease(currentPatientList2->patient))
	{
		printf("MAMY PROBLEM!");
		printf("\n pierwszy: %s drugi: %s\n", currentPatientList1->patient->diseases->disease->description, currentPatientList2->patient->diseases->disease->description);
	}*/ //zrobic z tego assert
	return 0;
}

int changeDiseaseDescription(char name[], int n, char description[]) {

	PatientList *currentPatientList = findPatient(name);
	if(currentPatientList == NULL) // patient doesn't exist, return error code 
		return 1;
	DiseaseList *prev = NULL; //pointer to diseaseList just before diseaseList to be deleted or NULL if diseaseList to be deleted is first
	DiseaseList *diseaseToBeDeleted = findDisease(currentPatientList->patient, n, &prev);
	if(diseaseToBeDeleted == NULL) {
		return 1; // disease with given number doesn't exist
	}	
	DiseaseList *next = diseaseToBeDeleted->next; // pointer to diseaseList just after diseaseList to be deleted
	// delete our DiseaseList and disease if it's not used by someone else
	diseaseToBeDeleted->disease->refCounter = diseaseToBeDeleted->disease->refCounter - 1;
	if(diseaseToBeDeleted->disease->refCounter == 0) {
		free(diseaseToBeDeleted->disease->description);
		free(diseaseToBeDeleted->disease);
		amountOfDiseases--;
	}
	free(diseaseToBeDeleted);
	// create new DiseaseList
	DiseaseList *newDiseaseList = (DiseaseList*) malloc(sizeof(DiseaseList));
	newDiseaseList->disease = (Disease*) malloc(sizeof(Disease));
	newDiseaseList->disease->description = (char*) malloc((strlen(description)+1)*sizeof(char));
	strcpy(newDiseaseList->disease->description, description);
	newDiseaseList->disease->refCounter = 1;
	newDiseaseList->next = next;
	amountOfDiseases++;
	// join our new DiseaseList into existing DiseaseList
	if(prev == NULL) {
		currentPatientList->patient->diseases = newDiseaseList;
	}
	else {
		prev->next = newDiseaseList;
	}
	return 0;
}

const char* getPatientDescription(char name[], int n) {
	PatientList *currentPatientList = findPatient(name);
	if(currentPatientList == NULL)
		return NULL;
	Patient *patient = currentPatientList->patient;
	DiseaseList *tmp = NULL;
	DiseaseList *diseaseList = findDisease(patient, n, &tmp);
	if(diseaseList == NULL)
		return NULL;
	return diseaseList->disease->description;
}

int deletePatient(char name[]) {
	PatientList *currentPatientList = findPatient(name);
	if(currentPatientList == NULL) // patient doesn't exist, return error code 
		return 1;
	DiseaseList *ptr = currentPatientList->patient->diseases;
	while(ptr != NULL) {
		DiseaseList *next = ptr->next;
		// there are 3 thing to free: DiseaseList, Disease, Description - But Disease can only be freed when refCounter == 0
		Disease *disease = ptr->disease;
		disease->refCounter = disease->refCounter - 1; 
		if(disease->refCounter == 0) {
			free(disease->description);
			free(disease);
			amountOfDiseases--;
		}
		free(ptr);
		ptr = next;
	}
	currentPatientList->patient->diseases = NULL;
	return 0;
}

void freeMemory() {
	// free every allocated memory
	PatientList *current = patientListHead, *next = NULL;
	while(current != NULL) {
		next = current->next;
		DiseaseList *diseaseCurrent = current->patient->diseases, *nextDisease = NULL;
		while(diseaseCurrent != NULL) {
			nextDisease = diseaseCurrent->next;
			if(diseaseCurrent->disease != NULL) {
				if(diseaseCurrent->disease->description != NULL)
					free(diseaseCurrent->disease->description);
				free(diseaseCurrent->disease);
			}
			free(diseaseCurrent);
			diseaseCurrent = nextDisease;
		}
		if(current->patient != NULL)
			free(current->patient);
		free(current);
		current = next;
	}
}