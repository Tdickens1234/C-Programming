//Circle.h
//Circle derived class

#ifndef CIRCLE_H
#define CIRCLE_H

#include "Shape.h"
#include <string>

class Circle : public Shape
{
        private:

        int radius;

        public:

        Circle(const std::string&, int = 0);

//overridden virtual functions

        virtual void print() const;
        virtual double get_area() const;

};

#endif

