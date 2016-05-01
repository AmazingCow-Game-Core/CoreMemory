//----------------------------------------------------------------------------//
//               █      █                                                     //
//               ████████                                                     //
//             ██        ██                                                   //
//            ███  █  █  ███        main.cpp                                  //
//            █ █        █ █        CoreMemory                                //
//             ████████████                                                   //
//           █              █       Copyright (c)  2016                       //
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


//This guard is to ease the usage of the MemoryCore,
//so it's users won't need to worry about removing any files
//since is very unlikely that this flag is defined elsewhere.
#ifdef __AMAZINGCORE_COREMEMORY_TEST_ENABLED__

#include <cstdlib>
#include <iostream>
#include <vector>
#include "../include/CoreMemory.h"

USING_NS_COREMEMORY;
using namespace std;


void usage()
{
    cout << "Amazing Cow - CoreMemory Test Game" << endl;
    cout << "Usage:"  << endl
         << "  testgame <width> <height> <seed> <use-index>" << endl
         << "Example:" << endl
         << "  testgame 5 4 -1 1 #width 5 - height 4 - random seed - use index" << endl
         << "  testgame 5 4  3 0 #width 5 - height 4 - seed 3 - use coords"
         << endl;

    exit(1);
}

int main(int argc, const char *argv[])
{
    if(argc != 5)
        usage();

    int width  = atoi(argv[1]);
    int height = atoi(argv[2]);
    int seed   = atoi(argv[3]);
    int index  = atoi(argv[4]);

    GameCore core(width, height, GameCore::kUnlimitedTries, seed);

    while(core.getStatus() == Status::Continue)
    {
        cout << core.ascii() << endl;
        cout << "Width               : "  << core.getWidth()               << endl;
        cout << "Height              : "  << core.getHeight()              << endl;
        cout << "PairsCount          : "  << core.getPairsCount()          << endl;
        cout << "MatchedPairsCount   : "  << core.getMatchedPairsCount()   << endl;
        cout << "RemainingPairsCount : "  << core.getRemainingPairsCount() << endl;
        cout << "-----------------------" << endl;
        cout << "Status : "               << core.getStatus() << endl;
        cout << "-----------------------" << endl;
        cout << "TriesCount          : "  << core.getTriesCount()          << endl;
        cout << "MaxTriesCount       : "  << core.getMaxTriesCount()       << endl;
        cout << "RemainingTriesCount : "  << core.getRemainingTriesCount() << endl;
        cout << "-----------------------" << endl;
        cout << "Seed              : "    << core.getSeed() << endl;
        cout << "isUsingRandomSeed : "    << core.isUsingRandomSeed() << endl;
        cout << "-----------------------" << endl;


        CoreCoord::Coord card1, card2;

        if(index)
        {
            cout << "cards (index)?: " << endl;

            int c1, c2;
            cin >> c1 >> c2;

            card1 = core.indexToCoord(c1);
            card2 = core.indexToCoord(c2);

            cout << "COORDS: " << endl;
            cout << card1 << endl;
            cout << card2 << endl;
        }
        else
        {
            cout << "cards (coords)?: " << endl;

            int c1y, c1x;
            int c2y, c2x;

            cin >> c1y >> c1x >> c2y >> c2x;

            card1 = CoreCoord::Coord(c1y, c1x);
            card2 = CoreCoord::Coord(c2y, c2x);
        }

        cout << "Matched: " << core.checkMatch(card1, card2) << endl;
    }

}

#endif // __AMAZINGCORE_MEMORYCORE_TEST_ENABLED__ //
