// -----------------------------------------------------------------
// parseCmdLine - a getopt wrapper
// Copyright (C) 2018  Gabriele Bonacini
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

#include <parseCmdLine.hpp>

#include <unistd.h>

#include <iostream>
#include <locale>
#include <cctype>

using std::string;
using std::pair;
using std::toupper;
using std::tolower;

namespace parcmdline{

    ParseCmdLine::ParseCmdLine(int argc, char **argv, const char* flags, bool uniq) 
         : errState{false}, unflaggedParams{false}, uniqueParams{uniq},
           argcRef{argc},   errString{""}, unflaggedArgs{"noparams"},
           errorMesg{""}
    {
        tokenizeFlags(flags);
        parseArgs(argv, flags);
    }

    bool ParseCmdLine::isSet(char flag) const noexcept{
        if(flagsStatus.find(flag) != flagsStatus.end())
            if(flagsStatus.at(flag).isPresent)
                return true;
        
        return false;
    }

    bool ParseCmdLine::isLegal(char flag)  const noexcept{
        if(flagsStatus.find(flag) != flagsStatus.end())
                return true;

        return false;
    }

    bool ParseCmdLine::hasValue(char flag) const noexcept{
        if(flagsStatus.find(flag) != flagsStatus.end())
            if(flagsStatus.at(flag).hasValue)
                return true;

        return false;
    }

    bool  ParseCmdLine::hasUnflaggedPars(void) const noexcept{
        return unflaggedParams;
    }

    const string& ParseCmdLine::getUnflaggedPars(void) const noexcept{
        return unflaggedArgs;
    }

    const string& ParseCmdLine::getValue(char flag) const noexcept{
        if(flagsStatus.find(flag) != flagsStatus.end())
            if(flagsStatus.at(flag).hasValue)
                return flagsStatus.at(flag).value;

        errorMesg.append("\nError getting the value of: ").push_back(flag);
        return errString;
    }

    const string  ParseCmdLine::getValueUpper(char flag)    const noexcept{
        string  buff;
        try{
            if(flagsStatus.find(flag) != flagsStatus.end())
                if(flagsStatus.at(flag).hasValue){
                   for(auto ch : flagsStatus.at(flag).value)
                      buff.push_back(static_cast<char>(toupper(ch)));

                   return buff;
            }
        }catch(...){
            errorMesg.append("\nError getting the upper case value of: ").push_back(flag);
        }

        return errString;
    }

    const string  ParseCmdLine::getValueLower(char flag)    const noexcept{
        string  buff;
        try{
            if(flagsStatus.find(flag) != flagsStatus.end())
                if(flagsStatus.at(flag).hasValue){
                   for(auto ch : flagsStatus.at(flag).value)
                      buff.push_back( static_cast<char>(tolower(ch)));

                   return buff;
            }
        }catch(...){
            errorMesg.append("Error getting the lower case value of: ").push_back(flag);
        }

        return errString;
    }

    bool ParseCmdLine::setOn(char flag) noexcept{
        if(flagsStatus.find(flag) == flagsStatus.end())
            return false;

        if(flagsStatus[flag].isPresent)
            return false;

        flagsStatus[flag].isPresent         = true;
        return true;
    }

    bool ParseCmdLine::getErrorState() const noexcept{
        return errState;
    }

    const string&  ParseCmdLine::getErrorMsg(void) const noexcept{
        return errorMesg;
    }

    bool ParseCmdLine::setErrorState(bool state) const noexcept{
        errState      =  state;
        return !state;
    }

    bool ParseCmdLine::parseArgs(char **argv, const char* flags) noexcept{
        for(int ch = getopt (argcRef, argv, flags); static_cast<unsigned char>(ch) != 255; ch = getopt (argcRef, argv, flags)){
            char c = static_cast<char>(ch);
            if(c != '?' && c > 0){
                if(flagsStatus.find(c) == flagsStatus.end()){
                    errorMesg.append("\nError unexpected parameter: ").push_back(c);
                    return setErrorState(true);
                }

                if(!setOn(c)){
                    errorMesg.append("\nError processing parameter: ").push_back(c);
                    return setErrorState(true);
                }

                if(flagsStatus[c].hasValue){
                    if(optarg == nullptr || optarg[0] == '-'){
                        errorMesg.append("\nError assingning a value to parameter: ").push_back(c);
                        return setErrorState(true);
                    }

                    if(uniqueParams &&  !flagsStatus[c].isPresent){
                        errorMesg.append("\nError duplicated parameter: ").push_back(c);
                        return setErrorState(true);
                    }
                    
                    flagsStatus[c].value.insert(0, optarg);
                }
            }else if(c == '?'){
                    errorMesg.append("\nError parsing command line parameters.");
                    return setErrorState(true);
            }else{
                break;
            }
        }

        if(argcRef > optind){
            unflaggedParams = true;
            unflaggedArgs   = argv[optind];
        }

        return true;
    }

    bool ParseCmdLine::tokenizeFlags(const char* flags) noexcept{
        int    pos       { 0 }; 
        char   prevKey   { 0 }; 

        while(flags[pos] != 0){
            if((flags[pos] >= 65 && flags[pos] <= 90) || ( flags[pos] >= 97 && flags[pos] <= 122)){
                prevKey                           =  flags[pos];
                flagsStatus.insert(pair<char, ParseResult>(flags[pos], {false, false, ""}));
            }else if(flags[pos] == 58){
                if(prevKey == 0)
                    return setErrorState(true);

                flagsStatus[prevKey].hasValue     =  true;
            }else{
                return setErrorState(true);
            }
            pos++;
        }

        return true;
    }

} // End Namespace 
