// -----------------------------------------------------------------
// sigenmax2870 - a tool to configure  LTDZ MAX2870 signal generator
//                compatible boards by pc using serial port
// Copyright (C) 2023  Gabriele Bonacini
//
// This program is free software for no profit use, then you can redistribute 
// it and/or modify it under the terms of the GNU General Public License 
// as published by the Free Software Foundation; either version 2 of 
// the License, or (at your option) any later version.
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software Foundation,
// Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
// A commercial license is also available for a lucrative use.
// -----------------------------------------------------------------

#pragma once

#include <limits>
#include <cstddef>
#include <cstdint>
#include <string>

#include <anyexcept.hpp>

namespace safeconv{

   template<class T>
      size_t safeSizeT(T size)  anyexcept{
         if(size < 0)       
            throw std::string("Invalid conversion to size_t: negative Avalue.");

         #if defined __clang_major__ &&  __clang_major__ >= 4 
         #pragma clang diagnostic push 
         #pragma clang diagnostic ignored "-Wsign-compare"
         #endif

         #ifdef __GNUC__
         #pragma GCC diagnostic push
         #pragma GCC diagnostic ignored "-Wsign-compare"
         #pragma GCC diagnostic ignored "-Wtype-limits"
         #endif

         if(size > std::numeric_limits<size_t>::max())
            throw std::string("Invalid conversion to size_t: overflow.");

         #ifdef __clang__
         #pragma clang diagnostic pop
         #endif

         #ifdef __GNUC__
         #pragma GCC diagnostic pop
         #endif

         return static_cast<size_t>(size);
   }

   template<class T>
      uint16_t safeSizeUint16(T size)  anyexcept{
         if(size < 0)       
            throw std::string("Invalid conversion to uint16_t: negative Avalue.");

         #if defined __clang_major__ &&  __clang_major__ >= 4 
         #pragma clang diagnostic push 
         #pragma clang diagnostic ignored "-Wsign-compare"
         #endif

         if(size > std::numeric_limits<uint16_t>::max())
            throw std::string("Invalid conversion to uint16_t: overflow.");

         #ifdef __clang__
         #pragma clang diagnostic pop
         #endif

         return static_cast<uint16_t>(size);
   }

   template<class T>
      ssize_t safeSSizeT(T size)  anyexcept{
         if(size > std::numeric_limits<size_t>::max())
            throw std::string("Invalid conversion to ssize_t: overflow.");
         return static_cast<ssize_t>(size);
   }

   template<class T>
      long safeLongT(T size)  anyexcept{
         if(size > std::numeric_limits<long>::max())
            throw std::string("Invalid conversion to long: overflow.");
         return static_cast<long>(size);
   }

   template<class T>
   uint8_t safeUint8T(T size)  anyexcept{
      if(size < 0)
         throw std::string("Invalid conversion to uint8_t: negative value.");
      if(size > std::numeric_limits<uint8_t>::max())
         throw std::string("Invalid conversion to uint8_t: overflow.");
      return static_cast<uint8_t>(size);
   }

   template<class T>
   uint8_t safeUint(T size)  anyexcept {
      #ifdef __GNUC__
      #pragma GCC diagnostic push
      #pragma GCC diagnostic ignored "-Wsign-compare"
      #endif

      #if defined __clang_major__ &&  __clang_major__ >= 4 
      #pragma clang diagnostic push 
      #pragma clang diagnostic ignored "-Wsign-compare"
      #endif
      if(size < 0)
         throw std::string("Invalid conversion to unsigned int: negative value.");
      if(size > std::numeric_limits<unsigned int>::max())
         throw std::string("Invalid conversion to unsigned int: overflow.");

      #ifdef __clang__
      #pragma clang diagnostic pop
      #endif

      #ifdef __GNUC__
      #pragma GCC diagnostic pop
      #endif

      #if defined __clang_major__ &&  __clang_major__ >= 4 
      #pragma clang diagnostic push 
      #pragma clang diagnostic ignored "-Wimplicit-int-conversion"
      #endif

      return static_cast<unsigned int>(size);

      #ifdef __clang__
      #pragma clang diagnostic pop
      #endif
   }

   template<class T>
   uint32_t safeUint32T(T size)  anyexcept{
      #ifdef __GNUC__
      #pragma GCC diagnostic push
      #pragma GCC diagnostic ignored "-Wsign-compare"
      #endif

      #if defined __clang_major__ &&  __clang_major__ >= 4 
      #pragma clang diagnostic push 
      #pragma clang diagnostic ignored "-Wsign-compare"
      #endif
      if(size < 0)
         throw std::string("Invalid conversion to uint32_t: negative value.");
      if(size > std::numeric_limits<uint32_t>::max())
         throw std::string("Invalid conversion to uint32_t: overflow.");

      #ifdef __clang__
      #pragma clang diagnostic pop
      #endif

      #ifdef __GNUC__
      #pragma GCC diagnostic pop
      #endif

      #if defined __clang_major__ &&  __clang_major__ >= 4 
      #pragma clang diagnostic push 
      #pragma clang diagnostic ignored "-Wimplicit-int-conversion"
      #endif

      return static_cast<uint32_t>(size);

      #ifdef __clang__
      #pragma clang diagnostic pop
      #endif
   }

} // End Namespace
