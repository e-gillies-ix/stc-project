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
    for (std::vector<Event>::iterator evt = events.begin() ; evt != events.end(); ++evt) evt->print();
}

//Getters
double Track::getVelocity() const {return velocity;};
double Track::getSlope() const {return slope;};
double Track::getIntercept() const {return intercept;};
int Track::getNEvents() const {return events.size();};
//Setters
void Track::addEvent(Event nextEvent) {events.push_back(nextEvent);};
void Track::addEvent(short int raw) {events.push_back(Event(raw));};
void Track::fitTrackBad(){

    double sumX, sumY, sumT, sumX2, sumT2, sumXY, sumXT, sumYT;
    double meanX, meanY, meanT;
    double varyYT, varyXT, varyXX, varyXY, varyTT;
    double sumYprime, sumXYprime;
    for (std::vector<Event>::iterator evt = events.begin() ; evt != events.end(); ++evt) {
        sumX+=evt->getX();
        sumY+=evt->getY();
        sumT+=evt->getT();
        sumX2+=evt->getX2();
        sumT2+=evt->getT2();
        sumXY+=evt->getXY();
        sumXT+=evt->getXT();
        sumYT+=evt->getYT();
    }
    meanX = sumX / events.size();
    meanY = sumY / events.size();
    meanT = sumT / events.size();
    intercept = meanY;

    varyYT = sumYT - meanY*sumT;  
    varyXT = sumXT - meanX*sumT;  
    varyXX = sumX2 - meanX*sumX;  
    varyXY = sumXY - meanX*sumY;  
    varyTT = sumT2 - meanT*sumT;  

    velocity = ( varyYT + varyXY*varyXT/varyXX ) / (varyTT + varyXT*varyXT/varyXX); 
    std::cout << "Velocity : " << velocity << std::endl;
    intercept -= meanT*velocity; 

    for (std::vector<Event>::iterator evt = events.begin() ; evt != events.end(); ++evt) {
        sumYprime += evt->getY() - velocity*evt->getT();
        sumXYprime += evt->getX()*(evt->getY() - velocity*evt->getT());
    }

    std::cout << "sumXYprime : " << sumXYprime << std::endl;
    std::cout << "sumYprime : " << sumYprime << std::endl;
    std::cout << "Velocity : " << velocity << std::endl;
    slope = (sumXYprime - meanX*sumYprime) / varyXX;
    velocity = velocity * sqrt(1 + slope*slope )  / ( 1 - slope*slope);
    intercept -= meanX*slope;

    /*std::cout << "MeanT : " << meanT << std::endl;
      std::cout << "MeanY : " << meanY << std::endl;
      std::cout << "MeanX : " << meanX << std::endl;
      std::cout << "VaryYT : " << varyYT << std::endl;
      std::cout << "VaryXT : " << varyXT << std::endl;
      std::cout << "VaryXX : " << varyXX << std::endl;
      std::cout << "VaryTT : " << varyTT << std::endl;
      std::cout << "VaryXY : " << varyXY << std::endl;
      */

}    


void Track::fitTrack(){

    //First do rough fit on line to find where hits are relative to line
    double sumX, sumY, sumX2, sumXY, varyYX, meanX, meanY;
    double varyXX, varyXY;

    for (std::vector<Event>::iterator evt = events.begin() ; evt != events.end(); ++evt) {
        sumX+=evt->getX();
        sumY+=evt->getY();
        sumX2+=evt->getX2();
        sumXY+=evt->getXY();
    }
    
    meanX = sumX / events.size();
    meanY = sumY / events.size();
    varyXX = sumX2 - meanX*sumX;  
    varyXY = sumXY - meanX*sumY;  
    varyYX = sumXY - meanY*sumX;  

    //First order slope
    slope = varyXY/varyXX; 
    intercept = meanY - slope*meanX;

    //Package relative position of hit to line in time variable using rough
    //fit.  Use this information to do full time and position fit.
    double sumT, sumT2, sumXT, sumYT, meanT;
    double varyXT, varyYT, varyTT, varyTX;
    
    for (std::vector<Event>::iterator evt = events.begin() ; evt != events.end(); ++evt) {
        //Uneffected by relative position considerations
        sumT2+=evt->getT2();
        //Flip the sign on time if hit is below track
        if (std::signbit(evt->getY() - slope*evt->getX() - intercept)){
        sumT-=evt->getT();
        sumXT-=evt->getXT();
        sumYT-=evt->getYT();
        }
        //Do not flip if it is above track
        else{
        sumT+=evt->getT();
        sumXT+=evt->getXT();
        sumYT+=evt->getYT();
        }
    }    

    meanT = sumT / events.size();
    varyYT = sumYT - meanY*sumT;  
    varyXT = sumXT - meanX*sumT;  
    varyTT = sumT2 - meanT*sumT;  
    varyTX = sumXT - meanT*sumX;

    velocity = ( varyYX*varyXT - varyYT*varyXX ) / (varyTX*varyTX - varyXX*varyTT); 
    slope = (varyYX - velocity*varyTX)/varyXX;
    intercept = meanY - meanT*velocity- meanX*slope; 

    std::cout << "Velocity Prime: " << velocity << std::endl;
/*
    double sumYprime, sumXYprime;
    for (std::vector<Event>::iterator evt = events.begin() ; evt != events.end(); ++evt) {
        sumYprime += evt->getY() - velocity*evt->getT();
        sumXYprime += evt->getX()*(evt->getY() - velocity*evt->getT());
    }

    std::cout << "sumXYprime : " << sumXYprime << std::endl;
    std::cout << "sumYprime : " << sumYprime << std::endl;
    slope = (sumXYprime - meanX*sumYprime) / varyXX;
*/    
    velocity = velocity/sqrt(1 + slope*slope );
    std::cout << "Velocity : " << velocity << std::endl;

    /*std::cout << "MeanT : " << meanT << std::endl;
      std::cout << "MeanY : " << meanY << std::endl;
      std::cout << "MeanX : " << meanX << std::endl;
      std::cout << "VaryYT : " << varyYT << std::endl;
      std::cout << "VaryXT : " << varyXT << std::endl;
      std::cout << "VaryXX : " << varyXX << std::endl;
      std::cout << "VaryTT : " << varyTT << std::endl;
      std::cout << "VaryXY : " << varyXY << std::endl;
      */

}    


