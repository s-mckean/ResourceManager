/*********************************************************************************************************
Author: Spencer McKean

Description: Header for graph.cpp
*********************************************************************************************************/

#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "node.h"


class Graph {
	private:
		vector<Node*> nodes;

	public:
		Graph(string fileName = "resource");

		void DisplayGraph(string direction);
		void DisplayGraphList();
		void DisplayGraphNodes(string direction);

		void RemoveNode(string nodeName);
		void CreateNode(string nodeType);
		void DeleteAllNodes();

		void SaveGraph(string fileName = "saveFile");

		~Graph();
};

#endif

