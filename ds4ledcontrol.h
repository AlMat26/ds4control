#ifndef DS4LEDCONTROL_H
#define DS4LEDCONTROL_H

#include <filesystem>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>

namespace fs = std::filesystem;

enum RGB_SUBSEQUENCES {
    SS_RED, SS_GREEN, SS_BLUE
};

class ds4ledControl
{
private:
    std::string ledPath;
    std::vector <std::string> ledCatalogs;
    unsigned int RGBsubsequence[3]; //subsequence in ledCatalog folder

    std::ofstream outFileRed, outFileGreen, outFileBlue;

    unsigned int red, green, blue;

public:
    ds4ledControl();

    unsigned int getRed() {
        return red;
    }
    unsigned int getGreen() {
        return red;
    }
    unsigned int getBlue() {
        return red;
    }


    void setRed ( unsigned int );
    void setGreen ( unsigned int );
    void setBlue ( unsigned int );

    void wait (unsigned int time) {
        clock_t begin = clock ();
        while ( clock () - begin < time ) {}
    }
};

#endif // DS4LEDCONTROL_H
