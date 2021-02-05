#pragma once
#include <string>
class Player
{
protected:
	char name[100];//player name
		int player_id;
		int highscore = 0;
	public:
		std::string Return_info(std::string);
		bool is_modified;
		int Return_numeric(std::string);
		void Set_numeric(std::string type, int val);
		Player();
		Player(int player_id, char* p_name, int highscore, bool mod);
		Player(int player_id);
		~Player();
	
};
