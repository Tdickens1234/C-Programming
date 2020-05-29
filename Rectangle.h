//Rectangle.h
//Rectangle derived class

#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Shape.h"
#include <string>

class Rectangle : public Shape
{
        private:

        int height;
	int width;

        public:

        Rectangle(const std::string&, int = 0, int = 0);

//overridden virtual functions

        virtual void print() const;
        virtual double get_area() const;

};

#endif

