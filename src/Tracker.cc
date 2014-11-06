#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <bitset>

using namespace std;

int main(){

    int nEvents, nTracks;
    short  event;
    int x,y,t;

    //Set up our 
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
        x = event & ~(~0 << (2-0+1));
        y = (event >> 3) & ~(~0 << (5-3+1));
        t = (event >> 6) & ~(~0 << (15-6+1));
        cout << "x: " << x << ", " << (bitset<16>)x << endl;
        cout << "y: " << y << ", " << (bitset<16>)y << endl;
        cout << "t: " << t << ", " << (bitset<16>)t << endl;

    }

    testBinary.close();

    //Output testing
    ofstream testOut;
    testOut.open("testOutput.dat");
    testOut << "hello world" << endl;
    testOut.close();
}

/*
   streampos size;
   char * memblock;

   ifstream file ("onetrack.raw", ios::in|ios::binary|ios::ate);
   if (file.is_open())
   {
   size = file.tellg();
   memblock = new char [size];
   file.seekg (0, ios::beg);
   file.read (memblock, size);
   cout << (bitset<16>)*memblock << endl;
   cout << sizeof(memblock) << endl;
   file.close();

   cout << "the entire file content is in memory";

   delete[] memblock;
   }
   else cout << "Unable to open file";
   */


