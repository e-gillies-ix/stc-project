#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <bitset>

#include"Event.hpp"
#include"Track.hpp"

using namespace std;

int main(){

    int nEvents, nTracks, nPoints;
    short int  eventRaw;
    Track thisTrack;
    std::vector<Event> track;

    nEvents = 8;

    //Set up our input stream
    //Test for hits along bottom line, i.e. y=0, at 100 time unit delay
    //to hit wires half a cell unit away on odd x.
    short testFlat[]= {0,6401,2,6403,4,6405,6,6407};
    for (int n=0; n < nEvents; n++){
        //Extract Events
        thisTrack.addEvent(testFlat[n]);
    }
    thisTrack.print();
    thisTrack.fitTrackBad();
    cout << "Line 3 is: " << thisTrack.getIntercept() << " + " << thisTrack.getSlope() << "*x " << endl;
    thisTrack.fitTrack();
    cout << "Line 3 is: " << thisTrack.getIntercept() << " + " << thisTrack.getSlope() << "*x " << endl;

    short testSym[] = {0,1537,3082,4619,4636,3101,1574,39};
    Track thatTrack;
    for (int n=0; n < nEvents; n++){
        //Extract Events
        thatTrack.addEvent(testSym[n]);
    }
    thatTrack.print();
    thisTrack.fitTrackBad();
    cout << "Line 3 is: " << thatTrack.getIntercept() << " + " << thatTrack.getSlope() << "*x " << endl;
    thatTrack.fitTrack();
    cout << "Line 3 is: " << thatTrack.getIntercept() << " + " << thatTrack.getSlope() << "*x " << endl;

}
//shift y
//cout << "Event " << n << ": " << (bitset<16>)eventRaw << endl;
        /*cout << "Event " << n << ": " << (bitset<16>)eventRaw << endl;
        cout << "x: " << x[n] << ", " << (bitset<16>)x[n] << endl;
        cout << "y: " << y[n] << ", " << (bitset<16>)y[n] << endl;
        cout << "t: " << t[n] << ", " << (bitset<16>)t[n] << endl;*/
