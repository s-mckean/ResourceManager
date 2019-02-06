# Resource Manager

Author: Spencer McKean

Code last modified on 12/6/18

GitHub Link: https://github.com/s-mckean/ResourceManager

## Description

A program that will read in a text file of a format

	handgun bullets
	bullets ore
	bombs ore
	turret bullets

where the first word in a line is a resource and the following word, or words, are the various resources that it depends on.
Using the information read in, a resource tree of dependencies will be created. The user then has the ability to manipulate
the resource tree with input commands.

### Commands

The user has the option to input various commands:

	1.) 'NodeName'			  - Will delete the node that has the name that was entered from the graph
	2.) 'Q' or 'q'			  - Will quit the program
	3.) +'NodeName'	'link1' 'link2'	  - Will add or modify the node with NodeName and add a dependence on subsequent inputs
	4.) /swap			  - Will change the direction that the tree is displayed
	5.) /save 'FileName'		  - Will save to 'saveFile.txt' by default if no 'FileName' is entered
	6.) /load 'FileName'		  - Will load file with 'FileName'.txt or resource.txt by default
	7.) /clear			  - Will erase the entire tree
	8.) '/h' or '/help'		  - Will display all commands and a brief description
	
## Sample Window

![Image](https://user-images.githubusercontent.com/42820224/52361910-f62eaa80-2a04-11e9-93eb-8734c03e7e51.PNG)
	
## File Structure
	
	README.md				- README
	ResourceManager.sln			- Visual Studio .sln file
	ResourceManager(folder)
		-> node.h			- header for the 'Node' class which contains information for each resource
		-> graph.h			- header for the 'Graph' class which contains all of the resource nodes
		-> inputController.h		- header for inputController.cpp
		
		-> Main.cpp			- runs user inputed commands until they quit
		-> node.cpp			- Contains functions required for manipulating resource nodes 
		-> graph.cpp			- Contains functions required for the manipulation of the graph of nodes
		-> inputController.cpp		- Used to parse user inputs in order to perform the desired action
		
		-> resource.txt			- sample input text file
		-> resource1.txt		- sample input text file
		-> resource2.txt		- sample input text file
