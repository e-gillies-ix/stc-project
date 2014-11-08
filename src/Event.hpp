#ifndef EVENT_HPP
#define EVENT_HPP
#include<iostream>

//Simple Event Structure for Wire Reading

class Event {
    double x,y,t;

    public:
    //Constructors
    Event();
    Event(int, int, int);
    Event(double, double, double);
    Event(short int);

    //Destructor
    ~Event();
    
    //Member Fucntions
    void print();
    double getX() const, getY() const, getT() const;
    double getX2() const, getT2() const;
    double getXY() const, getXT() const, getYT() const;
};
#endif
//maybe store raw data input?
