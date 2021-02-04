#include "player.h"

Player::Player()//constructor
{
	player_id = 0;
	highscore = 0;
	is_modified = false;
}
Player::Player(int p_id)//constructor
{
	player_id = p_id;
	highscore = 0;
	is_modified = false;
}
Player::Player(int p_id, char* p_name, int p_highscore, bool mod)//constructor
{
	player_id = p_id;
	strcpy_s(name, p_name);
	highscore = p_highscore;
	is_modified = mod;
}
Player::~Player()//destructor
{
}
std::string Player::Return_info(std::string type)//type = id or name
{
	if (type == "name")
	{
		return name;
	}
}
int Player::Return_numeric(std::string type)
{
	if (type == "id")
	{
		return player_id;
	}
	else if (type == "score")
	{
		return highscore;
	}
}
void Player::Set_numeric(std::string type, float val)
{
	if (type == "id")
	{
		player_id = val;
	}
	else if (type == "score")
	{
		highscore = val;
	}
}