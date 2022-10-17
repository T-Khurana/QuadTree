#include <iostream>
#include <string>
//#include "QuadTreeNode.h"


using namespace std;

class quad_tree_node{

//friend class quad_tree;

public:
	string city_name;
	double latitude;
	double longitude;
	int population;
	int cost_of_living;
	int avg_sal;

	quad_tree_node* north_east;
	quad_tree_node* north_west;
	quad_tree_node* south_east;
	quad_tree_node* south_west;

	quad_tree_node(string name, double x, double y, int pop, int col, int avg);//, quad_tree_node* NE, quad_tree_node* NW, quad_tree_node* SE, quad_tree_node* SW);
	bool insert (quad_tree_node* current, quad_tree_node* node);
	int search(double x, double y);
	int attribute(string attr);
	quad_tree_node* search_helper(double x, double y);
	//double min (double x, double y, string d, string attr);
	quad_tree_node* direction(string d);
	//void print();
	//void clear (quad_tree_node* root);

};

class quad_tree{

private:

	quad_tree_node* root;

	

public:
	//int size;
	quad_tree();
	bool insert(string name, double x, double y, int pop, int col, int avg);
	int searchx (double x, double y);
	int q_max(quad_tree_node* rootz, string attrib);
	int q_min(quad_tree_node* rooty, string attrib);
	int q_total(quad_tree_node* rootx, string attri);
	void printx(quad_tree_node* roott);
	int size_of_tree ();
	void clearx(quad_tree_node* rootl);
	quad_tree_node* get_root(){
		return root;
	}

};





