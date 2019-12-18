#include <iostream>

class Player
{
private:
   std::string name {"XXXXXXX"};
   int health;
   int xp;
public:
// Overloaded Constructors
    Player();
    Player(std::string name_val);
    Player(std::string name_val, int health_val, int xp_val);
};

Player::Player(): name{"None"}, health{0}, xp{0}{
    std::cout << "No- arg constrctor" << std::endl;
}

Player::Player(std::string name_val): name{name_val}, health{0}, xp{0} {
    std::cout << "Single- arg constrctor" << std::endl;
}

Player::Player(std::string name_val, int health_val, int xp_val): name{name_val}, health{health_val}, xp{xp_val}{
    std::cout << "Three- arg constrctor" << std::endl;
}
using namespace std;

int main()
{
    Player player;
    Player frank{"Frank"};
    Player Abhay{"Abhay", 100, 55};
    return 0;
}
