#include "Database_tools.h"

int main()
{
	// create an array of pointers to player pointers and initialise all points in the array to nullptr 
	
	// Load in data from binary file
	//profile_length = load_file_info();
	std::cout << "number of profiles is " << profile_length << std::endl;
	load_player_data(profile_array);
	
	//Sort profile array.
	std::cout << "Sorting array...." << std::endl;
	Bubble_sort(profile_array, profile_length);
	printArray(profile_array, profile_length);
	
	while (gameisRunning)
	{
		Manage_profile(profile_array, profile_size, profile_length, user);
	}

	system("pause");
	return 0;
}



