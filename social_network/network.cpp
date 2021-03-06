#include "network.h"
#include "user.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstring>
#include <deque>
#include <algorithm>
using namespace std;

Network::Network() {

}

Network::~Network() {

}

int Network::read_friends(const char *filename) {
   string line, line1 , line2, line3, line4;
   ifstream myfile(filename);
   if (myfile.is_open())
   {
      stringstream ss(filename);
      int num_users;
      myfile >> num_users;
      int iterations = 0;
       vector<string> friends_vector;
       while(!myfile.eof() && iterations < num_users) {
        int id, zip, year;
        string name, friends;
        myfile >> id;
        getline(myfile, line);
        stringstream s1(line);
        name = s1.str();
        getline(myfile, line);
        stringstream s0(line);
        name = s0.str();
        name.erase(name.begin());
        getline(myfile, line);
        stringstream s2(line);
        s2 >> year;
        getline(myfile, line);
        stringstream s3(line);
        s3 >> zip;
        getline(myfile, line);
        stringstream s4(line);
        friends = s4.str();
        friends_vector.push_back(friends);
        add_user(name, year, zip);
        iterations++;
      }

      for (int i = 0; i < users.size(); i++)
      {
         string friends_string = friends_vector[i];
         stringstream stream(friends_string);
         vector<int> n_vector;
         int n;
         while(stream >> n){
             n_vector.push_back(n);
             stream.clear();
         }
         for (int j = 0; j < n_vector.size(); j++)
         {
            users[i].add_friend(n_vector[j]);
         }      
      }
      return 0;
   }
   else {
      cerr << "Error opening file" << endl;
      return -1;
   }
   
}

int Network::write_friends(const char *filename) {
   ofstream myfile;
   myfile.open(filename);
   if (myfile.is_open())
   {
      myfile << users.size() << '\n';
      for (int i = 0; i < users.size(); i++)
      {
      myfile << users[i].get_id() << '\n';
      myfile << '\t' << users[i].get_name() << '\n';
      myfile << '\t' << users[i].get_birth() << '\n';
      myfile << '\t' << users[i].get_zip() << '\n';
      myfile << '\t';
     vector<int>* friend_vector = users[i].get_friend_vector();
      for (int j = 0; j < friend_vector->size(); j++)
      {
         myfile << (*friend_vector)[j] << ' ';
      }
      myfile << '\n';
      }   
      return 0;
   }
   else {
      cerr << "Error with file" << endl;
      return -1;
   }
}

void Network::add_user(std::string username, int yr, int zipcode){
   int num_users = users.size();
   User user(num_users, username, yr, zipcode);
   users.push_back(user);
}

int Network::add_connection(std::string name1, std::string name2){
   bool foundUser1, foundUser2 = 0;
   int id1, id2; 
   for (int i = 0; i < users.size(); i++)
   {
      if (users[i].get_name() == name1)
      {
         foundUser1 = 1;
         id1 = i;
      }
      if (users[i].get_name() == name2) {
         foundUser2 = 1;
         id2 = i;
      }
   }

   if (foundUser1 == 1 && foundUser2 == 1)
   {   
         vector<int>* friend_vector1 = users[id1].get_friend_vector();

        bool alreadyHas = 0;
        for (int j = 0; j < friend_vector1->size(); j++)
        {

           if ((*friend_vector1)[j] == id2)
           {
              alreadyHas = 1;
           }
        }
        if (alreadyHas == 0) {
           users[id1].add_friend(id2);
           users[id2].add_friend(id1);
            return 0;
        }
        else {
           cerr << "Already friends" << endl;
           return -1;
        }

   }
   else {
      cerr << "Error. Please enter 2 valid usernames" <<endl;
      return -1;
   }
}

int Network::remove_connection(std::string name1, std::string name2){
   bool foundUser1, foundUser2 = 0;
   int id1, id2; 
   for (int i = 0; i < users.size(); ++i)
   {
      if (users[i].get_name() == name1)
      {
         foundUser1 = 1;
         id1 = i;
      }
      else if (users[i].get_name() == name2) {
         foundUser2 = 1;
         id2 = i;
      }
   }

   if (foundUser1 == 1 && foundUser2 == 1)
   {
      users[id1].delete_friend(id2);
      users[id2].delete_friend(id1);
      return 0;
   }
   else {
      cerr << "Error. Please enter 2 valid usernames" <<endl;
      return -1;
   }
}

