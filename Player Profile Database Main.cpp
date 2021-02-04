#include <iostream>
#include <fstream>
#include <string>
#include "Player.h"
#include <algorithm>
#include <vector>
//Function declarations.
void load_player_data(Player**&);
int load_file_info();
void write_player_data(Player**&, int& profile_length);
void display_player_data(Player* player);
void expand_array(Player**&, int&);
void Manage_profile(Player**&, int&, int&, Player*& user);
void Bubble_sort(Player**&, int& n);
void printArray(Player**& profile_array, int size);
Player* Binary_search(Player**& profile_array, int& n, std::string K);
bool gameisRunning = true;
int profile_size = 100;
int profile_length = 0;
int main()
{
	// create an array of pointers to player pointers and initialise all points in the array to nullptr 
	Player** profile_array = new Player*[profile_size]();
	// Load in data from binary file
	profile_length = load_file_info();
	std::cout << "number of profiles is " << profile_length << std::endl;
	load_player_data(profile_array);
	
	//Sort profile array.
	//std::cout << "Sorting array...." << std::endl;
	//Bubble_sort(profile_array, profile_length);
	printArray(profile_array, profile_length);
	Player* user = nullptr;//current user.
	while (gameisRunning)
	{
		Manage_profile(profile_array, profile_size, profile_length, user);
	}

	system("pause");
	return 0;
}

// Take a reference to a dynamic array of pointers to player pointers and the size of the array 
// Create a new array twice as big and copy across the player pointers into the new pointer array and then update
// the profile_array pointer to point to the new double sized array of pointers.
void expand_array(Player **&profile_array, int &profile_size)
{
	//std::cout << profile_array[1]->Return_info("name");
	profile_size *= 2;
	Player** artemp = new Player*[profile_size];
	for (int i = 0; i < profile_size; i++)
	{
		//std::cout << profile_array[0];
		// check if the array of pointers is pointing to nullptr i.e. no player pointers has been assigned yet and no need to copy it.
		if(profile_array[i] != nullptr)
		artemp[i] = profile_array[i];
	}
	delete[] profile_array;
	//std::cout << artemp[1]->Return_info("name");
	profile_array = artemp;

	//auto old_size = *profile_size;
	//*profile_size += 100;//expand array size
	//*profile_array = new Player[*profile_size];
	//
	//for (size_t i = 0; i < old_size; ++i)//pop new array
	//{
	//	*profile_array[i] = artemp[i];
	//}
}
void Manage_profile(Player**& profile_array, int& profile_size, int &profile_length, Player*& user)
{
	int input;
	int id;
	int score;
	
	std::string search_key;
	char player_name[100];
	
	if(user != nullptr)
	std::cout << "----Current Player---- " << user->Return_info("name") << "\n" << std::endl;
	std::cout << "Would you like to do?\n 1: create a new profile \n 2: use an existing profile \n 3: View all profiles\n 4: Modify profile\n 5:Exit" << std::endl;
	std::cin >> input;
	std::cin.clear();
	std::cin.ignore();
	
	
	switch (input)
	{
	case 1:
		//create new profile.
		//check if array is large enough.
		if (profile_length >= profile_size)
		{
			//pass by reference the array of pointers to player pointers to the array expander
			expand_array(profile_array, profile_size);
		}
		// create players and add them to the dynamic array
		std::cout << "Please type in your name" << std::endl;
		//std::getline(std::cin, player_name);
		std::cin >> player_name;
		profile_array[profile_length] = new Player(profile_length, player_name, 0,true);	
		profile_length++;
		std::cout << "Done. Profile added." << std::endl;
		
		break;
	case 2:
		//search existing profile.
		//ask user for desired name.
		//search database for chosen name.
		//store the profiles id in a new int array.
		std::cout << "Please select your profile by typing in the desired users name" << std::endl;
		std::getline(std::cin, search_key);
		user = Binary_search(profile_array, profile_length, search_key);
		std::cout << "Player profile loaded" << std::endl;
		break;
	case 3: 
	//view all.
		for (size_t i = 0; i < profile_length; i++)
		{
			std::cout << "Player name is " << profile_array[i]->Return_info("name") << std::endl;
			std::cout << "Player id is " << profile_array[i]->Return_numeric("id") << std::endl;
			std::cout << "Player highscore is " << profile_array[i]->Return_numeric("score") << std::endl;
		}
		break;
	case 4://Modify player data
	{
		if (user != nullptr)//if a user has been extracted
		{
			std::cout << "How much would you like to increase the score by?" << std::endl;
			int addscore;
			std::cin >> addscore;
			user->Set_numeric("score", addscore);
			user->is_modified = true;
			std::cout << "Done score modified!" << std::endl;
		}
		break;
	}
	case 5://Write out player data on exit.
		write_player_data(profile_array, profile_length);
		gameisRunning = false;
		break;
	}
}
int load_file_info()
{
	//load data from the file to the program.
	std::cout << "Loading game info " << std::endl;
	int profile_size = 0;
	std::fstream file;//create file stream handle
	file.open("Player profile database.dat", std::ios::in | std::ios::binary);//open file
	if (!file.eof())//check if the file is not blank
	{
		file.read((char*)&profile_size, sizeof(int));
		std::cout << "profile_size is" << profile_size;
	}
	file.close();
	return profile_size;
}
void load_player_data(Player **&profile_array)
{
	//load data from the file to the program.
	std::fstream file;//create file stream handle
	file.open("Player profile database.dat", std::ios::in | std::ios::binary);//open file
	file.seekp(sizeof(int), std::ios::beg);
																			  //file.seekg(sizeof(int), std::ios::beg);//move read marker away from the profile size int.
	if (profile_length > 0)// if there is a profile in the file.
	{
		for (size_t i = 0; i < profile_length ; i++)
		{
			profile_array[i] = new Player(i);//create new player set id.
			file.read((char*)&*profile_array[i], sizeof(Player));//read in chunk of binary data to player.
			profile_array[i]->is_modified = false;//reset "is modified" to false so program does not rewrite player data in write method.
			std::cout << "Loaded player data for " << profile_array[i]->Return_info("name") << profile_array[i]->Return_numeric("score") << std::endl;
		}
	}
	file.close();
	Bubble_sort(profile_array, profile_length);
}
void write_player_data(Player **& profile_array, int& profile_length)
{
	//write data from the file to the program.
	std::cout << "Sorted Profile database" << std::endl;
	std::fstream file;
	Player* temp = new Player();
	file.open("Player profile database.dat",std::ios::in | std::ios::out | std::ios::binary);//wont destroy data
	
	if (file.is_open())//check if the file is open
	{
		file.seekp(0, std::ios::beg);//write at beggining
		file.write((char*)&profile_length, sizeof(int));//write the profile length
		std::cout << "profile length is" << profile_length;

		for (size_t i = 0; i < profile_length; i++)
		{
			if (profile_array[i] != nullptr)
			{
				if (profile_array[i]->is_modified == true)// check if the data has been modified.
				{
					file.read((char*)&*temp, sizeof(Player));//read in data and store in temp player.
				
					if (temp->Return_info("name") == profile_array[i]->Return_info("name"))//if name is file matches target name.
					{
						file.write((char*)&*profile_array[i], sizeof(Player));//Write player contents to file.
						std::cout << "Data Written for player " << profile_array[i]->Return_info("name") << std::endl;
					}
					else
					{
						file.seekp(i + (size_t)sizeof(Player), std::ios::cur);
					}
					
				}
			}
			


		}
		file.close();
	}
	
	
}
void display_player_data(Player *player)
{
	std::cout << "player id is " << player->Return_info("id") << std::endl;
	std::cout << "player name is " << player->Return_info("name") << std::endl;
	std::cout << "player score is " << player->Return_numeric("score") << std::endl;
}

