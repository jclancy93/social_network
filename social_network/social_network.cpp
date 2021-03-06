// Name: Jack Clancy
// 

#include "network.h"
#include "user.h"
#include <iostream>
#include <sstream>
using namespace std;

int main(int argc, char *argv[])
{
   Network network;
   network.read_friends(argv[1]);
   cout  << "Welcome to the social network" << endl;
   cout  << "Press 1 to Add User" << endl;
   cout  << "Press 2 to Add Connection" << endl;
   cout  << "Press 3 to Reomve Connection" << endl;
   cout  << "Press 4 to Print Users" << endl;
   cout  << "Press 5 to List Users Friends" << endl;
   cout  << "Press 6 to Write From File" << endl;
   cout  << "Press 7 for Shortest Path" << endl;
   cout  << "Press 8 for Disjoint Sets" << endl;
   cout  << "Press 9 for Suggested Friends" << endl;
   cout  << "===================================" << endl;
   int option;
   string command;
   while (1) {
         getline(cin, command);
      stringstream command_line(command);
      command_line >> option;
      if (option == 1)
      {
         string fname, lname, fullname;
         int zip, year;
         command_line >> fname >> lname >> zip >> year;
         fullname = fname + ' ' + lname;
         network.add_user(fullname, zip, year);
         cout << "" << endl;
         command_line.clear();
      }
      else if (option == 4)
      {
         cout << "Time to print all users" << endl;
         network.print_users(network);
         cout << "" << endl;
      }
      else if (option == 2)
      {
         string fname1, lname1, fname2,  lname2, name1, name2;
         command_line >> fname1 >> lname1 >> fname2 >> lname2;
         name1 =  fname1 + ' ' + lname1;
         name2 =  fname2 + ' ' + lname2;
         cout << name1 << ';' <<endl;
         cout << name2 << ';' <<endl;
         cout << name1 << endl;
         cout << name2 << endl;
         network.add_connection(name1, name2);
         cout << "" << endl;
      }
      else if (option == 3)
      {
         string fname1, lname1, fname2,  lname2, name1, name2;
         command_line >> fname1 >> lname1 >> fname2 >> lname2;
         name1 =  fname1 + ' ' + lname1;
         name2 =  fname2 + ' ' + lname2;
         network.remove_connection(name1, name2);
         cout << "" << endl;
      }
      else if (option == 5)
      {
         string fname, lname, fullname;
         command_line >> fname >> lname;
         fullname = fname + " " + lname;
         network.list_friends(fullname);
         cout << "" << endl;
      }
      else if (option == 6)
      {
         string filename;
         command_line >> filename;
         network.write_friends(filename.c_str());
         cout << "" << endl;
      }
      else if (option == 7) {
         int id1, id2;
          string fname1, lname1, fname2,  lname2, name1, name2;
         command_line >> fname1 >> lname1 >> fname2 >> lname2;
         name1 =  fname1 + ' ' + lname1;
         name2 =  fname2 + ' ' + lname2;
         id1 = network.get_id(name1); 
         id2 = network.get_id(name2); 
         std::vector<int> path;
         if (id1 != -1 && id2 != -1)
         {
            //now that both exist,call function 
            path =  network.shortest_path(id1, id2);

         }
         else {
            cerr << "Please provide two valid usernames" << endl;
         }

         if (path.size() > 0)
         {
          cout << "Distance: " << network.get_depth(id2) << endl;

          for (int i = 0; i < path.size() -1 ; i++)
            {
               cout << network.get_name(path[i]) << "->";
            }
            cout << network.get_name(path[path.size() -1]) << endl;
         }

      }
      else if (option == 8) {
         vector<vector<int> > groups = network.groups();
         for (int i = 0; i < groups.size(); i++)
         {
            cout << "Set " << i << " => ";
            for (int j = 0; j < groups[i].size(); j++)
            {
               cout << network.get_name(groups[i][j]) << ", ";
            }
            cout << endl;
         }
      }
    else if (option == 9) {
       int id;
         string fname1, lname1, name;
        command_line >> fname1 >> lname1;
        name =  fname1 + ' ' + lname1;
         id = network.get_id(name); 
       int max_score;
       cout << "The suggested friend(s) is/are: " << endl;
         vector<int> suggested_friends = network.suggest_friends(id, max_score);
         for (int i = 0; i < suggested_friends.size(); i++)
         {
            cout << network.get_name(suggested_friends[i]) << "    Score: "
             << max_score << endl;
         }
      }
    else return 0;
   }
}
