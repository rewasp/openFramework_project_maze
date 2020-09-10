#include "graph.h"

graph::graph()
{

}

/* resize vector */
graph::graph(int row, int col)
{
	adj_list.resize(row*col);
	room_placement.resize(row*col);
	visited.resize(row*col);
	linked.resize(row*col);

	parent.resize(row*col);
	shortest_path.resize(row*col);

	fill(visited.begin(), visited.end(), false);

}


void graph::put_edge(int u, int v)
{
	adj_list[u].push_back(v);
	adj_list[v].push_back(u);
}

void graph::print_adj()
{
	for (int i = 0; i < node_num; i++) {
		printf("Node %d's connection list\n", i);
		for (int j = 0; j < adj_list[i].size(); j++) {
			cout << adj_list[i][j] << endl;
		}
	}

}

void graph::dfs()
{
	dfs_visit(0);
	/* After DFS is done, initialize ofFbo travel */
	make_travel_Fbo();
}

bool graph::dfs_visit(int node)
{
	visited[node] = true;
	//printf("visiting node %d\n", node);

	if (node == node_num - 1) {
		printf("Reached final destination!!\n");
		return TRUE;
	}

	for (int down : adj_list[node])
		if (visited[down] == FALSE) {
			parent[down] = node;

			add_travel_Fbo(node, down);
			if (dfs_visit(down) == TRUE) return TRUE;
		}

}

void graph::make_travel_Fbo()
{
	/* Ack: walked path while performing DFS */

	travel.allocate(ofGetWidth(), ofGetHeight());
	travel.begin();
	ofClear(240, 255, 255, 0);
	ofSetColor(path);
	ofSetLineWidth(2);

	for (int i = 0; i < node_num; i++) {
		for (int j = 0; j < linked[i].size(); j++)
			ofDrawLine(room_placement[i], room_placement[linked[i][j]]);
	}

	travel.end();
}

/* Mark visited path */
void graph::add_travel_Fbo(int start_node, int end_node)
{
	linked[start_node].push_back(end_node);
}

void graph::find_shortest()
{
	shortest.allocate(ofGetWidth(), ofGetHeight());
	shortest.begin();
	ofClear(240, 255, 255, 0);
	ofSetColor(sp);
	ofSetLineWidth(2);

	/* Start from target ndoe.. trace back while only passing the each one's parent node */
	int go = node_num - 1; // target node
	int back = parent[node_num - 1]; // target node's parent

	while (go != 0) {
		ofDrawLine(room_placement[go], room_placement[back]);
		go = back;
		back = parent[go];
	}
	shortest.end();

}

graph::~graph()
{
}
