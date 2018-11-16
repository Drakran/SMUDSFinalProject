#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <stdexcept>
#include <dirent.h>
#include <fstream>
#include <parser.h>
#include <Driver.h>
#include <avltree.h>
#include <chrono>


using namespace std;


int main(int argc, char* argv[]) {


    /* adapted from:
    * https://stackoverflow.com/questions/612097
    * /how-can-i-get-the-list-of-files-in-a-directory-using-c-or-c
    */


   string dir_path;

   if (argc < 2) {
       dir_path = ".";
   }
   else {
       dir_path = argv[1];
   }

   Driver Manager(argv[1],argv[2]);
   Manager.Testing();

       return 0;
}
