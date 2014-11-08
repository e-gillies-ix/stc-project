#ifndef TRACK_HPP
#define TRACK_HPP
#include<iostream>
#include <vector>
#include"Event.hpp"

//Track defined as vector of events
//Holds a number of statisical properties

class Track {
    //Physical Properties
    double velocity,slope,intercept;
    std::vector<Event> events;

    public:
    //Constructors
    Track();
    Track(std::vector<Event>);

    //Destructor
    ~Track();
    
    //Member Fucntions
    void print();
    //Getters
    std::vector<Event> getEvents() const; 
    double getVelocity() const, getSlope() const, getIntercept() const;
    int getNEvents() const;
    //Setters
    void addEvent(Event);
    void addEvent(short int);
    void fitTrack();
    void fitTrackBad();
};
#endif

