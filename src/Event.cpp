#include <iostream>
#include <cmath>
#include"Event.hpp"

//Simple Event Structure for Wire Reading

//Constructors
Event::Event()
: x(0.),y(0.),t(0.)
{}

//From Physical Values Constructor
Event::Event(double xIn,double yIn,double tIn)
: x(xIn),y(yIn),t(tIn)
{}

//Implicit Constuctor from unalteted integer input
//Adds in Y offset
Event::Event(int xInteg, int yInteg, int tInteg)
: x((double) xInteg),y((double)yInteg + xInteg%2 == 0 ? 0 : 0.5), t((double)tInteg)
{}

//Constructor from raw 2 byte input
Event::Event(short int raw){
    //Takes bits [n,m] via (raw >> n) & ~(~0 << (m-n+1))
    x = (double)(raw & ~(~0 << 3));
    y = (double)((raw >> 3) & ~(~0 << 3));
    t = (double)((raw >> 6) & ~(~0 << 10));
}

//Destructor
Event::~Event() {} 

//Printer
void Event::print() {
    std::cout << "Event : (" << x <<", " << y <<", " << t <<")" << std::endl;
}

//Accessors
double Event::getX() const {return x;};
double Event::getY() const {return y;};
double Event::getT() const {return t;};
double Event::getX2() const {return x*x;};
double Event::getT2() const {return t*t;};
double Event::getXY() const {return x*y;};
double Event::getXT() const {return x*t;};
double Event::getYT() const {return y*t;};




//maybe we can  do (physical coords, integer coords, raw coords)
