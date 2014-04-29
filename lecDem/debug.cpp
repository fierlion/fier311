#include <iostream>
#include <string>

int main(int argc, char **argv){
  std::string input;
  int i = 0;

  std::cin >> input;

  for (i = input.length(); i >= 0; i--){
    std::cout << input[i];
  }

  std::cout << std::endl;
  return 0;
}
