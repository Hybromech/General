#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "Player.h"
#include "Search_and_Sort.h";

extern Player** profile_array;
extern Player* user;//current user.
extern std::string const file_name;
extern bool gameisRunning;
extern int profile_size;
extern int profile_length;
extern const int profile_init;
extern int profile_index;

void expand_array(Player**& profile_array, int& profile_size);
void Manage_profile(Player**& profile_array, int& profile_size, int& profile_length, Player*& user);
void Create_profile(char* player_name);
int load_file_info();
void load_player_data(Player**& profile_array);
void write_player_data(Player**& profile_array, int& profile_length);
bool Files_exists(std::string filename);
void display_player_data(Player* player);
void printArray(Player**& profile_array, int size);

	
