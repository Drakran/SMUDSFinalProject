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
   bool condition = true;
   char choice[20];
   while(condition)
   {     
       std::cout << "Choose an option: \n1. Maintenance mode\n2. Interactive mode\n3. Beast mode\n0. Quit\n";
       cin >> choice;
       if(choice[0] == '1')
       {
           char choiceMaintenance[20];
           bool conditionMaintenance = true;
           cout<<"Entering maintenance mode....\n";
           while(conditionMaintenance)
           {
               std::cout << "Choose an option: \n1. Add opinions \n2. Clear index\n0. Back\n";
               cin >> choiceMaintenance;
               string path;
               if(choiceMaintenance[0] == '1')
               {
                   cin.ignore();
                   std::cout<<"Enter path: " ;
                   std::cin>>path;
                   Driver Manager(argv[1]);
                   Manager.makingStorageAVLTree();
                   //Update index from new opinions goes here




               }
               if(choiceMaintenance[0] == '2')
               {
                   //Clear index goes here
                   //Delete .txt file
               }
               if(choiceMaintenance[0] == '0')
               {
                   cout<<"Exiting maintenance mode...\n";
                   std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                   conditionMaintenance = false;
               }
           }
       }
       if(choice[0] == '2')
       {
           cout<<"Entering interactive mode...\n";
           char choiceMaintenance[20];
           bool conditionInteractive = true;
           while(conditionInteractive)
           {
               std::cout << "Choose an option: \n1. AVLTree \n2. HashTable\n0. Back\n";
               cin >> choiceMaintenance;
               if(choiceMaintenance[0] == '1')
               {
                   Driver Manager(argv[1]);
                   Manager.TestingWithAVLTree();
               }
               if(choiceMaintenance[0] == '2')
               {
                   Driver Manager(argv[1]);
                   Manager.TestingWithHashTable();
               }
               if(choiceMaintenance[0] == '0')
               {
                   cout<<"Exiting interactive mode...\n";
                   conditionInteractive = false;
                   std::this_thread::sleep_for(std::chrono::milliseconds(500));
               }
           }
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
           std::this_thread::sleep_for(std::chrono::milliseconds(1000));
       }
   }
   return 0;
}
