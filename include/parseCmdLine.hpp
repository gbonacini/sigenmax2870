// -----------------------------------------------------------------
// parseCmdLine - a getopt wrapper
// Copyright (C) 2018  Gabriele Bonacini
//
// This program is free software for no profit use, then can redistribute 
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

#include <string>
#include <map>

namespace parcmdline {

    struct ParseResult{
        bool          hasValue,
                      isPresent;
        std::string   value;
    };

    using Flag        =  char;
    using ParsedMap   =  std::map<Flag, ParseResult>;

    class ParseCmdLine{
        public:
            ParseCmdLine(int argc, char **argv, const char* flags, bool uniq=true);
                    bool             isSet(char flag)                           const noexcept;
                    bool             isLegal(char flag)                         const noexcept;
                    bool             hasValue(char flag)                        const noexcept;
                    bool             hasUnflaggedPars(void)                     const noexcept;
            const   std::string&     getUnflaggedPars(void)                     const noexcept;
            const   std::string&     getValue(char flag)                        const noexcept;
            const   std::string      getValueUpper(char flag)                   const noexcept;
            const   std::string      getValueLower(char flag)                   const noexcept;
                    bool             getErrorState(void)                        const noexcept;
            const   std::string&     getErrorMsg(void)                          const noexcept;

        private:
            mutable bool             errState;
                    bool             unflaggedParams,
                                     uniqueParams;
                    int              argcRef;
                    ParsedMap        flagsStatus;
            const   std::string      errString;
                    std::string      unflaggedArgs;
            mutable std::string      errorMesg;

                    bool             setErrorState(bool state)                  const noexcept;
                    bool             parseArgs(char **argv, const char* flags)        noexcept;
                    bool             tokenizeFlags(const char* flags)                 noexcept;
                    bool             setOn(char flag)                                 noexcept;
    };

} // End Namespace

