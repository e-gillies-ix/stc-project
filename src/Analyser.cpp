#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <bitset>
#include <climits>

#include"Event.hpp"
#include"Track.hpp"

using namespace std;

int main(){

    int totalEvents, totalTracks;
    short int  eventRaw;
    Track thisTrack;
    double averageVelo = 0;
    double averageSlope = 0;
    double maxVelocity = 0, minVelocity = LLONG_MAX;
    double maxSlope = -LLONG_MAX, minSlope = LLONG_MAX;

    short nullEvent = 0;
    int eventsTrack = 8;
    
    for (int evt = 0 ; evt < eventsTrack ; evt++) thisTrack.addEvent(nullEvent);
    //Set up our input stream
    ofstream asciiOut("trackData.dat"); 
    ifstream testBinary("manytracks.raw", ios::binary | ios::in | ios::ate);
    totalEvents = testBinary.tellg()/sizeof(eventRaw);
    totalTracks = totalEvents/eventsTrack;
    //Loop over events in file
    for  (int m=0; m < totalTracks; m++) {
        if (m%(totalTracks/100)== 0)  cout << "M = " << m << endl;
        //Look for correct event
        for (int n=0; n < eventsTrack; n++){
            testBinary.seekg(2*n + 16*m,ios::beg);
            testBinary.read((char*)&eventRaw,sizeof(eventRaw));
            //Extract Events
            thisTrack.setEvent(eventRaw,n);
            //use iterator here EG
        }
        //thisTrack.printEvents();
        thisTrack.firstFit();
        //thisTrack.printEvents();
        bool fit = false;
        while (!fit){
            fit = thisTrack.fitTrack();
            //thisTrack.printTrack();
        }
        //Output some max and min values for root
        if (thisTrack.getVelocity() > maxVelocity) maxVelocity = thisTrack.getVelocity();
        if (thisTrack.getVelocity() < minVelocity) minVelocity = thisTrack.getVelocity();
        if (thisTrack.getSlope() > maxSlope) maxSlope = thisTrack.getSlope();
        if (thisTrack.getSlope() < minSlope) minSlope = thisTrack.getSlope();
        //Store the values
        averageVelo += thisTrack.getVelocity();
        averageSlope += thisTrack.getSlope();
        asciiOut << thisTrack.getVelocity() << " " << thisTrack.getSlope() << " " << atan(thisTrack.getSlope()) << endl; 
        //Checking the track
        if (!thisTrack.checkTrack()){ 
            cout<< "Event M = " << m << "is bad." << endl;
            thisTrack.printEvents();
            thisTrack.printTrack();
        }
        thisTrack.reset();
    }
    //Close the file
    testBinary.close();
    asciiOut.close();
    cout << "Average Velocity = " << averageVelo/totalTracks << endl;
    cout << "Velocity  Range= (" << minVelocity << ", " << maxVelocity << ")" << endl;
    cout << "Average Slope = " << averageSlope/totalTracks << endl;
    cout << "Slope  Range= (" << minSlope << ", " << maxSlope << ")" << endl;

}
//shift y
//cout << "Event " << n << ": " << (bitset<16>)eventRaw << endl;
/*cout << "Event " << n << ": " << (bitset<16>)eventRaw << endl;
  cout << "x: " << x[n] << ", " << (bitset<16>)x[n] << endl;
  cout << "y: " << y[n] << ", " << (bitset<16>)y[n] << endl;
  cout << "t: " << t[n] << ", " << (bitset<16>)t[n] << endl;*/
