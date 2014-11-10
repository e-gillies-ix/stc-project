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
    Track inTrack; 
    inTrack.addEvent(0,3,57.);
    inTrack.addEvent(1,3.5,19.);
    inTrack.addEvent(2,4,19.);
    inTrack.addEvent(3,4.5,57.);
    inTrack.addEvent(4,4,96.);
    inTrack.addEvent(5,4.5,57.);
    inTrack.addEvent(6,5,19.);
    inTrack.addEvent(7,5.5,19.);
    inTrack.print();
    inTrack.fitTrack();
    cout << "NEW LINE ------------------------------------" << endl;
    /*Track perfTrack = Track();
    perfTrack.addEvent(0.,3.,57.46957711);
    perfTrack.addEvent(1.,3.5,19.1565257);
    perfTrack.addEvent(2.,4.,19.1565257);
    perfTrack.addEvent(3.,4.5,57.46957711);
    perfTrack.addEvent(4.,4.,95.78262852);
    perfTrack.addEvent(5.,4.5,57.46957711);
    perfTrack.addEvent(6.,5.,19.1565257);
    perfTrack.addEvent(7.,5.5,19.1565257);
    perfTrack.print();
    perfTrack.fitTrack();
    */

}
//shift y
//cout << "Event " << n << ": " << (bitset<16>)eventRaw << endl;
/*cout << "Event " << n << ": " << (bitset<16>)eventRaw << endl;
  cout << "x: " << x[n] << ", " << (bitset<16>)x[n] << endl;
  cout << "y: " << y[n] << ", " << (bitset<16>)y[n] << endl;
  cout << "t: " << t[n] << ", " << (bitset<16>)t[n] << endl;*/
