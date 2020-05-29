//Rectangle.cpp
//Rectangle method definitions

#include <iostream>
#include <string>
#include "Rectangle.h"

using std::string;
using std::cout;
using std::endl;

/***************************************************************
Constructor: Rectangle::Rectangle(const string& color, int newHeight, int NewWidth)

Use: sets the data members of the rectangle object

Parameters: a reference to a string constant and two ints

Returns: -
***************************************************************/

Rectangle::Rectangle(const string& color, int newHeight, int newWidth) : Shape(color)
{
height = newHeight;
width = newWidth;
}

/***************************************************************
Function: void Rectangle::print() const

Use: prints rectangle information

Parameters: -

Returns: -
***************************************************************/

void Rectangle::print() const
{
	Shape::print();
        cout << " Rectangle, height " << height << " width " << width << " area " << get_area() << endl;
}

/***************************************************************
Function: double Rectangle::get_area() const

Use: calculates the area of the rectangle object

Parameters: -

Returns: a double representing the area of the rectangle
***************************************************************/

double Rectangle::get_area() const
{
        double area = (height * width);
        return area;
}


