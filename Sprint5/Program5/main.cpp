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
   Driver Manager(argv[1]);
   while(condition)
   {     
       std::cout << "Choose an option: \n1. Maintainance mode\n2. Query mode\n3. Beast mode\n0. Quit\n";
       cin >> choice;
       if(choice[0] == '1')
       {
           cout<<"Entering maintainance mode....\n";
           Manager.makingStorage();
           cout<<"Exiting maintainance mode...\n";
           std::this_thread::sleep_for(std::chrono::milliseconds(2000));
       }
       if(choice[0] == '2')
       {
           cout<<"Entering query mode....\n";
           Manager.Testing();
           cout<<"Exiting query mode...\n";
           std::this_thread::sleep_for(std::chrono::milliseconds(2000));
       }
       if(choice[0] == '3')
       {
           cout<<"Entering beast mode....\n";
           std::this_thread::sleep_for(std::chrono::milliseconds(2000));
           cout<<"Oops.... Nothing to do, exiting...\n";
           std::this_thread::sleep_for(std::chrono::milliseconds(2000));
       }
       if(choice[0] == '0')
       {
           condition = false;
           cout << "Stopping program.....\n";
           std::this_thread::sleep_for(std::chrono::milliseconds(2000));
       }
   }
   return 0;
}
