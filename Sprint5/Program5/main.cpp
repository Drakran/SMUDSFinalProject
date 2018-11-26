#include "dirent.h"
#include "parser.h"
#include "Driver.h"
#include "avltree.h"

using namespace std;

int main(int argc, char* argv[])
{
    /* adapted from:
    * https://stackoverflow.com/questions/612097
    * /how-can-i-get-the-list-of-files-in-a-directory-using-c-or-c
    */
   bool condition = true;
   char choice[20];
   while(condition)
   {
       std::cout << "Choose an option: \n1. Maintainance mode\n2. Query mode\n3. Beast mode\n0. Quit\n";
       cin >> choice;
       if(choice[0] == '1')
       {
       }
       if(choice[0] == '2')
       {
           Driver Manager(argv[1]);
           Manager.Testing();

       }
       if(choice[0] == '0')
       {
           condition = false;
           cout << "Stopping program.....\n";
       }
   }
   return 0;
}