int Network::get_id(std::string username) {
   bool foundUser1 = 0;
   int id1; 
   for (int i = 0; i < users.size(); ++i)
   {
      if (users[i].get_name() == username)
      {
         foundUser1 = 1;
         id1 = i;
      }
   }

   if (foundUser1 == 1)
   {
      return users[id1].get_id();
   }
   else {
      cerr << "Error. Please enter a valid username" <<endl;
      return -1;
   }
}

string Network::get_name(int id) {
   bool foundUser1 = 0;
   string name; 
   for (int i = 0; i < users.size(); ++i)
   {
      if (users[i].get_id() == id)
      {
         foundUser1 = 1;
         name = users[i].get_name();
      }
   }

   if (foundUser1 == 1)
   {
      return name;
   }
   else {
      cerr << "Error. Please enter a valid username" <<endl;
      return name;
   }
}

int Network::get_depth(int id) {
   bool foundUser = 0;
   int depth; 
   for (int i = 0; i < users.size(); ++i)
   {
      if (users[i].get_id() == id)
      {
         foundUser = 1;
         depth = users[i].depth;
      }
   }

   if (foundUser == 1)
   {
      return depth;
   }
   else {
      cerr << "Error. Please enter a valid username" <<endl;
      return -1;
   }   
}

void Network::print_users(Network) {
   cout << "ID" << setw(15) << setfill(' ') << "NAME" << setw(15) << 
   setfill(' ') << "YEAR" << setw(15) << setfill(' ') << "ZIP"<< endl;
   for (int i = 0; i < users.size(); i++)
   {
      cout << users[i].get_id() << setw(15) << setfill(' ') <<
       users[i].get_name() << setw(15) <<setfill(' ') <<
        users[i].get_birth() << setw(15) << setfill(' ') <<
         users[i].get_zip() << endl;
   }
}

void Network::list_friends(string username) {
   int id; 
   bool isFound = 0;
   for (int i = 0; i < users.size(); i++)
   {
      if (users[i].get_name() == username)
      {
         id = i;
         isFound = 1;
      }
   }
   if (isFound == 1)
   {
   cout << "ID" << setw(15) << setfill(' ') << "NAME" << setw(15) <<
   setfill(' ') <<  "YEAR" << setw(15) << setfill(' ') << "ZIP"  << endl;
   vector<int>* friend_vector = (users[id].get_friend_vector());
   for (int i = 0; i < friend_vector->size(); i++)
   {
      int friend_id = (*friend_vector)[i];
      cout << users[friend_id].get_id() << setw(15) << setfill(' ') << 
      users[friend_id].get_name()<< setw(15) <<setfill(' ') << 
      users[friend_id].get_birth() << setw(15) << setfill(' ') << 
      users[friend_id].get_zip() << endl;
   }
   }
   else {
      cerr << "Please provide a valid username" << endl;
   }
}


std::vector<int> Network::shortest_path(int from, int to) {
   //Find the shortest path between two users 
   //Breadth First Search
   //we check if from and to exist in social_network.cpp
      //now that both exist, get friend list
   for (int i = 0; i < users.size(); i++)
   {
      users[i].predecessor = -1;
      users[i].depth = 0;
   }

   bool pathFound = 0;

   deque<int> queue;
   queue.push_back(from);

   //keep executing til queue empty
   while(!queue.empty()) {
      //pop front user from queue
      int user_for_check = queue.front();
      queue.pop_front();
         //check if user is 'to'
         if (users[user_for_check].get_id() == to)
         {
            pathFound = 1;
            break;
         }

         //if not, get friend vector and add to list
         vector<int>* user_for_check_friends = 
         users[user_for_check].get_friend_vector();

         for (int i = 0; i < user_for_check_friends->size(); i++)
         {
            if (users[(*user_for_check_friends)[i]].predecessor == -1)
            {
               users[(*user_for_check_friends)[i]].predecessor = user_for_check;
               users[(*user_for_check_friends)[i]].depth = 
               users[user_for_check].depth + 1;
               queue.push_back((*user_for_check_friends)[i]);
            }
         }
      }

      vector<int> path;
      if (pathFound)
      {
         // backtrack to original user 
         int currNode = to; 
      while(1) {
         path.push_back(currNode);
         if (users[currNode].predecessor == from) 
         {
            currNode = users[currNode].predecessor;
            path.push_back(currNode);
            break;
         }
      currNode = users[currNode].predecessor;
      }
      }

      reverse(path.begin(),path.end());
      return path;
}

