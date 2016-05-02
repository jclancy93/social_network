#include "user.h"
#ifndef NETWORK_H
#define NETWORK_H
#include <string>

class Network {
 public:
  Network();
  ~Network();
  int read_friends(const char *filename);
  int write_friends(const char *filename);
  void add_user(std::string username, int yr, int zipcode);
  int add_connection(std::string name1, std::string name2);
  int remove_connection(std::string name1, std::string name2);
  int get_id(std::string username);
  int get_depth(int id);
  std::string get_name(int id);
  void print_users(Network);
  void list_friends(std::string username);
  std::vector<int> shortest_path(int from, int to);
  std::vector<int> shortest_path2(int from, int to);  
  std::vector<std::vector<int> > groups();
  std::vector<int> suggest_friends(int who, int& score);


 private:
    std::vector<User> users;
  
};


#endif
