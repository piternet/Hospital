/*
 * hospital.c
 *
 *  Created on: 17 mar 2016
 *      Author: piternet
 */

#include "parse.h"
#include "structure.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define V_PARAMETR "-v"

int main(int argc, char **argv) {
	int parametr = 0;
	if(argc > 1) { // program is executed with some parametr 
		if(strcmp(argv[1], V_PARAMETR) == 0) {
			parametr = 1; // there is V_PARAMETR parametr
		}
	}
	getInput(parametr);
	freeMemory();
	return 0;
}
