#include <iostream>
#include <string>
#include "QuadNode.cpp"

using namespace std;

string input_line;

int main (){
	quad_tree tree;

	while (!cin.eof()){

		getline(cin, input_line);

		int blank_space =0;

		blank_space= input_line.find(' ');

		string command= input_line.substr(0, blank_space);

		if (input_line == ""){
			cin.ignore(256, '\n');
		}

		input_line.erase(0, blank_space+1);

		if (command == "i"){

			int semi_colon_1=input_line.find(';');								//find the first semicolon
			string city_name = input_line.substr(0, semi_colon_1);  //store city name in string
			input_line.erase(0, semi_colon_1+1);	//erase the used string


			int semi_colon_2=input_line.find(';');								//find second semicolon
			string latitude=input_line.substr(0, semi_colon_2);	
			double x=stod(latitude);
			input_line.erase(0, semi_colon_2+1);

			int semi_colon_3=input_line.find(';');								//find the third semicolon
			string longitude=input_line.substr(0, semi_colon_3);
			double y=stod(longitude);
			input_line.erase(0, semi_colon_3+1);

			int semi_colon_4=input_line.find(';');
			string population=input_line.substr(0, semi_colon_4);
			int p=stoi(population);
			input_line.erase(0, semi_colon_4+1);

			int semi_colon_5=input_line.find(';');
			string cost_of_living=input_line.substr(0, semi_colon_5);
			int r=stoi(cost_of_living);
			input_line.erase(0, semi_colon_5+1);

			int s=stoi(input_line);
			bool val=tree.insert(city_name, x, y, p, r, s);
			if (val){
				cout<<"success"<<endl;
			}
			else if (!val){
				cout<<"failure"<<endl;
			}

		}
		else if (command == "size"){
			int sz=tree.size_of_tree();
			cout<<"tree size "<<sz<<endl;
		}

		else if (command == "s"){

			int semi_colon_6 = input_line.find(';');
			string x=input_line.substr(0, semi_colon_6);
			double x1=stod(x);
			input_line.erase(0, semi_colon_6+1);

			double y1=stod(input_line);
			tree.searchx(x1, y1);

		}

		else if (command == "q_max"){
			
			int semi_colon_1 = input_line.find(';');
			string x=input_line.substr(0, semi_colon_1);
			double x1=stod(x);
			input_line.erase(0, semi_colon_1+1);

			int semi_colon_2 = input_line.find(';');
			string y = input_line.substr(0, semi_colon_2);
			double y1 = stod(y);
			input_line.erase(0, semi_colon_2+1);

			int semi_colon_3 = input_line.find(';');
			string d = input_line.substr(0, semi_colon_3);
			input_line.erase(0, semi_colon_3+1);

			string attrib = input_line;

			quad_tree_node* point=tree.get_root()->search_helper(x1, y1);

			if (point!=nullptr){
				quad_tree_node* direction = point -> direction(d);
				if (direction !=nullptr){
					int max= tree.q_max(direction, attrib);
					cout <<"max "<<max<<endl;
				}
				else {
					cout<<"failure"<<endl;
				}

			}

			if (point==nullptr){
				cout<<"failure"<<endl;
			}

		}

		else if (command == "q_min"){


			int semi_colon_1 = input_line.find(';');
			string x=input_line.substr(0, semi_colon_1);
			double x1=stod(x);
			input_line.erase(0, semi_colon_1+1);

			int semi_colon_2 = input_line.find(';');
			string y = input_line.substr(0, semi_colon_2);
			double y1 = stod(y);
			input_line.erase(0, semi_colon_2+1);

			int semi_colon_3 = input_line.find(';');
			string d = input_line.substr(0, semi_colon_3);
			input_line.erase(0, semi_colon_3+1);

			string attrib = input_line;

			quad_tree_node* point=tree.get_root()->search_helper(x1, y1);

			if (point!=nullptr){
				quad_tree_node* direction = point -> direction(d);
				if (direction !=nullptr){
					int mini= tree.q_min(direction, attrib);
					cout <<"min "<<mini<<endl;
				}
				else {
					cout<<"failure"<<endl;
				}

			}

			if (point==nullptr){
				cout<<"failure"<<endl;
			}

		}

		else if (command == "q_total"){

			int semi_colon_1 = input_line.find(';');
			string x=input_line.substr(0, semi_colon_1);
			double x1=stod(x);
			input_line.erase(0, semi_colon_1+1);

			int semi_colon_2 = input_line.find(';');
			string y = input_line.substr(0, semi_colon_2);
			double y1 = stod(y);
			input_line.erase(0, semi_colon_2+1);

			int semi_colon_3 = input_line.find(';');
			string d = input_line.substr(0, semi_colon_3);
			input_line.erase(0, semi_colon_3+1);

			string attrib = input_line;


			quad_tree_node* point=tree.get_root()->search_helper(x1, y1);

			if (point!=nullptr){
				quad_tree_node* direction = point -> direction(d);
				if (direction !=nullptr){
					int total= tree.q_total(direction, attrib);
					cout <<"total "<<total<<endl;
				}
				else {
					cout<<"failure"<<endl;
				}

			}

			if (point==nullptr){
				cout<<"failure"<<endl;
			}

		}

		else if (command == "print"){

			tree.printx(tree.get_root());
			cout << endl;
		}

		else if (command == "clear"){

			tree.clearx(tree.get_root());
		}
	}

	return 0;
}

