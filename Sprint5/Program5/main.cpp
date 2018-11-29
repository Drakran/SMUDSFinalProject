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

   Driver Manager(argv[1]);
   Manager.userInterface();

   return 0;
}
