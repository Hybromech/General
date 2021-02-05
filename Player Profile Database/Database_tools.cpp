#include "Database_tools.h"

Player** profile_array = new Player * [profile_size]();
Player* user = nullptr;//current user.
std::string const file_name = "Player profile database.dat";
bool gameisRunning = true;
int profile_size = 100;
int profile_length = 0;
const int profile_init = 100;
int profile_index = 0;

void Manage_profile(Player**& profile_array, int& profile_size, int& profile_length, Player*& user)
{
	int input;
	int id;
	int score;
	char player_name[100];
	std::string search_key;
	
	if (user != nullptr)
	std::cout << "----Current Player---- " << user->Return_info("name") << "\n" << std::endl;
	std::cout << "Would you like to do?\n 1: create a new profile \n 2: use an existing profile \n 3: View all profiles\n 4: Modify profile\n 5:Exit" << std::endl;
	std::cin >> input;
	std::cin.clear();
	std::cin.ignore();

	switch (input)
	{
	case 1:
	{
		//create new profile.
		//check if array is large enough.
		if (profile_length >= profile_size)
		{
			//pass by reference the array of pointers to player pointers to the array expander
			expand_array(profile_array, profile_size);
		}
		Create_profile(player_name);
		break;
	}
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
void Create_profile(char* player_name)
{
	// create players and add them to the dynamic array
	std::fstream file;
	file.open("Player profile database.dat", std::ios::in | std::ios::out | std::ios::binary);
	for (size_t i = 0; i < profile_init; i++)
	{
		if (profile_array[profile_index]->Return_info("name") == "unknown")//check if current pos is unknown.
		{
			std::cout << "Please type in your name" << std::endl;
			//std::getline(std::cin, player_name);
			std::cin >> player_name;
			auto temp_player = new Player(profile_index, player_name, 0, true);
			profile_array[profile_index] = temp_player;
			user = temp_player;

			//write new player to the file.
			file.write((char*)profile_array[profile_index], sizeof(Player));
			file.close();
			std::cout << "Done. Profile added." << std::endl;
			break;
		}
		else
		{
			file.seekp((size_t)sizeof(Player), std::ios::cur);//seek to the next player.
		}
		profile_index++;
	}
}
void expand_array(Player**& profile_array, int& profile_size)
{
	// Take a reference to a dynamic array of pointers to player pointers and the size of the array 
	// Create a new array twice as big and copy across the player pointers into the new pointer array and then update
	// the profile_array pointer to point to the new double sized array of pointers.
	//std::cout << profile_array[1]->Return_info("name");
	profile_size *= 2;
	Player** artemp = new Player * [profile_size];
	for (int i = 0; i < profile_size; i++)
	{
		//std::cout << profile_array[0];
		// check if the array of pointers is pointing to nullptr i.e. no player pointers has been assigned yet and no need to copy it.
		if (profile_array[i] != nullptr)
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
void load_player_data(Player**& profile_array)
{
	std::fstream file;//create file stream handle
	file.open(file_name);
	if (file)//Check if file is exists.
	{
		file.close();
		std::cout << "file exists" << std::endl;
		file.open(file_name, std::ios::in | std::ios::binary);//open file
		//file.seekg(sizeof(int), std::ios::beg);//move read marker away from the profile size int.
		for (size_t i = 0; i < profile_init; i++)
		{
			profile_array[i] = new Player(i);//create new player set id.
			file.read((char*)profile_array[i], sizeof(Player));//read in chunk of binary data to player.
			profile_array[i]->is_modified = false;//reset "is modified" to false so program does not rewrite player data in write method.
			if (profile_array[i]->Return_info("name") != "unknown")
			{
				profile_length++;
				std::cout << "Loaded player data for " << profile_array[i]->Return_info("name") << profile_array[i]->Return_numeric("id") << std::endl;
			}
		}
		file.close();
	}
	else // file does not exist.
	{
		std::cout << "file does not exist" << std::endl;
		file.open("Player profile database.dat", std::ios::out | std::ios::binary);//open file
		//file.seekp(sizeof(int), std::ios::beg);//move the write marker away from the profile size int.
		for (size_t i = 0; i < profile_init; i++)
		{
			char u[] = "unknown";
			profile_array[i] = new Player(i, u, 0, false);//create new player set id.
			file.write((char*)profile_array[i], sizeof(Player));//write new player.
			//profile_array[i]->is_modified = false;//reset "is modified" to false so program does not rewrite player data in write method.
			//std::cout << "Created player data for player id " << profile_array[i]->Return_numeric("id") << std::endl;
			std::cout << "Created player data for " << profile_array[i]->Return_info("name") << profile_array[i]->Return_numeric("id") << std::endl;
			profile_length++;
		}

		file.close();
	}
	//load data from the file to the program.


	file.close();
	Bubble_sort(profile_array, profile_length);
}
void write_player_data(Player**& profile_array, int& profile_length)//rewrite existing players
{
	//write data from the file to the program.
	std::fstream file;
	Player* profile_in_file = new Player();//blank player
	file.open(file_name, std::ios::in | std::ios::out | std::ios::binary);//wont destroy data
	if (file.is_open())//check if the file is open
	{
		//file.write((char*)&profile_length, sizeof(int));//write the profile length!!!
		//std::cout << "profile length is" << profile_length;
		for (size_t i = 0; i < profile_init; i++)
		{
			auto readhead = file.tellg();
			file.read((char*)profile_in_file, sizeof(Player));//read in data and store in temp player.!!!!!!
			std::cout << "readhead is " << readhead << std::endl;
			std::cout << " data in file is " << profile_in_file->Return_info("name") << std::endl;
			std::cout << " target profile player " << user->Return_info("name") << std::endl;
			if (profile_in_file->Return_info("name") == user->Return_info("name"))//if name is file matches target name.
			{
				if (user->is_modified == true)// check if the data has been modified.
				{
					std::cout << "current write position " << file.tellp();
					file.write((char*)user, sizeof(Player));//Write player contents to file.
					std::cout << "Data Written for player " << user->Return_info("name") << std::endl;
				}
		}
			else
			{
				//file.seekp((size_t)sizeof(Player), std::ios::cur);//seek to the next player.
			}
		}
		file.close();
	}
}
bool Files_exists(std::string filename)
{
	std::ifstream file;
	file.open(filename.c_str(), std::ios::in);
	if (file.good())
		return true;
	else return false;
}
void display_player_data(Player* player)
{
	std::cout << "player id is " << player->Return_info("id") << std::endl;
	std::cout << "player name is " << player->Return_info("name") << std::endl;
	std::cout << "player score is " << player->Return_numeric("score") << std::endl;
}
void printArray(Player**& profile_array, int size)
{
	for (int i = 0; i < size - 1; i++)
	std::cout << profile_array[i]->Return_numeric("id") << profile_array[i]->Return_info("name") << " ";
	std::cout << std::endl;
}
