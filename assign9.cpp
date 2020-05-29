//driver program for Shape class hierarchy

/*********************************************************************
   PROGRAM:    CSCI 241 Assignment 9
   PROGRAMMER: Tim Dickens
   LOGON ID:   z1804759
   DUE DATE:   Tuesday, May 2, 2017

   FUNCTION:   This program tests the functionality of the shape class
               inheritance heirarchy
*********************************************************************/
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>

#include "Shape.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Triangle.h"

using std::cout;
using std::endl;
using std::vector;
using std::string;

int main()
{

//create vector shapes

	vector<Shape *> shapes(6);

//initialize vector with shapes

	shapes[0] = new Triangle("red", 10, 5);
	shapes[1] = new Rectangle("black", 12, 2);
	shapes[2] = new Circle("orange", 100);
	shapes[3] = new Triangle("aqua", 13, 21);
	shapes[4] = new Circle("green", 10);
	shapes[5] = new Rectangle("blue", 16, 4);

	cout << "Printing All Shapes..." << endl << endl;

//process each element in vector shapes
	for( unsigned int i = 0; i < shapes.size(); i++)
	{
		shapes[i]->print();
	}

	cout << endl << "Printing Only Triangles..." << endl << endl;
//Process only triangles

	for( unsigned int i = 0; i < shapes.size(); i++)
	{
	//downcast pointer
	Triangle* trianglePtr = dynamic_cast<Triangle *>(shapes[i]);

	//determine if objct is a triangle and print if so
	if(trianglePtr != nullptr)
		{
		shapes[i]->print();
		}
	}
//release memory held by vector employees

	for( unsigned int i = 0; i < shapes.size(); i++)
	{
		delete shapes[i];
	}
cout << endl;
return 0;
}
