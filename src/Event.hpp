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
    //Accessors
    double getX() const, getY() const, getT() const;
    double getXX() const, getTT() const;
    double getXY() const, getXT() const, getYT() const;
    //Setters
    void setX(double), setY(double), setT(double), setEvent(short);
};
#endif
//maybe store raw data input?
