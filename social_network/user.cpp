#include "user.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

User::User(int id, string name, int birth_yr, int zip){
   user_id = id;
   user_name = name;
   birth_year = birth_yr;
   zip_code = zip;
   depth = -1;
   predecessor = 0;
}

void User::add_friend(int id){
   vector<int>* friends_vector = get_friend_vector();
   friends_vector->push_back(id);
   //cout << "User's friends are:"<< friend_vector[0] << endl;
}

void User::delete_friend(int id){
   for (int i = 0; i < friend_vector.size(); i++)
   {
      if (friend_vector[i] == id)
      {
         friend_vector.erase(friend_vector.begin() + i);
      }
   }
}

string User::get_name() {
   return user_name;
}

int User::get_id() {
   return user_id;
}

int User::get_birth() {
   return birth_year;
}

int User::get_zip() {
   return zip_code;
}

  vector<int>* User::get_friend_vector() {
     return &friend_vector;
 }
