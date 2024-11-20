//  CSC 150  Lab 13  Wheel of Misfortune with files
//  V. Manes 4/15/15

#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE

#include <iostream>
#include <cstring>
#include <cctype>
#include <fstream>
using namespace std;

const int MAX = 100;

//functions from lab11
void update_solution( const char phrase[], char found[], char ch);
void init_solution( char found[], const char phrase[] );
bool test_guess( const char phrase[], const char guess[] );

//functions from lab13
bool play_round( const char phrase[] ); //main game action moved out of main


int main(  )
{
	char phrase[MAX] = "";
	ifstream fin;
	ofstream fout;
	int win_count = 0;
	int lose_count = 0;
	
	//test arguments
	
	
	
	//open and test files
	fin.open("phrases.txt");
	fout.open("score.txt");

	if(!fin || !fout)
	{
		cout<<"phrases.txt would not open"<<endl;
		return 0;
	}
	
	
	
	//read line from file, play the phrase, repeat
	while(fin.getline(phrase, MAX))
	{
		if(play_round(phrase))
		{
			fout<<"Guess: "<<phrase<<endl;
			win_count++;
		}
		else
		{
			fout<<"Missed: "<<phrase<<endl;
			lose_count++;
		}
	}
	
		//write to output for win or loss on phrase
	
	//write score summary
	fout<<"Total wins: "<<win_count<<endl;
	fout<<"Total misses: "<<lose_count<<endl;
	
	//display score to player
	cout<<"Wins: "<<win_count<<endl;
	cout<<"Misses: "<<lose_count<<endl;
	
	fin.close();
	fout.close();
    return 0;
}
//plays the game. input is a single phrase. 
//returns true if player guesses correctly, false if player gives up
bool play_round( const char phrase[] ) //main game action moved out of main
{
	char found[MAX] =  "" ;
	char guess[MAX] = "";
	int index;
	int pos;
	char input;
	char choice;
	bool won = false;
	bool quit = false;
	
	cout << "\n\nNew phrase\n" << endl;
	
	init_solution( found,  phrase );
	cout << "The phrase : " << found << endl;

	do
	{
		cout << endl << "Guess a letter: " ;
		cin >> input;

		update_solution( phrase, found, input );
	
		cout << "The phrase : " << found << endl;

		cout << endl << "Guess the phrase? y/n: ";
		cin >> choice;

		if( choice == 'y' )
		{
			cin.ignore();
			cout << "Your guess: " ;
			cin.getline( guess, MAX );

			won = test_guess( phrase, guess );

			if( won )
				cout << "Whoopee, you did it!" << endl << endl;
			else
			{
				cout << "That's not it. " << endl ;
				cout << "Keep playing this phrase? y/n: ";
				cin >> choice;
				if( tolower(choice) == 'n' )
					quit = true;
			}
		}
	}while ( !won && !quit );
	
	return won;
	
}




void update_solution( const char phrase[], char found[], char ch )
{
	for (int i = 0; i < strlen(phrase); i++)
	{
		if (tolower(phrase[i]) == tolower(ch))
			found[i] = ch;
	}
}

void init_solution( char found[], const char phrase[] )
{
	int i = 0;
	int len = strlen( phrase );

	for( i = 0; i < len; i++ )
	{
		if( phrase[i] != ' ' )
			found[i] = '_';
		else
			found[i] = ' ';
	}

	found[i] = '\n';
}

bool test_guess( const char phrase[], const char guess[] )
{
	char s1[MAX] = "";
	char s2[MAX] = "";

	strcpy( s1, phrase );
	strcpy( s2, guess );

	strlwr( s1 );
	strlwr( s2 );

	if( strcmp( s1, s2 ) == 0 )
		return true;
	else
		return false;
}


