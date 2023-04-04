// -----------------------------------------------------------------
// sigenmax2870 - a tool to configure  LTDZ MAX2870 signal generator
//                compatible boards by pc using serial port
// Copyright (C) 2023  Gabriele Bonacini
//
// This program is distributed under dual license:
// - Creative Comons Attribution-NonCommercial 4.0 International (CC BY-NC 4.0) License 
// for non commercial use, the license has the following terms:
// * Attribution — You must give appropriate credit, provide a link to the license, 
// and indicate if changes were made. You may do so in any reasonable manner, 
// but not in any way that suggests the licensor endorses you or your use.
// * NonCommercial — You must not use the material for commercial purposes.
// A copy of the license it's available to the following address:
// http://creativecommons.org/licenses/by-nc/4.0/
// For commercial use a specific license is available contacting the author.
// -----------------------------------------------------------------

#include <stdlib.h>

#include <iostream>

#include <sigenmax2870.hpp>
#include <parseCmdLine.hpp>
#include <safeconversion.hpp>

using std::cerr;
using std::string;
using std::stoul;
using std::stoi;
using parcmdline::ParseCmdLine;
using sigenmax2870::Sigenmax2870;
using sigenmax2870::frequencyType;
using sigenmax2870::amplificationType;
using sigenmax2870::Sigenmax2870Exception;
using sigenmax2870::Termios;
using safeconv::safeUint32T;

[[noreturn]]
void usage(char* pname);

int main(int argc, char** argv){
    constexpr char    flags[]    { "hpf:d:a:" };
    ParseCmdLine pcl(argc, argv, flags);
    if(pcl.getErrorState()){
        string exitMsg{string("Invalid  parameter or value").append(pcl.getErrorMsg())};
        cerr << exitMsg << "\n";
        usage(argv[0]);
    }

    if(pcl.isSet('h'))
        usage(argv[0]);

    if(!pcl.isSet('d') || !pcl.isSet('f')){
        cerr << "-d and -f are mandatory\n";
        usage(argv[0]);
    }

    string path        = pcl.getValue('d');
    frequencyType freq = safeUint32T(stoi(pcl.getValue('f')));

    amplificationType amp = 1;
    if(pcl.isSet('a') )
        amp = safeUint32T(stoi(pcl.getValue('a')));

    try{
    
       Sigenmax2870 sigen(path, freq, amp);
       sigen.send();

       if(pcl.isSet('p'))
         sigen.dump();

    } catch(Sigenmax2870Exception& ex){
       cerr << "Error: " << ex.what() << "\n";
    } 

    return 0;

}

void usage(char* pname){
    cerr << "Usage:\n" << pname << " [-d device_path] [-f frequency] < -a amplification > < -p >\n"
         << "or\n"
         << pname << " [ -h ]\n"
         << "[-d device_path] full path of the serial device\n"
         << "[-f frequency] frequency to set (kHz)\n"
         << "[-a amplification] amplification factor ( 1 | 2 | 3 | 4 -> default: 1)\n"
         << "[ -p ] dump configuration \n"
         << "\nExample: \n"
         << pname << " -d /dev/tty.USB01 -f 10333 -a 2\n"
         << "\nSet the signal generator connected as /dev/tty.USB01 to 10.333 MHz using amplification setting 2 ( -1 dB)\n";
    exit(1);
}

