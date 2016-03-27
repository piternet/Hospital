/*
 * parse.h
 *
 *  Created on: 17 mar 2016
 *      Author: piternet
 */

#ifndef PARSE_H_
#define PARSE_H_

#define MAX_BUFF_SIZE 100007 // 10^5, + 7 for safety
#define EOL (char) 10 // end of line, ASCII code number 10

#define NEW_DISEASE_ENTER_DESCRIPTION "NEW_DISEASE_ENTER_DESCRIPTION"
#define NEW_DISEASE_COPY_DESCRIPTION "NEW_DISEASE_COPY_DESCRIPTION"
#define CHANGE_DESCRIPTION "CHANGE_DESCRIPTION"
#define PRINT_DESCRIPTION "PRINT_DESCRIPTION"
#define DELETE_PATIENT_DATA "DELETE_PATIENT_DATA"

#define CMD_DONE "OK"
#define CMD_IGNORED "IGNORED"

void getInput(int);
void parseLine(char[], int);

#endif /* PARSE_H_ */
