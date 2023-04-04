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

#include <sigenmax2870.hpp>

#include <fcntl.h>
#include <unistd.h>
#ifdef __linux__
#include <string.h>
#endif

#include <iostream>
#include <filesystem>

#include <checkendianess.hpp>
#include <safeconversion.hpp>

namespace sigenmax2870 {

using std::string;
using std::filesystem::exists;
using std::cerr;
using std::hex;
using std::to_string;
using safeconv::safeSizeUint16;
using safeconv::safeUint8T;
using safeconv::safeSSizeT;

Sigenmax2870Exception::Sigenmax2870Exception(string err, int errCode) noexcept 
  : errStatus{errCode}, errorMessage{err}
{}

int Sigenmax2870Exception::getErrorCode(void)  const  noexcept {
     return errStatus;
}

const string& Sigenmax2870Exception::what(void) const  noexcept {
     return errorMessage;
}

Sigenmax2870::Sigenmax2870(string  device, frequencyType freq, amplificationType db ) anyexcept
   : devicePath{device}, frequency{freq}, dbAmp{db}
{
     if( !exists(devicePath.c_str()))
         throw Sigenmax2870Exception("Serial device doesn't exist");

     reset(frequency, dbAmp);
    
     errno = 0;
     fd =  open(device.c_str(), O_WRONLY | O_NOCTTY | O_NDELAY );
     if( fd == -1){
        string errcode{"Error opening serial device - "};
        errcode.append(strerror(errno));
        throw Sigenmax2870Exception(errcode);
     }

     (void) tcflush(fd, TCIOFLUSH);

     int ret { tcgetattr(fd, &termSettings) };
     if( ret == -1)
        throw Sigenmax2870Exception("Error saving serial config");

     (void) cfsetispeed(&termSettings, BAUDS); 
     (void) cfsetospeed(&termSettings, BAUDS);

     #if defined __clang_major__ &&  __clang_major__ >= 4 
     #pragma clang diagnostic push 
     #pragma clang diagnostic ignored "-Wsign-conversion"
     #endif

     // 8N1 settings - see termios.h / man termios for more information
     termSettings.c_iflag=0;
     termSettings.c_oflag=0;
     termSettings.c_cflag=CS8|CREAD|CLOCAL;                   
     termSettings.c_lflag=0;
     termSettings.c_cc[VMIN]=1;
     termSettings.c_cc[VTIME]=5;

     #ifdef __clang__
     #pragma clang diagnostic pop
     #endif

     ret =  tcsetattr(fd, TCSANOW, &termSettings);
     if( ret == -1)
        throw Sigenmax2870Exception("Error setting serial device attributes");

}

Sigenmax2870::~Sigenmax2870(void) noexcept{
    close(fd);
} 

void  Sigenmax2870::send(void) const anyexcept {
    errno = 0;
    ssize_t ret { write(fd, cmd.data(), cmd.size()) };
    if( ret != safeSSizeT(cmd.size()) ){
        string errcode{"Error setting signal generator - ret: "};
        errcode.append(to_string(ret)).append(" - ");
        errcode.append(strerror(errno));
        throw Sigenmax2870Exception(errcode);
    }
}

void  Sigenmax2870::reset(frequencyType freq, amplificationType db)  anyexcept {
     frequency = freq;
     dbAmp     = db;

     if(frequency < MIN_FREQ || frequency > MAX_FREQ)
          throw Sigenmax2870Exception("Invalid frequency");
  
     if(dbValues.count(dbAmp) == 0)
          throw Sigenmax2870Exception("Invalid amplification value");
  
     frequencySegmentType  ifreq  { safeSizeUint16(frequency / 1000) };
     frequencySegmentType  ffreq  { safeSizeUint16(frequency - ifreq * 1000) };
     cmdType*          ifreqHdlr  { reinterpret_cast<cmdType*>(&ifreq) };
     cmdType*          ffreqHdlr  { reinterpret_cast<cmdType*>(&ffreq) };
     if(endianess.isBig()) {
         cmd[IFREQ_H]    = ifreqHdlr[0];
         cmd[IFREQ_L]    = ifreqHdlr[1];
         cmd[FFREQ_H]    = ffreqHdlr[0];
         cmd[FFREQ_L]    = ffreqHdlr[1];
     } else {
         cmd[IFREQ_H]    = ifreqHdlr[1];
         cmd[IFREQ_L]    = ifreqHdlr[0];
         cmd[FFREQ_H]    = ffreqHdlr[1];
         cmd[FFREQ_L]    = ffreqHdlr[0];
     }

     cmd[AMPLIFIC]   = safeUint8T(dbAmp);
     
}

void  Sigenmax2870::dump(void)  const noexcept{
   for( auto item : cmd)
      cerr <<  "[ 0x" << hex << static_cast<unsigned int>(item) << " ] ";
   cerr << "\n";
}

} // End Namespace sigenmax2870
