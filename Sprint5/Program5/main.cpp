#include "dirent.h"
#include "parser.h"
#include "Driver.h"
#include "avltree.h"
#include <map>


using namespace std;

int main(int argc, char* argv[])
{
    /* adapted from:
    * https://stackoverflow.com/questions/612097
    * /how-can-i-get-the-list-of-files-in-a-directory-using-c-or-c
    */

    //    _    _                 _____       _             __
    //   | |  | |               |_   _|     | |           / _|
    //   | |  | |___  ___ _ __    | |  _ __ | |_ ___ _ __| |_ __ _  ___ ___
    //   | |  | / __|/ _ \ '__|   | | | '_ \| __/ _ \ '__|  _/ _` |/ __/ _ \
    //   | |__| \__ \  __/ |     _| |_| | | | ||  __/ |  | || (_| | (_|  __/
    //    \____/|___/\___|_|    |_____|_| |_|\__\___|_|  |_| \__,_|\___\___|
    //

   Driver Manager(argv[1]);
   Manager.userInterface();

   return 0;
}
