//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        GameCore.h                                //
//            █ █        █ █        CoreMemory                                //
//             ████████████                                                   //
//           █              █       Copyright (c) 2016                        //
//          █     █    █     █      AmazingCow - www.AmazingCow.com           //
//          █     █    █     █                                                //
//           █              █       N2OMatt - n2omatt@amazingcow.com          //
//             ████████████         www.amazingcow.com/n2omatt                //
//                                                                            //
//                  This software is licensed as GPLv3                        //
//                 CHECK THE COPYING FILE TO MORE DETAILS                     //
//                                                                            //
//    Permission is granted to anyone to use this software for any purpose,   //
//   including commercial applications, and to alter it and redistribute it   //
//               freely, subject to the following restrictions:               //
//                                                                            //
//     0. You **CANNOT** change the type of the license.                      //
//     1. The origin of this software must not be misrepresented;             //
//        you must not claim that you wrote the original software.            //
//     2. If you use this software in a product, an acknowledgment in the     //
//        product IS HIGHLY APPRECIATED, both in source and binary forms.     //
//        (See opensource.AmazingCow.com/acknowledgment.html for details).    //
//        If you will not acknowledge, just send us a email. We'll be         //
//        *VERY* happy to see our work being used by other people. :)         //
//        The email is: acknowledgment_opensource@AmazingCow.com              //
//     3. Altered source versions must be plainly marked as such,             //
//        and must not be misrepresented as being the original software.      //
//     4. This notice may not be removed or altered from any source           //
//        distribution.                                                       //
//     5. Most important, you must have fun. ;)                               //
//                                                                            //
//      Visit opensource.amazingcow.com for more open-source projects.        //
//                                                                            //
//                                  Enjoy :)                                  //
//----------------------------------------------------------------------------//

#ifndef __CoreMemory_include_GameCore_h__
#define __CoreMemory_include_GameCore_h__

//std
#include <string>
#include <vector>
//CoreMemory
#include "CoreMemory_Utils.h"
#include "CoreMemory_Types.h"
//CoreCoord
#include "CoreCoord.h"
//CoreRandom
#include "CoreRandom.h"


NS_COREMEMORY_BEGIN

class GameCore
{
    // Constants / Enums / Typedefs //
public:
    static const int kUnlimitedTries;
    typedef std::vector<Core::Coord::Vec> Board;


    // Inner Types //
public:
    struct Card
    {
        int  value;
        bool matched;
    };


    // CTOR/DTOR //
public:
    GameCore(int width,
             int height,
             int maxTries = kUnlimitedTries,
             int seed     = CoreRandom::kRandomSeed);


    // Public Methods //
public:
    //Card.
    const Card& getCardAt(const CoreCoord::Coord &coord) const;
    const Card& getCardAt(int index) const;

    //Board.
    const Board& getBoard() const;
    int getWidth() const;
    int getHeight() const;
    int getPairsCount() const;
    int getMatchedPairsCount() const;
    int getRemainingPairsCount() const;

    //Match.
    bool checkMatch(const CoreCoord::Coord &coord1,
                    const CoreCoord::Coord &coord2);
    bool checkMatch(int index1, int index2);

    //Status.
    Status getStatus() const;

    //Tries.
    int getTriesCount() const;
    int getMaxTriesCount() const;
    int getRemainingTriesCount() const;

    //Seed.
    int getSeed() const;
    bool isUsingRandomSeed() const;

    //Helpers.
    CoreCoord::Coord indexToCoord(int index) const;
    int coordToIndex(const CoreCoord::Coord &coord) const;

    bool isValidCoord(const CoreCoord::Coord &coord) const;
    bool isValidIndex(int index) const;


    // Private Methods //
private:
    void checkStatus();
    void initBoard();

    // iVars //
private:
    Board m_board;

    Status m_status;

    int m_matchedPairsCount;

    int m_triesCount;
    int m_maxTriesCount;

    CoreRandom::Random m_random;
};

NS_COREMEMORY_END
#endif // defined(__CoreMemory_include_GameCore_h__) //
