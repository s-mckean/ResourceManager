/*****************************************************************************************************************************
Author: Spencer McKean

Description: Main

A program that will read in a text file of a format

	handgun bullets
	bullets ore
	bombs ore
	turret bullets

where the first word in a line is a resource and the following word, or words, are the various resources that it depends on.
Using the information read in, a resource tree of dependencies will be created.

The user has the option to input various commands:
	1.) 'NodeName'						- Will delete the node that has the name that was entered from the graph
	2.) 'Q' or 'q'						- Will quit the program
	3.)	+'NodeName'	'link1' 'link2'		- Will add or modify the node with NodeName and add a dependence on subsequent inputs
	4.) /swap							- Will change the direction that the tree is displayed
	5.) /save 'FileName'				- Will save to 'saveFile.txt' by default if no 'FileName' is entered
	6.) /load 'FileName'				- Will load file with 'FileName'.txt or resource.txt by default
	7.) /clear							- Will erase the entire tree
	8.) '/h' or '/help'					- Will display all commands and a brief description

*****************************************************************************************************************************/

#include <iostream>
#include <regex>
#include "graph.h"
#include "inputController.h"
using namespace std;

int main() {
	bool loop = true;
	int optionSelected = 0;
	string direction = "DOWN";
	smatch saveMatches;
	string userInput, commandVal;

	Graph *resourceGraph = new Graph();
	
	resourceGraph->DisplayGraph(direction);
	while (loop) {
		getline(cin, userInput);
		
		optionSelected = UserInParse(userInput, commandVal, saveMatches);
		
		system("cls");

		loop = RunCommand(resourceGraph, optionSelected, direction, commandVal, saveMatches);

		cout << endl;

		resourceGraph->DisplayGraph(direction);
	}

	delete resourceGraph;

	return 0;
}