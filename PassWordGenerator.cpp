// password-game/passwordgame.h
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include "PassWordGenerator.h"


PassWordGenerator::PassWordGenerator(std::vector<std::string> tokens){
  _tokens = tokens;
}

std::string PassWordGenerator::getRandomPassword(int numWords) {
  return "hi";
}

void PassWordGenerator::setIterationLength(int numWords) {
 return;
}

std::string PassWordGenerator::next() {
  return "hi";
}

bool PassWordGenerator::hasNext() {
  return 1;
}
