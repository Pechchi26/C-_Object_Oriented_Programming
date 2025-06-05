#ifndef PLAYER_HH
#define PLAYER_HH

#include <string>

using namespace std;

class Player
{
public:
    //Constructor
    Player(string name);
    //Destructor
    ~Player();

    string get_name();
    int get_points();
    void add_points(int points);

    bool has_won();

private:
    string name_;
    int points_;

};

#endif // PLAYER_HH
