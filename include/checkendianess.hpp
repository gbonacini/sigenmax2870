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

#pragma once

#include <string>

namespace endianesscheck {

class Endianess{
    private:
        std::string description;
        bool        big;
        bool        little;

    public:
        Endianess(void)                                          noexcept;

        const std::string& getDescriptionString(void)    const   noexcept;
        bool               isBig(void)                   const   noexcept;
        bool               isLittle(void)                const   noexcept;
};

} // End endianesscheck namespace
