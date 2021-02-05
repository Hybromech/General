#include "Search_and_Sort.h"

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
			if (profile_array[j] != nullptr)
				current_name = profile_array[j]->Return_info("name");
			if (profile_array[j + 1] != nullptr)
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
void swap(Player*& xp, Player* yp)
{
	Player temp = *xp;
	*xp = *yp;
	*yp = temp;
}