#include "ds4ledcontrol.h"

ds4ledControl::ds4ledControl () {
    ledPath = "/sys/class/leds";

    for ( const auto & entry : fs::directory_iterator (ledPath)) {

        std::string catalog = entry.path ();

        if ( catalog.find("000") != std::string::npos ) {

            ledCatalogs.push_back (catalog);
        }
    }

    std::ifstream ifile;

    for ( int i = 0; i < ledCatalogs.size(); i++ ) {

        ifile.open(ledCatalogs [i] + "/brightness");

        if ( ledCatalogs[i].find("red") != std::string::npos ) {

            ifile >> red;
            RGBsubsequence[SS_RED] = i;

        } else if ( ledCatalogs[i].find("green") != std::string::npos ) {

            ifile >> green;
            RGBsubsequence[SS_GREEN] = i;

        } else if ( ledCatalogs[i].find("blue") != std::string::npos ) {

            ifile >> blue;
            RGBsubsequence[SS_BLUE] = i;
        }

        ifile.close();
    }
}

void ds4ledControl::setRed ( unsigned int number ) {

    red = number;
    outFileRed.open ( ledCatalogs [RGBsubsequence[SS_RED]] + "/brightness" );
    outFileRed << red;
    outFileRed.close();
}

void ds4ledControl::setGreen ( unsigned int number ) {

    green = number;
    outFileGreen.open ( ledCatalogs [RGBsubsequence[SS_GREEN]] + "/brightness" );
    outFileGreen << green;
    outFileGreen.close();
}

void ds4ledControl::setBlue ( unsigned int number ) {

    blue = number;
    outFileBlue.open ( ledCatalogs [RGBsubsequence[SS_BLUE]] + "/brightness" );
    outFileBlue << blue;
    outFileBlue.close();
}
