//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        GameCore.cpp                              //
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

//Header
#include "../include/GameCore.h"
//std
#include <algorithm>
#include <sstream>
#include <iostream>

//Usings
USING_NS_COREMEMORY;

// Constants / Enums / Typedefs //
const int GameCore::kUnlimitedTries = -1;

// CTOR/DTOR //
GameCore::GameCore(int width, int height, int maxTries, int seed) :
    //m_board - Init in initBoard().
    m_status(Status::Continue),
    m_matchedPairsCount(0),
    m_triesCount(0),
    m_maxTriesCount(maxTries),
    m_random(seed)
{
    initBoard(width, height);
}

// Public Methods //
//Card.
const GameCore::Card& GameCore::getCardAt(const CoreCoord::Coord &coord) const
{
    return m_board[coord.y][coord.x];
}
const GameCore::Card& GameCore::getCardAt(int index) const
{
    return getCardAt(indexToCoord(index));
}

//Board.
const GameCore::Board& GameCore::getBoard() const
{
    return m_board;
}

int GameCore::getWidth() const
{
    return m_board.size();
}

int GameCore::getHeight() const
{
    return m_board[0].size();
}

int GameCore::getPairsCount() const
{
    return (getHeight() * getWidth()) / 2;
}

int GameCore::getMatchedPairsCount() const
{
    return m_matchedPairsCount;
}

int GameCore::getRemainingPairsCount() const
{
    return getPairsCount() - getMatchedPairsCount();
}

//Match.
bool GameCore::checkMatch(const CoreCoord::Coord &coord1,
                          const CoreCoord::Coord &coord2)
{
    //Game is already over.
    if(m_status != Status::Continue)
        return false;

    //Both must be valid coords.
    if(!isValidCoord(coord1) || !isValidCoord(coord2))
        return false;

    //Coords must be different.
    if(coord1 == coord2)
        return false;

    //Get the cards.
    auto &card1 = getCardAt(coord1);
    auto &card2 = getCardAt(coord2);

    //Already matched...
    if(card1.matched || card2.matched)
        return false;

    auto cardsAreEqual = (card1.value == card2.value);

    //Tries count is increment regardless
    //if player hit the guess or not.
    ++m_triesCount;

    if(cardsAreEqual)
    {
        ++m_matchedPairsCount;
        const_cast<Card &>(card1).matched = true;
        const_cast<Card &>(card2).matched = true;
    }

    checkStatus();

    return cardsAreEqual;
}
bool GameCore::checkMatch(int index1, int index2)
{
    return checkMatch(indexToCoord(index1), indexToCoord(index2));
}

//Status.
Status GameCore::getStatus() const
{
    return m_status;
}

//Tries.
int GameCore::getTriesCount() const
{
    return m_triesCount;
}
int GameCore::getMaxTriesCount() const
{
    return m_maxTriesCount;
}
int GameCore::getRemainingTriesCount() const
{
    if(m_maxTriesCount == kUnlimitedTries)
        return -1;

    return m_maxTriesCount - m_triesCount;
}

//Seed.
int GameCore::getSeed() const
{
    return m_random.getSeed();
}
bool GameCore::isUsingRandomSeed() const
{
    return m_random.isUsingRandomSeed();
}

//Helpers.
CoreCoord::Coord GameCore::indexToCoord(int index) const
{
    return CoreCoord::Coord(index / getWidth(),
                            index % getWidth());
}
int GameCore::coordToIndex(const CoreCoord::Coord &coord) const
{
    return (coord.y * getHeight()) + coord.x;
}

bool GameCore::isValidCoord(const CoreCoord::Coord &coord) const
{
    return coord.y >= 0 && coord.y < getHeight()
        && coord.x >= 0 && coord.x < getWidth();
}
bool GameCore::isValidIndex(int index) const
{
    return isValidCoord(indexToCoord(index));
}

//ascii
std::string GameCore::ascii() const
{
    std::stringstream ss;
    for(const auto &line : m_board)
    {
        for(const auto &card : line)
        {


            if(!card.matched)
            {
                ss << "{";
                ss << card.value;
                ss << "}";
            }
            else
            {
                ss << " . ";
            }

        }
        ss << "\n";
    }

    return ss.str();
}


// Private Methods //
void GameCore::checkStatus()
{
    //If player matched all cards let he wins, ignore the tries count.
    if(getMatchedPairsCount() == getPairsCount())
        m_status = Status::Victory;

    //Tries count are at maximum - Player loses.
    else if(getRemainingTriesCount() == 0)
        m_status = Status::Defeat;

    //Just continue...
}

void GameCore::initBoard(int width, int height)
{
    auto pairsCount = (width * height) / 2;

    std::vector<Card> pairsVec;
    pairsVec.reserve(pairsCount);

    for(int i = 0; i < pairsCount; ++i)
    {
        pairsVec.emplace_back(i);
        pairsVec.emplace_back(i);
    }


    std::shuffle(std::begin(pairsVec),
                 std::end(pairsVec),
                 m_random.getNumberGenerator());


    m_board.reserve(height);
    for(int i = 0; i < height; ++i)
    {
        m_board.push_back(Board::value_type(
            std::begin(pairsVec) + (i * width),        //Offset in pairsVec
            std::begin(pairsVec) + (i * width + width) //Offset in pairsVec + how many to copy
        ));
    }
}
