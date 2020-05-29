//Triangle.cpp
//Triangle method definitions

#include <iostream>
#include <string>
#include "Triangle.h"

using std::string;
using std::cout;
using std::endl;

/***************************************************************
Constructor: Triasngle::Triangle(const string& color, int newHeight, int newBase)

Use: sets the data members of the Triangle object

Parameters: a referencce to a string object and two ints

Returns: -
***************************************************************/

Triangle::Triangle(const string& color, int newHeight, int newBase) : Shape(color)
{
	height = newHeight;
	base = newBase;
}

/***************************************************************
Function: void Triangle::print() const

Use: prints triangle information

Parameters: -

Returns: -
***************************************************************/

void Triangle::print() const
{
	Shape::print();
        cout << " Triangle, height " << height << " base " << base << " area " << get_area() << endl;
}

/***************************************************************
Function: double Triangle::get_area() const

Use: calculates the area of the triangle object

Parameters: -

Returns: a double representing the area of the triangle
***************************************************************/

double Triangle::get_area() const
{
        double area = .5 * (base * height);
        return area;
}



