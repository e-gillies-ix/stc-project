#include "Riostream.h"

void tracks() {

    ifstream in;
    in.open("trackData.dat");
    Float_t velocity,slope,angle;
    Int_t nlines = 0;
    TFile *f = new TFile("trackData.root","RECREATE");
    TH1F *h1 = new TH1F("h1","Velocity Distribution",100,0.002028,0.002408);
    TH1F *h2 = new TH1F("h1","Slope Distribution",8,-0.08913,0.2658);
    TNtuple *ntuple = new TNtuple("ntuple","data from ascii file","velocity:slope:angle");
    while (1) {
        in >> velocity >> slope >> angle;
        if (!in.good()) break;
        if (nlines < 5) printf("velocity=%8f, slope=%8f, angle=%8f\n",velocity,slope,angle);
        h1->Fill(velocity);
        h2->Fill(slope);
        ntuple->Fill(velocity,slope,angle);
        nlines++;
    }
    printf(" found %d points\n",nlines);
    in.close();
    f->Write();
}
/*Average Velocity = 0.00239217
Velocity  Range= (0.00202891, 0.00240725)
Average Slope = 0.0898062
Slope  Range= (-0.0891341, 0.265799)
*/
