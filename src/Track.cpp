#include <iostream>
#include <cmath>
#include <vector>
#include"Track.hpp"
#include"Event.hpp"

//Track defined as vector of events
//Holds a number of statisical properties

//Constructors
    Track::Track()
: velocity(0.),slope(0.),intercept(0.),errVelocity(0.),errSlope(0.),errIntercept(0.),events()
{}

//From event vector
    Track::Track(std::vector<Event> eventsIn )
: velocity(0.),slope(0.),intercept(0.),events(eventsIn)
{}

//Destructor
Track::~Track() {} 

//Printers
void Track::printEvents() {
    for (std::vector<Event>::iterator evt = events.begin() ; evt != events.end(); ++evt) evt->print();
}
void Track::printTrack(){
    std::cout << "Fit values are: velocity=" << velocity << ", line= " << slope << "*x + " << intercept << std::endl; 
}

//Reset button
void Track::reset(){
   velocity = 0;
   slope = 0;
   intercept = 0;
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
void Track::setEvent(short int raw, int evt) {events[evt].setEvent(raw);};
//Fitters
void Track::firstFit(){

    //Add in trigger requirements that all x layers are hit
    sumX = 28; 
    sumXX = 140;
    varyXX = 42;
    meanX = 3.5;
    sumY = 0, sumXY = 0, varyXY = 0, meanY = 0, varyXY = 0, sumTT = 0;
    for (std::vector<Event>::iterator evt = events.begin() ; evt != events.end(); ++evt) {
        sumY+=evt->getY();
        sumXY+=evt->getXY();
        sumTT+=evt->getTT();
        //sumXX+=evt->getXX();
        //sumX+=evt->getX();
    }

    meanY = sumY / events.size();
    varyXY = sumXY - meanX*sumY;  
    //varyXX = sumXX - meanX*sumX;  
    //meanX = sumX / events.size();
    
    //First order slope
    slope = varyXY/varyXX; 
    intercept = meanY - slope*meanX;

}
bool Track::fitTrack(){
    double velocityNow = velocity;
    //Package relative position of hit to line in time variable using rough
    //fit.  Use this information to do full time and position fit.
    sumT = 0, sumXT = 0, sumYT = 0, meanT = 0;
    varyXT = 0, varyYT = 0, varyTT = 0;

    for (std::vector<Event>::iterator evt = events.begin() ; evt != events.end(); ++evt) {
        //Uneffected by relative position considerations
        //Flip the sign on time if hit is below track
        if (std::signbit(evt->getY() - slope*evt->getX() - intercept)){
            //std::cout << "Triggered on : " << evt->getX() << ", " << evt->getY() << ", " << evt->getT() << ") " << std::endl;  
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

    vPrime = ( varyXY*varyXT - varyYT*varyXX ) / (varyXT*varyXT - varyXX*varyTT); 
    slope = (varyXY - vPrime*varyXT)/varyXX;
    intercept = meanY - meanT*vPrime- meanX*slope; 
    velocity = vPrime/sqrt(1 + slope*slope );
    return velocityNow == velocity;
}

void Track::setError(){
    double errNum = (1 - 1/events.size()) * (sumX*sumXY - sumXX*sumY);
    double errDen = 2*(1 - 1/events.size()) * (sumX*sumXT - sumXX*sumT);
}


bool Track::checkTrack(){
    //Check for geometric ambiguities
    bool allNeg = true, allPos = true;
    for (std::vector<Event>::iterator evt = events.begin() ; evt != events.end(); ++evt) {
        if (std::signbit(evt->getY() - slope*evt->getX() - intercept)) allPos = false; 
        else allNeg = false;
    }
    if(allNeg || allPos) return false;
    else return true;
}
