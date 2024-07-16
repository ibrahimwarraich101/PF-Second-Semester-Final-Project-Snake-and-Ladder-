#include <iostream>
#include <ctime>
#include <string>
#include <fstream>
#include<windows.h>
#include <Wincon.h>

using namespace std;

int board[100];
int position[4] = { 0 };
bool entered[4] = { false };
int turns[4] = { 0 };
int winners[4] = { 0 };

int diceroll()
{
	srand(time(0));
	return rand() % 6 + 1;
}

void player_data()
{
	cout << "Players\t\tSigns\t\tLocation\tTurns\n";
	for (int i = 0; i < 4; i++) {
		cout << i + 1 << "\t\t";
		switch (i) {
		case 0:
			cout << "*\t\t";
			break;
		case 1:
			cout << "&\t\t";
			break;
		case 2:
			cout << "#\t\t";
			break;
		case 3:
			cout << "$\t\t";
			break;
		}
		cout << position[i] + 1 << "\t\t";
		cout << turns[i] << "\n";
	}
	cout << endl;

}

void boardplaces()
{
	// For snakes
	board[98] = 79;		board[94] = 74;		board[91] = 87;		board[88] = 67;		board[73] = 52;
	board[63] = 59;		board[61] = 18;		board[45] = 24;		board[48] = 10;		board[15] = 5;

	//For ladders
	board[1] = 37;		board[7] = 30;		board[14] = 25;		board[20] = 41;		board[35] = 43;
	board[27] = 83;		board[50] = 66;		board[86] = 93;		board[77] = 97;		board[70] = 90;

}

void credits()
{
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleInfo);
	WORD originalAttributes = consoleInfo.wAttributes;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE);
	cout << endl << endl;
	cout << "Name: Muhammad Ibrahim\nRoll No: 23F-0590\nSection: BSCS-2E\n\n";
	cout << "Name: Muhammad Siddique\nRoll No: 23F-0669\nSection: BSCS-2E\n\n";

	// Reset the console text attribute
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), originalAttributes);

}

void rules()
{
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleInfo);
	WORD originalAttributes = consoleInfo.wAttributes;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);

	cout << "Instructions are:\n\n";
	cout << "1. The Player can start a game by getting a six." << endl;
	cout << "2. If two player goes on same point ,first player will go to previous point." << endl;
	cout << "3. If player goes on snake'mouth point he will move to snake'tail point." << endl;
	cout << "4. If player goes on ladder'intial point then he will move to ladder'end point." << endl;
	cout << "5. First winner can give 6 score to any other player as a gift." << endl;
	cout << "6. If player gets 6 he will get another turn." << endl;
	cout << "7. If player gets three consecutive 6 those score will be skipped." << endl;
	cout << "8. Game will end when any three players will win." << endl;

	// Reset the console text attribute
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), originalAttributes);

}

bool checkturn(int turn)
{
	if (winners[turn] == 1)
		return false;
	return true;
}

void printBoard()
{
	bool dir = 1;
	int c = 99, c2 = 99, starter, change;
	string str = "";
	cout << "\n-------------------------------------------------------------\n";

	for (int i = 0; i < 10; i++)
	{
		if (dir)
		{
			starter = c;
			change = -1;
		}
		else
		{
			starter = c - 9;
			change = 1;
		}
		cout << "|";
		if (i == 0)
		{
			cout << " ";
		}
		for (int j = starter, k = 0; k < 10; k++, j += change, c--)
		{
			if (j < 99)
			{
				cout << "  ";
			}
			if (j <= 8)
			{
				cout << " ";
			}
			cout << j + 1 << " ";
			cout << "|";
		}
		cout << endl;
		cout << "|";
		for (int j = starter, k = 0; k < 10; k++, j += change, c2--)
		{
			if (board[j] == j)
			{
				cout << "     |";
			}
			else
			{
				if (board[j] < 99)
				{
					cout << "  ";
				}
				if (board[j] <= 8)
				{
					cout << " ";
				}
				cout << board[j] + 1 << " ";
				cout << "|";
			}
		}
		c2 = c;
		cout << "\n";
		for (int j = starter, k = 0; k < 10; k++, j += change, c2--)
		{
			str = "";
			cout << "|";
			if (j == position[0])
			{
				str += '*';
			}
			if (j == position[1])
			{
				str += '&';
			}
			if (j == position[2])
			{
				str += '#';
			}
			if (j == position[3])
			{
				str += '$';
			}
			for (int k = 0; k < 4 - str.length(); k++)
			{
				cout << " ";
			}
			cout << str << " ";
		}
		cout << "|\n-------------------------------------------------------------\n";
		dir = !dir;
	}
}

