#pragma once
#include "Player.h"
#include <iostream>

void swap(Player*& xp, Player* yp);
void Bubble_sort(Player**& profile_array, int& n);
bool compare_words(std::string key, std::string other);
Player* Binary_search(Player**& profile_array, int& n, std::string K);