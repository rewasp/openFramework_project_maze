#pragma once

#include "ofMain.h"

class graph
{
public:

	int node_num;

	vector<vector<int>> adj_list; // use adjacent list for graph representation
	vector<ofVec2f> room_placement; // to know each room number in advance

	vector<int> shortest_path; // to save the shortest path
	vector<vector<int>> linked; // to save visited path
	vector<int> parent;
	vector<bool> visited;

	ofFbo travel;
	ofFbo shortest;

	ofColor path;
	ofColor sp;

	void dfs();

	graph(int row, int col); // constructor overloaded

	void put_edge(int u, int v);
	void print_adj();

	void make_travel_Fbo();
	void add_travel_Fbo(int, int);
	void find_shortest();

	graph();
	~graph();

private:
	bool dfs_visit(int node);
};

