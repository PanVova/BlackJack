#include <iostream>
#include <vector>
#include <time.h>  
#include <algorithm> 
using namespace std;

int random_card(int size);
int sum_hand(vector<int> hand);
void check_status_player(vector<int> player);
void check_status_totally(vector<int> player_hand, vector<int> dealer_hand);
void choice(int number);
void clear();
void starter_hand();
void draw_card();
void show_hand();
void set_bet();

vector<int> numbers = { 2,3,4,5,6,7,8,9,10,10,10,10, 11 , 2,3,4,5,6,7,8,9,10,10,10,10, 11  , 2,3,4,5,6,7,8,9,10,10,10,10, 11  , 2,3,4,5,6,7,8,9,10,10,10,10, 11 };
vector<int> player_hand;
vector<int> dealer_hand;

bool can_enter = true;
int money = 100;
int your_bet = 0;
int multiplier = 1;

int main() 
{
	while (true) {
		srand(time(NULL));

		set_bet();

		starter_hand();

		if (player_hand[0] + player_hand[1] == 21)
		{
			can_enter = false;
		}

		int number = 0;
		while (can_enter) {
			cout << "Choice what to do : 1 - draw a card , 2 - Stop drawing , 3 - Double Down"<< endl;
			cin >> number;
			choice(number);
		}

		//dealer turns
		while (true)
		{
			if (sum_hand(dealer_hand) < 17 && sum_hand(player_hand) < 21)
			{
				dealer_hand.push_back(numbers[random_card(numbers.size())]);
				cout << "Dealer draw a " << dealer_hand[dealer_hand.size() - 1] << endl;
				numbers.erase(find(numbers.begin(), numbers.end() - 1, dealer_hand.size() - 1));
				
				for (auto &i : dealer_hand) { cout << i << " "; }
				cout << '\n';
			}
			else { break; }
		}

		check_status_totally(player_hand, dealer_hand);

		if (money == 0) 
		{
			cout << "You lost all of your money" << endl;
			break;
		}
		cout << "Wanna play more ? 1- no, everything else is yes" << endl;
		int a;
		cin >> a;
		if (a == 1 ) 
		{
			break;
		}
		clear();
	}
}

void set_bet() 
{
	cout << "You have " << money << " dollars" << endl;
	cout << "Set your bet : ";

	cin >> your_bet;
	while (true) {
		if (your_bet <= money)
		{
			break;
		}
		else if (your_bet > money)
		{
			cout << "Try again" << endl;
		}
	}
}

void starter_hand() 
{
	player_hand.push_back(numbers[random_card(numbers.size())]);
	numbers.erase(find(numbers.begin(), numbers.end() - 1, player_hand[0]));
	player_hand.push_back(numbers[random_card(numbers.size())]);
	numbers.erase(find(numbers.begin(), numbers.end() - 1, player_hand[1]));


	dealer_hand.push_back(numbers[random_card(numbers.size())]);
	numbers.erase(find(numbers.begin(), numbers.end() - 1, dealer_hand[0]));
	dealer_hand.push_back(numbers[random_card(numbers.size())]);
	numbers.erase(find(numbers.begin(), numbers.end() - 1, dealer_hand[1]));

	show_hand();

	cout << "Total Sum : " << sum_hand(player_hand) << endl;

	cout << "\nHand of a dealer :  " << dealer_hand[0] << " , " <<" *" << endl;
}

void show_hand() 
{
	cout << "\nHand of a player : ";
	for (auto &i : player_hand) { cout << i << " "; }
	cout << '\n';
}

void clear() 
{
	player_hand.clear();
	dealer_hand.clear();
	can_enter = true;
	multiplier = 1;
	vector<int> numbers = { 2,3,4,5,6,7,8,9,10,10,10,10, 11 , 2,3,4,5,6,7,8,9,10,10,10,10, 11  , 2,3,4,5,6,7,8,9,10,10,10,10, 11  , 2,3,4,5,6,7,8,9,10,10,10,10, 11 };

}

int random_card(int size)
{
	return rand() % + size ;
}

void draw_card() 
{
	player_hand.push_back(numbers[random_card(numbers.size())]);
	cout << "You draw a " << player_hand[player_hand.size() - 1] << endl;
	numbers.erase(find(numbers.begin(), numbers.end() - 1, player_hand.size() - 1));
}

int sum_hand(vector<int> hand) 
{
	int sum=0;
	for (auto &i : hand) { sum += i; }
	return sum;
}

void check_status_totally(vector<int> player_hand, vector<int> dealer_hand)
{
	int player_hand_sum = 0;
	for (auto &i : player_hand) { player_hand_sum += i; }
	int dealer_hand_sum = 0;
	for (auto &j : dealer_hand) { dealer_hand_sum += j; }


	if (player_hand_sum > dealer_hand_sum && player_hand_sum <= 21 || dealer_hand_sum > 21 && player_hand_sum < 21 )
	{
		cout << "You win " << endl;
		money = money +  your_bet*multiplier;
	}
	else if (player_hand_sum < dealer_hand_sum || player_hand_sum > 21 && dealer_hand_sum <21 )
	{
		cout << "You lose" << endl;
		money -= your_bet;
	}
	else if(player_hand_sum == dealer_hand_sum)
	{
		cout << "Equal" << endl;
	}
	cout << "You have : " << money << " dollars" << endl;

}

void check_status_player(vector<int> player)
{
	int sum = 0;
	for (auto &i : player) { sum += i; }
	if (sum < 21) 
	{
		cout << "You can draw another card" << endl;
	}
	else if (sum > 21) 
	{
		can_enter = false;
	}
	else 
	{
		can_enter = false;
	}

	cout << "Total Sum : " << sum << endl;
}

void choice(int number) 
{
	switch (number) 
	{
	case 1: // draw a card
		draw_card();
		show_hand();
		check_status_player(player_hand);
		break;
	case 2: // stop
		can_enter = false;
		break;
	case 3: // double_down
		draw_card();
		show_hand();
		can_enter = false;
		multiplier = 2;
		break;
	}
}