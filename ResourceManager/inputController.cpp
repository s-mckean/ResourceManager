/*********************************************************************************************************
Author: Spencer McKean

Description:

A file created to handle the input of the user.

Command Codes:
1 - Delete Node
2 - Quit
3 - Add Node
4 - Switch direction of tree
5 - Save to file
6 - Load File
7 - Clear Entire tree
8 - Help

examples inputs:
----------------------------------------------------------------------------------------------------------
Delete Node:        "NodeName" - Will delete node with name 'NodeName'
----------------------------------------------------------------------------------------------------------
Quit:               "Q" or "q" - will quit the program
----------------------------------------------------------------------------------------------------------
Add Node:           "+NodeName" - will create a node with name 'NodeName'
                    "+NodeName link1 link2" - will create a node that requires node1 and node2
				                           (there can be any number of links)
----------------------------------------------------------------------------------------------------------
Switch Direction:   "/swap" - will change the direction the tree is read
                              read: all nodes that require a certain node (default) 
							                         or 
							        the nodes required for a certain node
----------------------------------------------------------------------------------------------------------
Save File:          "/save" - will save the current tree to 'saveFile.txt'
                    "/save FileName" - will save the current tree to 'FileName'

					Note: '.txt' will not be read if FileName ends with it
					       if FileName = resource.txt it will save to resource.txt not resource.txt.txt
----------------------------------------------------------------------------------------------------------
Load File:          "/Load" - will load the tree from 'resource.txt'
                    "/Load FileName" - will load the tree from 'FileName'

					Note: '.txt' will not be read if FileName ends with it
						   if FileName = resource.txt it will load from resource.txt not resource.txt.txt
----------------------------------------------------------------------------------------------------------
Clear Tree:         "/clear - will delete the entire current tree
----------------------------------------------------------------------------------------------------------
Help:               "/help" or "/h" - will display all available commands
*********************************************************************************************************/

#include <string>
#include <regex>
#include "inputController.h"
using namespace std;

/*Parses and determines what to do with user input*/
int UserInParse(string userIn, string &commandVal, smatch &saveMatches) {
	smatch inputMatches;
	string commandSym;
	
	regex parseInput("^([\\+|\\/])?(.+)$");
	regex parseFileName("^(save|load)[ ]?([^\\\\/\\:\\*\?\"\\<\\>\\|\\.]*)(\\.txt)?$");

	if (regex_search(userIn, inputMatches, parseInput)) {
		commandSym = inputMatches[1];
		commandVal = inputMatches[2];

		if (commandSym == "+") {
			return 3; //add node
		}
		else if (commandSym == "/") {
			if (commandVal == "help" || commandVal == "h") {
				return 8; //help
			}
			else if (commandVal == "swap") {
				return 4; //swap
			}
			else if (commandVal == "clear") {
				return 7; //clear
			}
			else if (regex_search(commandVal, saveMatches, parseFileName)) {
				if (saveMatches[1] == "save") {
					return 5; //save
				}
				else {
					return 6;//load
				}
			}
			else {
				return 0; //invalid
			}
		}
		else if (commandVal == "q" || commandVal == "Q") {
			return 2; //quit
		}
		else {
			return 1; //delete
		}
	}
	else {
		return 0; //invalid
	}
}

/*Does the appropriate action for the respective command code*/
bool RunCommand(Graph *tree, int commandCode, string &graphDirection, string commandVal, smatch saveMatches) {
	switch (commandCode) {

	case 1: //delete
		tree->RemoveNode(commandVal);
		return true;

	case 2: //quit
		return false;

	case 3: //Add Node
		tree->CreateNode(commandVal);
		cout << "Node created." << endl;
		return true;

	case 4: //swap
		(graphDirection == "DOWN" ? graphDirection = "UP" : graphDirection = "DOWN");
		cout << "Graph direction has been swapped." << endl;
		return true;

	case 5: //save tree
		if (saveMatches[2] == "")
		{
			tree->SaveGraph();
		}
		else {
			tree->SaveGraph(saveMatches[2]);
		}
		return true;

	case 6: //load tree
		if (saveMatches[2] == "") {
			tree = new Graph();
		}
		else {
			tree = new Graph(saveMatches[2]);
		}
		return true;

	case 7: //clear
		tree->DeleteAllNodes();
		cout << "Tree deleted.\n" << endl;
		return true;

	case 8: //Help
		cout << "q, Q   --- Quit\n" 
			"+      --- add node followed by any number of links <+NodeName link1 link2 ...linkN>\n"
			"/swap  --- switches the direction of the tree\n"
			"/clear --- deletes the entire tree\n"
			"/save  --- saves entire tree to to a specified text file.\n"
			"           'saveFile.txt is the default file name </save> or </save saveFileName>\n"
			"           (file names cannot contain \\ / : * ? \" < > | .)\n"
			"/load  --- Loads a text file. 'resource.txt' by default </load> or </load fileToLoad>"
			<< endl;
		return true;

	default: //invalid input
		cout << "invalid input" << endl;
		cout << "Enter \\h or \\help for a list of commands.\n" << endl;
		return true;
	}
}
