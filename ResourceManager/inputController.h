/*********************************************************************************************************
Author: Spencer McKean

Description: Header for inputController.cpp
*********************************************************************************************************/

#ifndef INPUTCONTROLLER_H
#define INPUTCONTOLLER_H

#include <string>
#include "graph.h"
using namespace std;


int UserInParse(string userIn, string &commandVal, smatch &saveMatches);

/*	Command Codes :
	1 - Delete Node
	2 - Quit
	3 - Add Node
	4 - Switch direction of tree
	5 - Save to file
	6 - Load File
	7 - Clear Entire tree
	8 - Help	*/
bool RunCommand(Graph *tree, int commandCode, string &graphDirection, string commandVal, smatch saveMatches);

#endif INPUTCONTROLLER_H