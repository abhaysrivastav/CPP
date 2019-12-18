#include <iostream>
#include <string>

class Player
{
private:
   std::string name;
   int health;
   int xp;
public:
// Overloaded Constructors
    Player();
    Player(std::string name_val);
    Player(std::string name_val, int health_val, int xp_val);
};

Player::Player():Player{"None", 0, 0}{
    std::cout << "No-args constructor" << std::endl;
}

Player::Player(std::string name_val): Player{name_val, 0, 0}{
    std::cout << "One-args constructor" << std::endl;
}

Player::Player(std::string name_val, int health_val, int xp_val)
    : name{name_val}, health{health_val}, xp{xp_val} {
            std::cout << "Three-args constructor" << std::endl;
}

int main()
{
    Player player;
    Player frank{"Frank"};
    Player abhay{"Abhay" , 100, 55};
    return 0;
}
