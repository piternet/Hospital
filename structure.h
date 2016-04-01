/*
 * structure.h
 *
 *  Created on: 17 mar 2016
 *      Author: piternet
 */

#ifndef STRUCTURE_H_
#define STRUCTURE_H_

int getAmountOfDiseases();
void freeMemory();

int addNewDiseaseDescription(char[], char[]);
int copyDiseaseDescription(char[], char[]);
int changeDiseaseDescription(char[], int, char[]);
const char* getPatientDescription(char[], int);
int deletePatient(char[]);

#endif /* STRUCTURE_H_ */
