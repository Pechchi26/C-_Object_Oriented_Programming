#include "player.hh"
#include <iostream>

Player::Player(string name):
    name_(name), points_(0)
{

}

Player::~Player()
{

}

string Player::get_name()
{
    return name_;
}

int Player::get_points()
{
    return points_;
}

void Player::add_points(int points)
{
    points_+=points;
    if(points_>50)
    {
        points_=25;
        std::cout <<name_<<" gets penalty points!"<<std::endl;
    }
}

bool Player::has_won()
{
    if(points_==50)
    {
        return true;
    }
    return false;
}
