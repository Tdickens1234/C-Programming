//Circle.cpp
//Circle method definitions, no definitions for virtual methods

#define PI 3.14159265358979323846264338327950288419716939937610582097494459

#include <iostream>
#include <string>
#include "Circle.h"

using std::string;
using std::cout;
using std::endl;
/***************************************************************
Constructor: Circle::Circle(const string& color, int newRadius) : Shape(color)

Use: sets the data members of the circle object

Parameters: a reference to a string constant and an int

Returns: -
***************************************************************/

Circle::Circle(const string& color, int newRadius) : Shape(color)
{
radius = newRadius;
}

/***************************************************************
Function: void Circle::print() const

Use: prints circle information

Parameters: -

Returns: -
***************************************************************/

void Circle::print() const
{
	Shape::print();
        cout << " circle, radius " << radius << " area " << get_area() << endl;
}

/***************************************************************
Function: double Circle::get_area() const

Use: calculates the area of the circle object

Parameters: -

Returns: a double representing the area of the Circle
***************************************************************/

double Circle::get_area() const
{
	double area = PI * (radius * radius);
	return area;
}


