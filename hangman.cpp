/*
		Author: Hayden Gemeinhardt
		hangman.cpp
		Since: 6/6/2020
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		cout << "Failure to open word library. Open readme.txt";
		return 0;
	}

	ifstream f;
	f.open(argv[1]);
	if (!f)
	{
		cout << "File " << argv[1] << " does not exist." << endl;
		return 0;
	}
	
	int numOfWords = 0;
	f >> numOfWords;

	string words[1000];
	for (int i = 0; i < numOfWords; i++)
	{
		f >> words[i];
	}

	srand(time(NULL));
	int command = 0, i = 0;
	while (command != 2)
	{
		cout << "Menu:" << endl << "1. Play" << endl << "2. Quit" << endl << "Input choice-> ";
		cin >> command;

		if (command == 1)
		{
			int lives = 5, letters = 0, correct = 0, a = 0;
			int num = rand() % numOfWords;
			char guess[5];
			string word = words[num];
			string answer, used = "";
			for (int p = 0; word[p]; p++)
			{
				letters++;
				answer.append("_ ");
			}

			cout << endl << "Please enter one letter at a time";
			while (lives != 0)
			{
				cout << endl << "Lives: " << lives << endl << "Used letters: " << used << endl << "Word: ";
				cout << answer << endl << "Enter letter-> ";
			ENTER: cin >> guess;
				if (strlen(guess) != 1)
				{
					cout << endl << "Please enter one and only one letter" << endl << "Enter letter-> ";
					goto ENTER;
				}
				if (!isalpha(guess[0]))
				{
					cout << endl << "Enter a valid letter" << endl << "Enter letter-> ";
					goto ENTER;
				}
				a = 0;
				while (used[a])
				{
					if (used[a] == guess[0])
					{
						cout << endl << "Letter already used, try again" << endl << "Enter letter-> ";
						goto ENTER;
					}
					a++;
				}

				a = 0;
				while(word[a])
				{
					if (word[a] == guess[0])
					{
						answer[a*2] = guess[0];
						correct = 1;
						letters--;
					}
					a++;
				}


				if (correct == 1)
				{
					correct = 0;
				}
				else
					lives--;

				used.push_back(guess[0]);
				used.push_back(' ');

				if (letters == 0)
					break;
			}

			if (lives == 0)
				cout << endl << "Answer: " << word << endl << "Defeat..." << endl << endl;
			else
				cout << endl << "Answer: " << word << endl << "Victory!" << endl << endl;
		}
	}
	f.close();
}
