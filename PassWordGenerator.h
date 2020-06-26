// password-game/passwordGenerator.h
#include <vector>
#include <string>
class PassWordGenerator {

public:
    PassWordGenerator(std::vector<std::string> tokens);

    std::string getRandomPassword(int numWords);

    void setIterationLength(int numWords);

    std::string next();

    bool hasNext();  // false condition when curser is at length of tokens

private:
    std::vector<std::string> _tokens;
  };
