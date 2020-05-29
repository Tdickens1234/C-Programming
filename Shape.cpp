//Shape.cpp
//Shape method definitions, no definitions for virtual methods

#include <string>
#include <iostream>
#include "Shape.h"

using std::string;
using std::cout;
using std::endl;

/***************************************************************
Constructor: Shape::Shape(const string& newColor)

Use: sets the color of the shape

Parameters: a reference to a string constant

Returns: -
***************************************************************/

Shape::Shape(const string& newColor)
{
	color = newColor;
}

/***************************************************************
Destructor: Shape::~Shape()

Use: compiler doesn't like not having one

Parameters: -

Returns: -
***************************************************************/

Shape::~Shape()
{
}

/***************************************************************
Function: void Shape::print() const

Use: prints the color of the shape

Parameters: -

Returns: -
***************************************************************/

void Shape::print() const
{
	cout << color;
}