int main()
{
	HANDLE console_color;
	console_color = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	srand(time(0));

	for (int i = 0; i < 100; i++)
	{
		board[i] = i;
	}

	int dice = 0, turn = 0, playerwon = 0, count = 0, winPlr;
	bool winner = true, win = 0;
	int giftreceiver = -1;
	ofstream writer;
	ifstream reader;
	string str;
	char choice;
	char again = '1';

	do
	{
		system("cls");

		cout << "(1) for play the game.\n";
		cout << "(2) for credits.\n";
		cout << "(3) for Rules/Regulations.\n";
		cout << "(4) for Score.\n";
		cout << "Enter your choice: ";
		cin >> choice;
		cout << endl;

		switch (choice)
		{
		case '1':
			winners[turn] = { 0 };
			// for board places
			boardplaces();

			while (playerwon <= 3)
			{
				if (checkturn(turn))
				{
					system("cls");

					player_data();
					printBoard();

					cout << endl;
					cout << "Player " << turn + 1 << "'s Turn:  ";
					system("pause");

					dice = diceroll();
					cout << "\n\tPlayer " << turn + 1 << " Rolled " << dice << endl;
					system("pause");

					if (dice == 6)
					{
						cout << "\n\tYou got an extra turn.\n\n";
						count++;
						system("pause");

						// when the player consective rolled 3 six dices
						if (count == 3)
						{
							cout << "\n\tYou got three consecutive sixes. So, Your turn is considered void!\n\n";
							system("pause");
							if (position[turn] <= 18)
							{
								position[turn] = 1;
							}
							else
							{
								position[turn] -= 18;
							}

							turn = (turn + 1) % 4;
							count = 0;
						}
						turns[turn]++;
						entered[turn] = 1;
						position[turn] += dice;
						continue;
					}
					else
					{
						count = 0;
					}

					if (!entered[turn])
					{
						cout << "\n\tYou need to first dice roll 6 to entered in game.\n";
						system("pause");
						turn = (turn + 1) % 4;

						continue;
					}
					turns[turn]++;

					int previous = position[turn];// to save the position of player 

					position[turn] += dice;
					// for ladder move
					if (position[turn] < board[position[turn]])
					{
						CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
						GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleInfo);
						WORD originalAttributes = consoleInfo.wAttributes;

						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | BACKGROUND_GREEN);
						cout << "\n\tCongratulations! You climbed a ladder!\n\n";
						system("pause");

						// Reset the console text attribute
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), originalAttributes);
					}

					//for snake move
					if (position[turn] > board[position[turn]])
					{
						CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
						GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleInfo);
						WORD originalAttributes = consoleInfo.wAttributes;

						// SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | BACKGROUND_RED);
						cout << "\n\tOh no! You landed on a snake!\n\n";
						system("pause");

						// Reset the console text attribute
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), originalAttributes);
					}					
					
					position[turn] = board[position[turn]];

					//for The first winner can give six moves forward to any other player as gift.
					if (winner && position[turn] >= 99)
					{
						position[turn] = 100;
						cout << "Player " << turn + 1 << " wins!\n";
						playerwon++;
						if (playerwon == 1)
						{
							cout << "Player " << turn + 1 << " wins!\nPlayer " << turn + 1 << " gifts 6 moves forward to another player.\n";
							winner = false;
							cout << "Enter the player number (1-4) to gift 6 moves.: ";
							cin >> giftreceiver;
							giftreceiver--;
							if (giftreceiver < 0 || giftreceiver >= 4 || giftreceiver == turn)
							{
								cout << "Invalid player number. Gift move failed.\n";
							}
							else
							{
								position[giftreceiver] += 6;
								position[giftreceiver] = board[position[giftreceiver]];
								cout << "Player " << turn + 1 << " gifts 6 moves forward to Player " << giftreceiver + 1 << ".\n";
							}
						}
					}

					//If two people are at same point index the first one goes back to initial state.
					for (int i = 0; i < 4; i++)
					{
						if (i != turn && position[i] == position[turn])
						{
							position[turn] = previous;
							break;
						}
					}

					// Condition for when players won the match
					if (position[turn] >= 99)
					{
						position[turn] = 100;
						if (!win)
						{
							win = 1;
							winPlr = turn + 1;
						}
						cout << "\tPlayer " << turn + 1 << " wins!\n\n";
						winners[turn] = 1;
						writer.open("Game_History.txt", ios::app);
						writer << "Winner: Player " << winPlr << "\n\n[Total Turns]\nPlayer 1:" << turns[0] << "\nPlayer 2:" << turns[1] << "\nPlayer 3:" << turns[2] << "\nPlayer 4:" << turns[3] << "\n-------------------------------------------\n\n";
						writer.close();

						playerwon++;
						if (playerwon == 3)
						{
							cout << "\n\tThe game is over because 3 players out of 4 have won the game.\n";
							system("Pause");
							break;
						}
					}

					turn = (turn + 1) % 4;
				}
				else turn = (turn + 1) % 4;

			}
			break;
		case '2':
			credits();
			break;
		case '3':
			rules();
			break;
		case '4':
			reader.open("Game_History.txt");
			while (getline(reader, str)) cout << str << endl;
			reader.close();
			break;
		default:
			cout << "Invalid Input!\n";
		}

		cout << endl << endl;

		cout << "Do you want to continue? Enter any key for continue, 0 for exit: ";
		cin >> again;
		cout << endl << endl;

	} while (again != '0');

	cout << endl;
	system("pause");
	return 0;
}