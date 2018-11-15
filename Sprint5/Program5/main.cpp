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

using namespace std;

int main(int argc, char* argv[]) {

//    Driver Manager;
//    Manager.Testing();
    /* adapted from:
    * https://stackoverflow.com/questions/612097
    * /how-can-i-get-the-list-of-files-in-a-directory-using-c-or-c
    */
   Parser parser;

   string dir_path;
   string extention = ".json";
   if (argc < 2) {
       dir_path = ".";
   }
   else {
       dir_path = argv[1];
   }
   vector<string> files = parser.getFiles(dir_path, extention);    //this will output all of files in format of: numberOfFile.json
//comment out this cout otherwise you see the name of each file (77000 files).
   cerr << files.size();
   for (int i = 0; i < files.size(); i++){
        //cout << files[i] << endl;
   }
   parser.parse();
   std::cout << "hi";

       return 0;
}