vector<vector<int> > Network::groups() {
   //iterate through all users to find groups 
   vector<vector<int> > groups;

   deque<int> r;
   // first performs BFS on one users, all of that users firneds are one set 
   // then, if depth is -1, then person hasnt been found then perform BFS 

   for (int i = 0; i < users.size(); i++)
   {
      r.push_back(users[i].get_id());
   }

   while(!r.empty()) {
      int c = r.front();
      r.pop_front();
      vector<int> v;
      v.push_back(c);

      for (int i = 0; i < r.size(); i++)
      {
         vector<int> path = shortest_path(c, r[i]);
         if (path.size() > 1)
         {
            for (int j = 0; j < path.size(); ++j)
            {
               v.push_back(path[j]);
            }
         }
      }

      //for v - v.size() then remove v at i 
      for (int i = 0; i < r.size(); i++)
      {      
         if (users[r[i]].predecessor != -1 && users[r[i]].depth > 0)
         {
            for (int j = 0; j < v.size(); j++)
            {
               if (r[i] == v[j])
               {
                  r.erase(r.begin() + i);
               }
            }
         }
      }

      vector<int> new_v;

      for (int i = 0; i < v.size(); i++)
      {
         bool any = false;
         for (int j = 0; j < new_v.size(); j++)
         {
            if (v[i] == new_v[j])
            {
               any = true;
            }
         }
         if(!any)
            new_v.push_back(v[i]);
      }


      groups.push_back(new_v);
   }
   return groups;
}

vector<int> Network::suggest_friends(int who, int& score) {
   //get all of whos friends who have a depth of 1, these 
   //people are already friends so no need to pay attention to them 
   vector<int>* whos_friends = users[who].get_friend_vector();
   vector<int>* whos_friends_friends;
   vector<int> ids;



   // now get all of whos friends friends, who are candidates for suggestions
   for (int i = 0; i < whos_friends->size(); i++)
    {
       whos_friends_friends = users[(*whos_friends)[i]].get_friend_vector();
    

    for (int j  = 0; j < whos_friends_friends->size(); j++)
    {
       bool is_candidate = 1; 
       //cout << users[(*whos_friends_friends)[j]].get_name() << endl;
       if ((*whos_friends_friends)[j] == who)
       {
          is_candidate = 0; 
       }
       for (int k = 0; k < whos_friends->size(); k++)
       {
          if ((*whos_friends_friends)[j] == (*whos_friends)[k])
          {
             is_candidate = 0; 
          }
       }
       if (is_candidate)
       {
         ids.push_back((*whos_friends_friends)[j]);
       }

    }
   }
   std::vector<int> scores;
   std::vector<int> candidate_list;
   std::vector<int> suggested_friends;
   for (int i = 0; i < ids.size(); i++)
   {
      bool already_seen = 0; 
      

      for (int j = 0; j < candidate_list.size(); j++)
      {
         if (ids[i] == candidate_list[j]) {
            already_seen = 1;
            scores[j]++;
         } 
      }
      if (!already_seen)
      {
         candidate_list.push_back(ids[i]);
         scores.push_back(1);
      }
   }

   int max_score = 0; 

   for (int i = 0; i < scores.size(); i++)
   {
      if (scores[i] > max_score)
      {
         max_score = scores[i];   
      }
   }

   for (int i = 0; i < scores.size(); i++)
   {
      if (max_score == scores[i])
      {
         suggested_friends.push_back(candidate_list[i]);
      }
   }

   score = max_score; 

   return suggested_friends;
}

