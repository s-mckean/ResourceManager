/*********************************************************************************************************
Author: Spencer McKean

Description:

This is a container for the entire tree/graph of nodes.
Manages all actions to be applied to the nodes.
*********************************************************************************************************/

#include <iostream>
#include <sstream>
#include <fstream>
#include "graph.h"
using namespace std;


Graph::Graph(string fileName) {
	string line;

	ifstream file(fileName + ".txt");

	if (!file) {
		cout << "File could not be found\n" << endl;
	}
	else {
		cout << "Loading " << fileName << ".txt" << endl;
		while (getline(file, line)) {
			CreateNode(line);
		}
	}

	file.close();
}

/*To display graph*/
void Graph::DisplayGraph(string direction) {
	DisplayGraphNodes(direction);
	cout << endl;
	DisplayGraphList();
}

/*Displays each node's usability in the graph*/
void Graph::DisplayGraphList() {
	for (unsigned int i = 0; i < nodes.size(); i++) {
		cout << nodes[i]->GetNodeType() << " - " << (nodes[i]->GetIsUsable() ? "Usable" : "Not Usable") << endl;
	}
	cout << endl;
}

/*Displays nodes with reliances*/
void Graph::DisplayGraphNodes(string direction) {
	vector<Node*> rootNodes;

	//find top of trees
	for (unsigned int i = 0; i < nodes.size(); i++) {
		if (nodes[i]->GetListSize(direction) == 0) {
			rootNodes.push_back(nodes[i]);
		}
	}

	//Loops through all top of trees for display
	for (unsigned int j = 0; j < rootNodes.size(); j++) {
		if (!rootNodes[j]->GetDisplayed()) {
			rootNodes[j]->DisplayNode(0, direction);
			cout << endl;
		}
	}

	//set displayed state for each node to false in order to reprint
	for (unsigned int k = 0; k < nodes.size(); k++) {
		nodes[k]->SetDisplayed(false);
	}
	
	cout << endl;
}

/*Handles finiding and deleting a specified node*/
void Graph::RemoveNode(string nodeName) {
	bool found = false;
	for (unsigned int i = 0; i < nodes.size(); i++) {
		if (nodes[i]->GetNodeType() == nodeName) {
			found = true;
			nodes[i]->SetSubNodesUsable(false);
			nodes[i]->DeleteNode();
			delete nodes[i];
			nodes.erase(nodes.begin() + i);
			cout << "The '" << nodeName << "' node has been deleted." << endl;
			break;
		}
	}
	if(!found) {
		cout << "Resource Node with that name does not exist." << endl;
	}
}

/*Creates a node and the links to that node*/
void Graph::CreateNode(string input) {
	Node *currentNode = NULL;
	string line, resName;
	bool arg1 = true;
	bool found = false;

	istringstream ss(input);

	while (getline(ss, resName, ' ')) {
		found = false;
		if (arg1) {
			//create first node if it hasnt already
			if(nodes.size() == 0) {
				currentNode = new Node(resName);
				nodes.push_back(currentNode);
			}

			else {
				//find the node if it exists
				for (unsigned int i = 0; i < nodes.size(); i++) {
					if (nodes[i]->GetNodeType() == resName) {
						currentNode = nodes[i];
						found = true;
						break;
					}
				}
				//if it is not found create a new node
				if (!found) {
					currentNode = new Node(resName);
					nodes.push_back(currentNode);
				}
			}

			arg1 = false; //no longer node to create
		}

		//to create links to node
		else {
			//to create link to an existing node
			for (unsigned int i = 0; i < nodes.size(); i++) {
				if (nodes[i]->GetNodeType() == resName) {
					currentNode->AddResourceRequired(nodes[i]);
					nodes[i]->AddRequirementFor(currentNode);
					found = true;
					break;
				}
			}
			//creates a new node if one is not found
			if (!found) {
				nodes.push_back(new Node(resName));
				currentNode->AddResourceRequired(nodes.back());
				nodes.back()->AddRequirementFor(currentNode);
			}
		}
	}
}

/*Deletes Entire Tree*/
void Graph::DeleteAllNodes() {
	int graphSize = nodes.size();
	for (int i = 0; i < graphSize; i++) {
		nodes[0]->DeleteNode();
		delete nodes[0];
		nodes.erase(nodes.begin());
	}
}

/*Saves file to fileName.txt or saveFile.txt*/
void Graph::SaveGraph(string fileName) {
	vector<Node*> nodeResources;
	ofstream saveFile(fileName + ".txt");

	for (unsigned int i = 0; i < nodes.size(); i++) {
		saveFile << nodes[i]->GetNodeType();
		nodeResources = nodes[i]->GetResources();
		for (unsigned int j = 0; j < nodeResources.size(); j++) {
			saveFile << " " << nodeResources[j]->GetNodeType();
		}
		saveFile << endl;
	}
	cout << "Graph saved to " << fileName << ".txt" << endl;
	saveFile.close();
}

Graph::~Graph() {
	for (unsigned int i = 0; i < nodes.size(); i++) {
		delete nodes[i];
	}
}