#include "player.hh"
#include <iostream>
#include <string>

using namespace std;

Player::Player(string name):
    name_(name){
}
string Player::get_name() {
    return name_;
}
void Player::add_points(int points) {
    points_ += points;
    if (points_ > 50) {
        cout << name_ << " gets penalty points!" << endl;
        points_ = 25;
        return;
    }
    if (points_ == 50){
        return;
    }
    return;
}
bool Player::has_won(){
    if (points_ == 50) {
        has_won_ = true;
    }else {
        has_won_ = false;
    }
    return has_won_;
}
int Player::get_points(){
    return points_;
}
