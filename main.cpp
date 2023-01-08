#include<iostream>
#include "Xml.h"
using namespace std;
using namespace xml;



int main() {

	Xml root;
	root.load("test.xml");
	cout << root.str() << endl;
	return 0;


	/*Xml s1("student");
	s1.text("boy");
	s1.attrs("id", 1);

	Xml s2("student");
	s2.text("girl");
	s2.attrs("id", "2");

	Xml root("students");
	root.append(s1);
	root.append(s2);*/
	//root[1] = s2;

	//root.remove("student");

	/*for (auto it = root.begin(); it != root.end(); it++) {
	
		cout << (*it).str();
	}*/

	/*for (int i = 0; i < root.size(); i++) {
		cout << root[i].str();
	}*/
	//cout << root.str() << endl;

	

}