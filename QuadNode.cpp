#include <iostream>
#include <string>
#include <limits.h>
#include "QuadNode.h"

using namespace std;

//Functions for the quad tree node class
int size=0;

bool quad_tree_node::insert(quad_tree_node *current, quad_tree_node *node){

	if ((current -> latitude == node -> latitude) && (current -> longitude == node -> longitude)){
		return false;
	}

	if ((node -> latitude >= current -> latitude) && (node -> longitude > current -> longitude)){
		//northeast condition
		if ((current -> north_east)== NULL){
			current -> north_east = node;
			size ++;
			return true;
		}

		return current->north_east->insert(current->north_east,node);

	}

	else if ((node -> latitude < current -> latitude) && (node -> longitude >= current -> longitude)){
		//northwest condition
		if ((current -> north_west)== NULL){
			current -> north_west = node;
			size ++;
			return true;
		}
		return current->north_west->insert(current->north_west,node);

	}

	else if ((node -> latitude <= current -> latitude) && (node -> longitude < current -> longitude)){
		//southwest

		if ((current -> south_west)== NULL){
			current -> south_west = node;
			size ++;
			return true;
		}
		return current->south_west->insert(current->south_west,node);
	}

	else if ((node -> latitude > current -> latitude) && (node -> longitude <= current -> longitude)){
		//southeast

		if ((current -> south_east)== NULL){
			current -> south_east = node;
			size ++;
			return true;
		}
		return current->south_east->insert(current->south_east,node);

	}	
	return false;

} 


quad_tree_node::quad_tree_node(string name, double x, double y, int pop, int col, int avg){

	city_name=name;
	latitude=x;
	longitude=y;
	population=pop;
	cost_of_living=col;
	avg_sal=avg;

	north_east =NULL;
	north_west=NULL;
	south_east=NULL;
	south_west=NULL;
}

int quad_tree_node::search(double x, double y){


	if ((x==latitude) && (y==longitude)){
		cout<<"found "<<city_name<<endl;
		return 1;
	}

	else if ((x >=latitude) && (y > longitude)){
		if (north_east == NULL){
			cout<<"not found"<<endl;
			return 0;
		}

		else{
			return north_east -> search(x,y);
		}

	}

	else if ((x<latitude) && (y>=longitude)){
		if (north_west == NULL){
			cout<<"not found"<<endl;
			return 0;
		}

		else {
			return north_west -> search(x,y);
		}
	}

	else if ((x<=latitude)&&(y<longitude)){
		if (south_west==NULL){
			cout<<"not found"<<endl;
			return 0;
		}

		else {
			return south_west -> search(x,y);
		}
	}
	else if ((x>latitude)&&(y<=longitude)){
		if (south_east == NULL){
			cout<<"not found"<<endl;
			return 0;
		}

		else {
			return south_east -> search(x,y);
		}
	}

	return 0;

}

//Functions for the quad tree class

quad_tree::quad_tree(){
	root = NULL;
}

bool quad_tree:: insert (string name, double x, double y, int pop, int col, int avg){

	if (size==0){
		root = new quad_tree_node (name, x, y, pop, col, avg);//, NULL, NULL, NULL, NULL);
		size++;
		return true;
	}

	else if (size !=0){
		quad_tree_node *node= new quad_tree_node (name, x, y, pop, col, avg);//, NULL, NULL, NULL, NULL);

		return node->insert(root,node);	

	}
}

int quad_tree::searchx (double x, double y){

	if(size ==0){
		cout<<"not found"<<endl;
		return 0;
	}

	else {
		return root->search(x,y);
	}

}
quad_tree_node* quad_tree_node::search_helper(double x, double y){

	if ((x==latitude) && (y==longitude)){
		return this;
	}

	else if ((x >=latitude) && (y > longitude)){
		if (north_east == NULL){
			return nullptr;
		}

		else{
			return north_east -> search_helper(x,y);
		}

	}

	else if ((x<latitude) && (y>=longitude)){
		if (north_west == NULL){
			return nullptr;
		}

		else {
			return north_west -> search_helper(x,y);
		}
	}

	else if ((x<=latitude)&&(y<longitude)){
		if (south_west==NULL){
			return nullptr;
		}

		else {
			return south_west -> search_helper(x,y);
		}
	}
	else if ((x>latitude)&&(y<=longitude)){
		if (south_east == NULL){
			return nullptr;
		}

		else {
			return south_east -> search_helper(x,y);
		}
	}

	return nullptr;

}

int quad_tree_node::attribute(string attr){
	if (attr=="p"){

		return this -> population;

	}

	if (attr=="r"){

		return this -> cost_of_living;
		
	}

	if (attr=="s"){
		return this -> avg_sal;
		
	}
}

quad_tree_node* quad_tree_node::direction(string d){
	if (d=="NE"){
		return this -> north_east;
	} 
	else if (d=="NW"){
		return this -> north_west;
	}

	else if (d=="SW"){
		return this -> south_west;
	}

	else if (d=="SE"){
		return this -> south_east;
	}
}



int quad_tree::q_total(quad_tree_node* rootx, string attri){

	if (rootx == nullptr){
		return 0;
	}
	else if (rootx != nullptr){
		return (q_total(rootx->north_west, attri)+q_total(rootx->north_east, attri)
			+q_total(rootx->south_west, attri)+ q_total(rootx->south_east, attri)+
			rootx->attribute(attri));
	}

}

int quad_tree::q_min(quad_tree_node* rooty, string attrib){
	int minimum = INT_MAX;

	if (rooty == nullptr){
		return minimum;
	}

	else if (rooty!=nullptr){
		int array[5];
		array[0]= q_min(rooty->north_west, attrib);
		array[1]= q_min(rooty->north_east, attrib);
		array[2]= q_min(rooty->south_west, attrib);
		array[3]= q_min(rooty->south_east, attrib);

		array[4]=rooty->attribute(attrib);

		for (int i=0; i<=4; i++){
			if (array[i]<minimum){
				minimum=array[i];
			}
		}
		return minimum;
	}
}
int quad_tree::q_max(quad_tree_node* rootz, string attrib){
	int maximum = -INT_MAX;

	if (rootz == nullptr){
		return maximum;
	}

	else if (rootz!=nullptr){
		int array[5];
		array[0]= q_max(rootz->north_west, attrib);
		array[1]= q_max(rootz->north_east, attrib);
		array[2]= q_max(rootz->south_west, attrib);
		array[3]= q_max(rootz->south_east, attrib);

		array[4]=rootz->attribute(attrib);

		for (int i=0; i<=4; i++){
			if (array[i]>maximum){
				maximum=array[i];
			}
		}
		return maximum;
	}
}


void quad_tree::printx(quad_tree_node* roott){

	
	if(roott==nullptr)
		return;
	else if (roott!=nullptr){

		printx(roott->north_east);
		printx(roott->north_west);
		cout<<roott->city_name<<" ";
		printx(roott->south_west);
		printx(roott->south_east);

	}


}

int quad_tree::size_of_tree(){

 	return size;
}

void quad_tree::clearx(quad_tree_node* rootl){

	if (rootl==root){
		rootl=nullptr;
		cout<<"success"<<endl;
		size = 0;
		return;
	}

	if (root!=nullptr){
		clearx(rootl->north_east);
		clearx(rootl->north_west);
		clearx(rootl->south_west);
		clearx(rootl->south_east);
		rootl ->north_east = nullptr;
		rootl ->north_west = nullptr;
		rootl ->south_east = nullptr;
		rootl ->south_west = nullptr;

	}
}