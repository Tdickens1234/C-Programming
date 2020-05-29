//Triangle.h
//Triangle derived class

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Shape.h"
#include <string>

class Triangle : public Shape
{
        private:

        int height, base;

        public:

        Triangle(const std::string&, int = 0, int = 0);

//overridden virtual functions

        virtual void print() const;
        virtual double get_area() const;

};

#endif

