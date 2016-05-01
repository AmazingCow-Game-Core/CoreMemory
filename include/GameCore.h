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
#include "CoreMemory_Types.h"
#include "CoreMemory_Utils.h"
//CoreCoord
#include "CoreCoord.h"
//CoreRandom
#include "CoreRandom.h"


NS_COREMEMORY_BEGIN

class GameCore
{
    // Inner Types //
public:
    struct Card
    {
        Card(int v) :
            value(v),
            matched(false)
        {
            //Empty...
        }

        int  value;
        bool matched;
    };

    // Constants / Enums / Typedefs //
public:
    static const int kUnlimitedTries;
    typedef std::vector<std::vector<Card>> Board;


    // CTOR/DTOR //
public:
    ///@brief
    ///     Constructs a new Memory Game Core.
    ///@param width
    ///       The width of board -
    ///       The (width * height) must yield a even number.
    ///@param height
    ///       The height of board -
    //        The (width * height) must yield a even number.
    ///@param maxTries
    ///       How many times player can try match the cards.
    ///       Default is kUnlimitedTries.
    ///@param seed
    ///       The seed that will be used to generate the board.
    ///       Default is CoreRandom::Random::kRandomSeed.
    ///@note The (width * height) must yield a even number,
    ///      if not an exception will be throw.
    ///@throws logic_error if the (width * height) doesn't yield a even number.
    ///@see
    ///     kUnlimitedTries, CoreRandom::Random::kRandomSeed.
    GameCore(int width,
             int height,
             int maxTries = kUnlimitedTries,
             int seed     = CoreRandom::Random::kRandomSeed);


    // Public Methods //
public:
    //Card.
    ///@brief Get the card at coord.
    ///@param coord
    ///       A valid coord in board bounds.
    ///@warning This method will not check the coord validity.
    ///@see getCardAt(), getBoard(), isValidCoord()
    const GameCore::Card& getCardAt(const CoreCoord::Coord &coord) const;

    ///@brief Get the card at index.
    ///@note Check the documentation for coord version.
    ///@see coordToIndex, indexToCoord.
    const GameCore::Card& getCardAt(int index) const;


    //Board.
    const Board& getBoard() const;
    int getWidth() const;
    int getHeight() const;
    int getPairsCount() const;
    int getMatchedPairsCount() const;
    int getRemainingPairsCount() const;

    //Match.
    ///@brief
    ///     Check if the cards matches.
    ///     The cards matches if the following conditions are met: \n
    ///     1 - Both coords are valid.                             \n
    ///     2 - Both coords are different, i.e. are not same card. \n
    ///     3 - None of cards are already matched.                 \n
    ///                                                            \n
    ///     Status might be changed after this method users
    ///     should call getStatus() to check if game is over.
    ///@param coord1
    ///     A valid coord in board bounds.
    ///@param coord2
    ///     A valid coord in board bounds.
    ///@see
    ///     getStatus(), getPairsCount(), getMatchedPairsCount(),
    ///     getRemainingPairsCount(),
    bool checkMatch(const CoreCoord::Coord &coord1,
                    const CoreCoord::Coord &coord2);

    ///@brief Check if the cards matches.
    ///@note Check the documentation for coord version.
    bool checkMatch(int index1, int index2);


    //Status.
    ///@brief Get the current status of game.
    ///@returns The game status.
    Status getStatus() const;


    //Tries.
    ///@brief Get how many tries player did so far.
    ///@returns How many tries player did.
    ///@see getStatus(), getMaxTriesCount(), getRemainingTriesCount()
    int getTriesCount() const;

    ///@brief Get how many tries player can do.
    ///@note
    ///     If kUnlimitedTries is used in CTOR, this method
    ///     will return the kUnlimitedTries value.
    ///@returns How many tries player can do.
    ///@see
    ///     kUnlimitedTries, getStatus(),
    //      getTriesCount(), getRemainingTriesCount()
    int getMaxTriesCount() const;

    ///@brief Get how many tries player can do yet.
    ///@note
    ///     If kUnlimitedTries is used in CTOR, this method
    ///     will return the kUnlimitedTries value.
    ///@returns How many tries player can do yet.
    ///@see
    ///     kUnlimitedTries, getStatus(),
    //      getTriesCount(), getMaxTriesCount()
    int getRemainingTriesCount() const;


    //Seed.
    ///@brief Gets the actual seed used by CoreRandom::Random.
    ///@returns The actual seed the is being used.
    ///@see isUsingRandomSeed().
    int getSeed() const;
    ///@brief Gets if CoreRandom::Random was initialized with a random seed.
    ///@returns True if a random seed is being used, false otherwise.
    ///@see getSeed().
    bool isUsingRandomSeed() const;


    //Helpers.
    CoreCoord::Coord indexToCoord(int index) const;
    int coordToIndex(const CoreCoord::Coord &coord) const;

    bool isValidCoord(const CoreCoord::Coord &coord) const;
    bool isValidIndex(int index) const;

    //ascii
    std::string ascii() const;

    // Private Methods //
private:
    void checkStatus();
    void initBoard(int width, int height);

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
