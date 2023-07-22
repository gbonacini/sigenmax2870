// -----------------------------------------------------------------
// sigenmax2870 - a tool to configure  LTDZ MAX2870 signal generator
//                compatible boards by pc using serial port
// Copyright (C) 2023  Gabriele Bonacini
//
// This program is distributed under dual license:
// - Creative Commons Attribution-NonCommercial 4.0 International (CC BY-NC 4.0) License 
// for non commercial use, the license has the following terms:
// * Attribution — You must give appropriate credit, provide a link to the license, 
// and indicate if changes were made. You may do so in any reasonable manner, 
// but not in any way that suggests the licensor endorses you or your use.
// * NonCommercial — You must not use the material for commercial purposes.
// A copy of the license it's available to the following address:
// http://creativecommons.org/licenses/by-nc/4.0/
// - For commercial use a specific license is available contacting the author.
// -----------------------------------------------------------------

#pragma once

#include <termios.h>

#include <array>
#include <set>
#include <string>
#include <cstdint>

#include <anyexcept.hpp>
#include <checkendianess.hpp>

namespace sigenmax2870 {
    const size_t CMD_LEN = 9;

    using Termios = struct termios;
    using frequencyType = uint32_t;
    using frequencySegmentType = uint16_t;
    using amplificationType = uint32_t;
    using cmdType = uint8_t;
    using Cmd = std::array<cmdType, CMD_LEN>;
    using DBValues = std::set<amplificationType>;
    using endianesscheck::Endianess;

    class Sigenmax2870Exception{
      public:
         explicit Sigenmax2870Exception(std::string err, int errCode=-1) noexcept;

         int                 getErrorCode(void)             const        noexcept;
         const std::string&  what(void)                     const        noexcept;
      private:
         int           errStatus;
         std::string   errorMessage;
    };

    
    class Sigenmax2870{
      private:
         const   speed_t         BAUDS     { B9600 };
         const   frequencyType   MIN_FREQ  { 23500 },
                                 MAX_FREQ  { 6000000 };
         const   size_t          IFREQ_H   { 2 },
                                 IFREQ_L   { 3 },
                                 FFREQ_H   { 4 },
                                 FFREQ_L   { 5 },
                                 AMPLIFIC  { 6 };

         Cmd                     cmd       { 0x55, 0x55, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0D, 0x0A };
         const DBValues          dbValues  { 1, 2, 3, 4 };        
         int                     fd        { -1 };
         const std::string       devicePath;
         frequencyType           frequency;
         amplificationType       dbAmp;
         Termios                 termSettings;  
         Endianess               endianess;
    
      public:
               Sigenmax2870(std::string       device,
                            frequencyType     freq,
                            amplificationType db=1 )                       anyexcept;
               ~Sigenmax2870(void)                                         noexcept;
    
         void  send(void)                                     const        anyexcept;
         void  reset(frequencyType     freq,
                     amplificationType db=1 )                              anyexcept;

         void  dump(void)                                     const        noexcept;
    };

} // End Namespace sigenmax2870
