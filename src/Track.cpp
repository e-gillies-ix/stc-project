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
void Track::addEvent(double x, double y, double t) {events.push_back(Event(x,y,t));};
void Track::addEvent(Event nextEvent) {events.push_back(nextEvent);};
void Track::addEvent(short int raw) {events.push_back(Event(raw));};
void Track::firstFit(){

    sumX = 0, sumY = 0, sumXX = 0, sumXY = 0, varyXY = 0, meanX = 0, meanY = 0;
    varyXX = 0, varyXY = 0, sumTT = 0;
    for (std::vector<Event>::iterator evt = events.begin() ; evt != events.end(); ++evt) {
        sumX+=evt->getX();
        sumY+=evt->getY();
        sumXX+=evt->getXX();
        sumXY+=evt->getXY();
        sumTT+=evt->getTT();
    }

    meanX = sumX / events.size();
    meanY = sumY / events.size();
    varyXX = sumXX - meanX*sumX;  
    varyXY = sumXY - meanX*sumY;  

    //First order slope
    slope = varyXY/varyXX; 
    intercept = meanY - slope*meanX;
    std::cout << "First Order Slope is: " << intercept << " + " << slope << "*x " << std::endl;

}
void Track::fitTrack(){

    //Package relative position of hit to line in time variable using rough
    //fit.  Use this information to do full time and position fit.
    sumT = 0, sumXT = 0, sumYT = 0, meanT = 0;
    varyXT = 0, varyYT = 0, varyTT = 0;

    for (std::vector<Event>::iterator evt = events.begin() ; evt != events.end(); ++evt) {
        //Uneffected by relative position considerations
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
    varyTT = sumTT - meanT*sumT;  

    velocity = ( varyXY*varyXT - varyYT*varyXX ) / (varyXT*varyXT - varyXX*varyTT); 
    slope = (varyXY - velocity*varyXT)/varyXX;
    intercept = meanY - meanT*velocity- meanX*slope; 
    velocity = velocity/sqrt(1 + slope*slope );

}
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
/*std::cout << "MeanT : " << meanT << std::endl;
  std::cout << "MeanY : " << meanY << std::endl;
  std::cout << "MeanX : " << meanX << std::endl;
  std::cout << "VaryYT : " << varyYT << std::endl;
  std::cout << "VaryXT : " << varyXT << std::endl;
  std::cout << "VaryXX : " << varyXX << std::endl;
  std::cout << "VaryTT : " << varyTT << std::endl;
  std::cout << "VaryXY : " << varyXY << std::endl;
  
  
    std::cout << "MeanT : " << meanT << std::endl;
    std::cout << "MeanY : " << meanY << std::endl;
    std::cout << "MeanX : " << meanX << std::endl;
    std::cout << "VaryYT : " << varyYT << std::endl;
    std::cout << "VaryXT : " << varyXT << std::endl;
    std::cout << "VaryXX : " << varyXX << std::endl;
    std::cout << "VaryTT : " << varyTT << std::endl;
    std::cout << "VaryXY : " << varyXY << std::endl;

    std::cout << "Second Order Slope is: " << intercept << " + " << slope << "*x " << std::endl;
    std::cout << "Velocity Prime: " << velocity << std::endl;
    std::cout << "Velocity: " << velocity << std::endl;

            std::cout << "Triggered on : " << evt->getX() << ", " << evt->getY() << ", " << evt->getT() << ") " << std::endl;  
  */

