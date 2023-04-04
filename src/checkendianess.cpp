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

#include <checkendianess.hpp>

#include <cstdint>

namespace endianesscheck {

using std::string;

Endianess::Endianess(void)  noexcept{
     uint16_t endian { 33 };
     uint8_t  flag   { *( reinterpret_cast<uint8_t*>(&endian)) };
     if( flag == 33 ){
          description = "little";
          big         = false;
          little      = true;
     } else {
          description = "big";
          big         = true;
          little      = false;
     }
}

const string& Endianess::getDescriptionString(void) const  noexcept{
        return description;
}

bool Endianess::isBig(void) const   noexcept{
        return big;
}

bool  Endianess::isLittle(void) const   noexcept{
        return little;
}

}  // End namespace  endianesscheck