void swap(Player*& xp, Player* yp)
{
	Player temp = *xp;
	*xp = *yp;
	*yp = temp;
}
void Bubble_sort(Player**& profile_array, int& n)
{
	int i, j;
	std::string current_name = "empty";
	std::string subsequent_name = "empty";
	for (i = 0; i < n - 1; i++)
	{
		// Itterate through array.
		for (j = 0; j < n - i - 1; j++)
		{
			if(profile_array[j] != nullptr)
			current_name = profile_array[j]->Return_info("name");
			if(profile_array[j + 1] != nullptr)
			subsequent_name = profile_array[j + 1]->Return_info("name");

			for (size_t i = 0; i < current_name.size(); i++)//loop through the word.
			{
				auto current_letter = current_name[i];
				auto subsequent_letter = subsequent_name[i];
				if (current_letter > subsequent_letter)//letter on right is greater.
				{
					//std::cout << " swapping " << profile_array[j]->Return_info("name") << " with " << profile_array[j+1]->Return_info("name");
					auto temp = profile_array[j];
					profile_array[j] = profile_array[j + 1];//swap left with right.
					profile_array[j + 1] = temp;
					break;
				}
				else if (current_letter == subsequent_letter)
					continue;
				else
					break;
			}

		}
		
	}
	//for (i = 0; i < n ; i++)//numberize array
	//{
	//	profile_array[i]->Set_numeric("id",i);
	//}
}
bool compare_words(std::string key, std::string other)
{
	//return value of true means the search key is smaller.
	//return value of false means the search key is larger.
	//in a for loop compare each letter in string key and other.
	//if either side returns null then break out of the loop and
	//return the smaller word.
	//if not then compare each character until a unique one is found.
	for (size_t i = 0; i < key.size(); i++)
	{
		auto left_letter = key[i];
		auto right_letter = other[i];
		if (left_letter == NULL || right_letter == NULL)
		{
			if (key.size() < other.size())
				return true;
			else
				return false;//other must be a larger word.
		}
			if (left_letter < right_letter)//left letter has lower decimal value therefore a higher letter.
			return true;
		else if (left_letter > right_letter)//right letter has lower decimal value therefore a higher letter.
			return false;
	}
}
Player* Binary_search(Player**& profile_array, int& n, std::string K)
{
	int L = 0;
	int R = n - 1;
	int M = 0;
	while (L <= R)
	{
			M = (L + R) / 2;
			if (profile_array[M]->Return_info("name") == K)//if M equals the search key.
			{
				std::cout << "Match found!" << std::endl;
				return profile_array[M];
			}
			else //find out whether the search string is greater or less than M.
			{
				if (compare_words(K, profile_array[M]->Return_info("name")) == false)
					L = M + 1;
				else
					R = M - 1;
			}
	}
	std::cout << "No match was found" << std::endl;
	return nullptr;
}
void printArray(Player**& profile_array, int size)
{
	int i;
	for (i = 0; i < size - 1; i++)
		std::cout << profile_array[i]->Return_numeric("id") << profile_array[i]->Return_info("name") << " ";
	std::cout << std::endl;
}
