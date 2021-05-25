#include "Player.h"

Player::Player(std::string name) {
    this->name = name;
    this->score = 0;
    this->playerHand = new LinkedList();
}

Player::~Player() {
    delete playerHand;
    playerHand = nullptr;
}
    
std::string Player::getName() {
    return name;
}

int Player::getScore() {
    return score;
}

LinkedList* Player::getPlayerHand() {
    return playerHand;
}

void Player::setScore(int score) {
    this->score = score;
}

void Player::setName(std::string name) {
    this->name = name;
}
    
void Player::setPlayerHand(LinkedList* hand) {
    this->playerHand = hand;
}

void Player::incrementScore(int newScore) {
    this->score += newScore;
}

void Player::printPlayerHand(){
    playerHand->printList();
}