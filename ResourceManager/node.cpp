/*********************************************************************************************************
Author: Spencer McKean

Description: Functions required for manipulating resource nodes
*********************************************************************************************************/

#include <iostream>
#include <vector>
#include "node.h"
using namespace std;

Node::Node(string t) {
	isUsable = true;
	nodeType = t;
	displayed = false;
}

string Node::GetNodeType() {
	return nodeType;
}

bool Node::GetIsUsable() {
	return isUsable;
}

int Node::GetListSize(string direction) {
	//down - all nodes that require a certain node
	//up   - the nodes required for a certain node
	if (direction == "DOWN") { return resources.size(); }
	else if (direction == "UP") { return requirementFor.size(); }
}

bool Node::GetDisplayed() {
	return displayed;
}

vector<Node*> Node::GetResources() {
	return resources;
}

void Node::SetIsUsable(bool b) {
	isUsable = b;
}

void Node::SetDisplayed(bool b) {
	displayed = b;
}

void Node::SetSubNodesUsable(bool b) {
	for (int i = 0; i < requirementFor.size(); i++) {
		requirementFor[i]->SetIsUsable(b);
		requirementFor[i]->SetSubNodesUsable(b);
	}
}

void Node::AddResourceRequired(Node *resource) {
	resources.push_back(resource);
}

void Node::AddRequirementFor(Node *resource) {
	requirementFor.push_back(resource);
}

void Node::DeleteNode() {
	for (int i = 0; i < requirementFor.size(); i++) {
		requirementFor[i]->RemoveNodeFromResources(this);
	}

	for (int j = 0; j < resources.size(); j++) {
		resources[j]->RemoveNodeFromReqFor(this);
	}
}

void Node::RemoveNodeFromResources(Node *nodeToRemove) {
	for (int i = 0; i < resources.size(); i++) {
		if (resources[i] == nodeToRemove) {
			isUsable = false;
			resources.erase(resources.begin()+i);
			break;
		}
	}
}

void Node::RemoveNodeFromReqFor(Node *nodeToRemove) {
	for (int i = 0; i < requirementFor.size(); i++) {
		if (requirementFor[i] == nodeToRemove) {
			requirementFor.erase(requirementFor.begin() + i);
			break;
		}
	}
}

/*Displays a node and recurses for all children*/
void Node::DisplayNode(int indentLevel, string direction) {
	vector<Node*> listToExplore;
	if (direction == "DOWN") {
		//if direction is down explore graph through requirementFor
		listToExplore = requirementFor;
	}
	else if (direction == "UP") {
		//if direction is UP explore graph through resources
		listToExplore = resources;
	}
	for (int i = 0; i < indentLevel; i++) {
		cout << "    ";
	}
	cout << (indentLevel == 0 ? "||" : (direction == "DOWN" ? "->" : "<-")) << nodeType;

	if (!displayed) {
		for (int i = 0; i < listToExplore.size(); i++) {
			cout << endl;
			listToExplore[i]->DisplayNode(indentLevel + 1, direction);
		}
		displayed = true;
	}
	else {
		cout << "(duplicate)";
	}
}