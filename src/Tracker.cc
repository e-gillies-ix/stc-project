#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <bitset>

using namespace std;

int main(){

    int nEvents, nTracks, nPoints;
    short  event;
    std::vector<int> x,y,t;
    double sumX, sumY, sumT, sumX2, sumT2, sumXT, sumYT, sumXY;
    double meanX, meanY, meanT;
    double weightY;
    double slope1, slope2, slope3;
    double velocity;
    double interY1, interY2, interY3;
    double sumYminusT, sumXYminusT;
    double varyYT, varyXT, varyXX, varyXY, varyTT;

    nPoints = 8;

    //Set up our input stream
    ifstream testBinary("onetrack.raw", ios::binary | ios::in | ios::ate);
    nEvents = testBinary.tellg()/sizeof(event);
    nTracks = nEvents/8;
    cout << nEvents << endl;
    cout << nTracks << endl;

    //Look for correct event
    for (int n=0; n < nEvents; n++){
        testBinary.seekg(2*n,ios::beg);
        testBinary.read((char*)&event,sizeof(event));
        cout << "Event " << n << ": " << (bitset<16>)event << endl;

        //Extract time and stuff
        x.push_back(event & ~(~0 << (2-0+1)));
        y.push_back((event >> 3) & ~(~0 << (5-3+1)));
        t.push_back((event >> 6) & ~(~0 << (15-6+1)));
        //Read out our bits and values
        cout << "x: " << x[n] << ", " << (bitset<16>)x[n] << endl;
        cout << "y: " << y[n] << ", " << (bitset<16>)y[n] << endl;
        cout << "t: " << t[n] << ", " << (bitset<16>)t[n] << endl;
        //Line of best fit
        sumY += y[n];
        sumT += t[n];
        sumT2 += t[n]*t[n];
        sumXT += x[n]*t[n];
        sumYT += y[n]*t[n]; 
        sumXY += x[n]*y[n];
        //sumX2 += x[n]*x[n];
        //sumX += x[n];
    }
    sumX = 28;
    meanX = 3.5;
    sumX2 = 140;
    meanY = sumY/nPoints;
    meanT = sumT/nPoints;
    slope1 = (sumXY - sumX*meanY) / (sumX2 - sumX*meanX);
    
    varyYT = sumYT - meanY*sumT;  
    varyXT = sumXT - meanX*sumT;  
    varyXX = sumX2 - meanX*sumX;  
    varyXY = sumXY - meanX*sumY;  
    varyTT = sumT2 - meanT*sumT;  

    velocity = ( varyYT + varyXY*varyXT/varyXX ) / (varyTT + varyXT*varyXT/varyXX); 
    
    for ( int n = 0; n < nEvents; n++){
        sumYminusT += y[n] - velocity*t[n];
        sumXYminusT += x[n]*(y[n] - velocity*t[n]);
    }

    slope2 = (sumXYminusT - meanX*sumYminusT) / varyXX;

    //Close the file
    testBinary.close();


    /*
    cout << "sum x : " << sumX << endl; 
    cout << "mean x  : " << meanX << endl; 
    cout << "sum x2 : " << sumX2 << endl; 
    */

    //Find line of best fit
        

    double den = 0;
    double num = 0;

    for (int m=0; m < nEvents; m++){
    
       num += (x[m] - meanX) * (y[m] - meanY); 
       den += (x[m] - meanX) * (x[m] - meanX); 

    }

    slope3 = num/den;

    interY1 = meanY - slope1*meanX;
    interY2 = meanY - slope2*meanX;
    interY3 = meanY - slope3*meanX;

    cout << "Line 1 is: " << interY1 << " + " << slope1 << "*x " << endl;
    cout << "Line 2 is: " << interY2 << " + " << slope2 << "*x " << endl;
    cout << "Line 3 is: " << interY3 << " + " << slope3 << "*x " << endl;

    //Output testing
    ofstream testOut;
    testOut.open("testOutput.dat");
    testOut << "hello world" << endl;
    testOut.close();
}
//shift y
