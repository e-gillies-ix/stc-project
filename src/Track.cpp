#include <iostream>
#include <cmath>
#include <vector>
#include"Track.hpp"
#include"Event.hpp"

//Track defined as vector of events
//Holds a number of statisical properties

//Constructors
Track::Track()
: velocity(0.),slope(0.),intercept(0.),events()
{}

//From event vector
Track::Track(std::vector<Event> eventsIn )
: velocity(0.),slope(0.),intercept(0.),events(eventsIn)
{}

//Destructor
Track::~Track() {} 

//Printer
void Track::print() {
    for (std::vector<Event>::iterator it = events.begin() ; it != events.end(); ++it) it->print();
}

//Getters
double Track::getVelocity() const {return velocity;};
double Track::getSlope() const {return slope;};
double Track::getIntercept() const {return intercept;};
int Track::getNEvents() const {return events.size();};
//Setters
void Track::addEvent(Event nextEvent) {events.push_back(nextEvent);};
void Track::addEvent(short int raw) {events.push_back(Event(raw));};
void Track::fitTrack(){

    double sumX, sumY, sumT, sumX2, sumT2, sumXY, sumXT, sumYT;
    double meanX, meanY, meanT;
    double varyYT, varyXT, varyXX, varyXY, varyTT;
    double sumYprime, sumXYprime;
    for (std::vector<Event>::iterator it = events.begin() ; it != events.end(); ++it) {
        sumX+=it->getX();
        sumY+=it->getY();
        sumT+=it->getT();
        sumX2+=it->getX2();
        sumT2+=it->getT2();
        sumXY+=it->getXY();
        sumXT+=it->getXT();
        sumYT+=it->getYT();
    }
    meanX = sumX / events.size();
    meanY = sumY / events.size();
    meanT = sumT / events.size();

    intercept = meanY;

    varyYT = sumYT - meanY*sumT;  
    std::cout << "VaryYT : " << varyYT << std::endl;
    varyXT = sumXT - meanX*sumT;  
    std::cout << "VaryXT : " << varyXT << std::endl;
    varyXX = sumX2 - meanX*sumX;  
    std::cout << "VaryXX : " << varyXX << std::endl;
    varyXY = sumXY - meanX*sumY;  
    std::cout << "VarXY : " << varyXY << std::endl;
    varyTT = sumT2 - meanT*sumT;  
    std::cout << "VaryTT : " << varyTT << std::endl;

    velocity = ( varyYT + varyXY*varyXT/varyXX ) / (varyTT + varyXT*varyXT/varyXX); 
    intercept -= meanT*velocity; 

    for (std::vector<Event>::iterator it = events.begin() ; it != events.end(); ++it) {
        sumYprime += it->getY() - velocity*it->getT();
        sumYprime += it->getX()*it->getY() - velocity*it->getT();
    }

    slope = (sumXYprime - meanX*sumYprime) / varyXX;
    velocity = velocity * sqrt(1 + slope*slope )  / ( 1 - slope*slope);
    intercept -= meanX*slope;
}    


