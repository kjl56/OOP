
#include "json.hpp"

#include <iterator>
#include <iostream>
#include <string>
#include <fstream>

int main(int argc, char* argv[])
{
  //if (argc = 1)//a json file is being passed in
  //{
    std::ifstream jsonFile("cpp.json");
    if (jsonFile.is_open())
    {
      std::string s;
      s.assign(std::istreambuf_iterator<char>(jsonFile), std::istreambuf_iterator<char>());
      //std::string::iterator it;
      //for (it = s.begin(); it < s.end(); ++it)
      //  std::cout << *it;

      json::Value* val = json::parse(s);

      std::cout << size(val) << ' ' << height(val) << '\n';
      std::cout << *val << '\n';//causes segmentation fault, but prints everything
    }
    else
    {
      std::cout << "Error reading cpp.json." << std::endl;
      return 0;
    }
  //}
  //else//no json file is being passed in
  //{
  //  std::cout << "Please pass in a json file when running." << std::endl;
  //  return 0;
  //}
  
  return 0;
}

/*
+Implement a JSON data structure (using inheritance)
+accepts JSON input from reddit.com as standard input
-design and implement a model of Reddit posts
  -Minimally, this data structure should contain an author and title, but it may contain other information.
-Build a list of post objects and print those.
  -print author and title of each post
*/