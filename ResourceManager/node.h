/*********************************************************************************************************
Author: Spencer McKean

Description: Header for node.cpp
*********************************************************************************************************/

#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Node 
{
	private:
		bool isUsable;
		bool displayed;
		string nodeType;
		vector<Node*> resources;
		vector<Node*> requirementFor;

	public:
		Node(string t = "default");
		string GetNodeType();
		bool GetIsUsable();
		int GetListSize(string direction);
		bool GetDisplayed();
		vector<Node*> GetResources();

		void SetIsUsable(bool b);
		void SetDisplayed(bool b);
		void SetSubNodesUsable(bool b);

		void AddResourceRequired(Node *resource);
		void AddRequirementFor(Node *resource);

		void DeleteNode();
		void RemoveNodeFromResources(Node *nodeToRemove);
		void RemoveNodeFromReqFor(Node *nodeToRemove);

		void DisplayNode(int indentLevel, string direction);
};

#endif
