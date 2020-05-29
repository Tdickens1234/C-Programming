//Shape.h
//Shape abstract base class

#ifndef SHAPE_H
#define SHAPE_H

#include <string>

class Shape
{
	private:

	std::string color;

	public:

	Shape(const std::string&);
	virtual ~Shape();

//pure virtual method making the class abstract

	virtual double get_area() const = 0;
	virtual void print() const;

};

#endif
