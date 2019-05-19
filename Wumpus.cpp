/*
 Author: Akash Magnadia
 */
#include <iostream>
#include <iomanip>   // for setw()
#include <cctype>    // for toupper()
#include <cstdlib>   // for rand() and srand()
#include <ctime>     // to seed random number generator with time(0)
#include <cstring>
#include <string>
using namespace std;

// global constants
#define MAX_LINE_LENGTH 81
#define NUMBER_OF_ROOMS 20

//--------------------------------------------------------------------------------
void displayCave()
{
	cout << "       ______18______             \n"
		<< "      /      |       \\           \n"
		<< "     /      _9__      \\          \n"
		<< "    /      /    \\      \\        \n"
		<< "   /      /      \\      \\       \n"
		<< "  17     8        10     19       \n"
		<< "  | \\   / \\      /  \\   / |    \n"
		<< "  |  \\ /   \\    /    \\ /  |    \n"
		<< "  |   7     1---2     11  |       \n"
		<< "  |   |    /     \\    |   |      \n"
		<< "  |   6----5     3---12   |       \n"
		<< "  |   |     \\   /     |   |      \n"
		<< "  |   \\       4      /    |      \n"
		<< "  |    \\      |     /     |      \n"
		<< "  \\     15---14---13     /       \n"
		<< "   \\   /            \\   /       \n"
		<< "    \\ /              \\ /        \n"
		<< "    16---------------20           \n"
		<< endl;
}//end displayCave()


//--------------------------------------------------------------------------------
void displayInstructions()
{
	cout << "Hunt the Wumpus:                                             \n"
		<< "The Wumpus lives in a completely dark cave of 20 rooms. Each \n"
		<< "room has 3 tunnels leading to other rooms.                   \n"
		<< "                                                             \n"
		<< "Hazards:                                                     \n"
		<< "1. Two rooms have bottomless pits in them.  If you go there you fall and die.  \n"
		<< "2. Two other rooms have super-bats.  If you go there, the bats grab you and    \n"
		<< "   fly you to some random room, which could be troublesome.  Then those bats go\n"
		<< "   to a new room different from where they came from and from the other bats.  \n"
		<< "3. The Wumpus is not bothered by the pits or bats, as he has sucker feet and   \n"
		<< "   is too heavy for bats to lift.  Usually he is asleep.  Two things wake      \n"
		<< "   him up: Anytime you shoot an arrow, or you entering his room.  When he      \n"
		<< "   wakes he moves if he is in an odd-numbered room, but stays still otherwise. \n"
		<< "   After that, if he is in your room, he eats you and you die!                 \n"
		<< "                                                                               \n"
		<< "Moves:                                                                         \n"
		<< "On each move you can do the following, where input can be upper or lower-case: \n"
		<< "1. Move into an adjacent room.  To move enter 'M' followed by a space and      \n"
		<< "   then a room number.                                                         \n"
		<< "2. Shoot your guided arrow through a list of up to three adjacent rooms, which \n"
		<< "   you specify.  Your arrow ends up in the final room.                         \n"
		<< "   To shoot enter 'S' followed by the number of rooms (1..3), and then the     \n"
		<< "   list of the desired number (up to 3) of adjacent room numbers, separated    \n"
		<< "   by spaces. If an arrow can't go a direction because there is no connecting  \n"
		<< "   tunnel, it ricochets and moves to the lowest-numbered adjacent room and     \n"
		<< "   continues doing this until it has traveled the designated number of rooms.  \n"
		<< "   If the arrow hits the Wumpus, you win! If the arrow hits you, you lose. You \n"
		<< "   automatically pick up the arrow if you go through a room with the arrow in  \n"
		<< "   it.                                                                         \n"
		<< "3. Enter 'R' to reset the person and hazard locations, useful for testing.     \n"
		<< "4. Enter 'C' to cheat and display current board positions.                     \n"
		<< "5. Enter 'D' to display this set of instructions.                              \n"
		<< "6. Enter 'P' to print the maze room layout.                                    \n"
		<< "7. Enter 'X' to exit the game.                                                 \n"
		<< "                                                                               \n"
		<< "Good luck!                                                                     \n"
		<< " \n"
		<< endl;
}//end displayInstructions()


void checkForHazard(int adjacentPositions[21][3], int hazards[7]) //print out if there are any hazards nearby
{
	for (int i = 0; i < 3; i++) //check all three adjacent postions
	{
		if (adjacentPositions[hazards[5]][i] == hazards[2] || adjacentPositions[hazards[5]][i] == hazards[3]) //if pit is near
		{
			cout << " You feel a draft.";
		}
	}

	for (int i = 0; i < 3; i++) //check all three adjacent postions
	{
		if (adjacentPositions[hazards[5]][i] == hazards[0] || adjacentPositions[hazards[5]][i] == hazards[1]) //if batman in his batcave is near
		{
			cout << " You hear rustling of bat wings.";
		}
	}

	for (int i = 0; i < 3; i++) //check all three adjacent postions
	{
		if (adjacentPositions[hazards[5]][i] == hazards[4]) //if wumpus is near
		{
			cout << " You smell a stench.";
		}
	}

	cout << endl;
	cout << endl;
}

void changeHazards(int(&hazards)[7], int &counter) //reset the hazards
{
	cout << "(Remember arrow value of -1 means it is with the person.)" << endl;
	cout << "Enter the 7 room locations (1..20) for player, wumpus, bats1, bats2, pit1, pit2, and arrow:" << endl;
	cin >> hazards[5]; //person
	cin >> hazards[4]; //wumpus
	cin >> hazards[0]; //bats1
	cin >> hazards[1]; //bats2
	cin >> hazards[2]; //pit1
	cin >> hazards[3]; //pit2
	cin >> hazards[6]; //arrow
	counter = 1; //reset the counter back to one

	cout << endl;
}

void move(int(&adjacentPositions)[21][3], int(&hazards)[7], int &moveLocation, int &counter, bool &validMove)
{
	cin >> moveLocation; //get the location from user

	for (int i = 0; i < 3; i++)
	{
		if (adjacentPositions[hazards[5]][i] == moveLocation)
		{
			hazards[5] = moveLocation; //changes the value of location of person
			validMove = true; //to see if valid move can be made and tell the user if not
			counter++; //increase the count by 1

	  //checks if the person doesn't have arrow and is at the same location as the arrow
			if ((hazards[6] != -1) && (hazards[5] == hazards[6]))
			{
				hazards[6] = -1;
				cout << "Congratulations, you found the arrow and can once again shoot." << endl;
			}
			break;
		}
	}

	if (validMove == false) //if the move is not adjacent
	{
		cout << "Invalid move.  Please retry." << endl;
	}
}

bool wumpusExperienceAlive(int(&adjacentPositions)[21][3], int(&hazards)[7])
{
	if (hazards[5] == hazards[4]) //if person is same location as wumpus
	{
		if ((hazards[4] == hazards[5]) && (hazards[4] % 2 == 0)) //if the room is even where the wumpus and person meets
		{
			cout << "You briefly feel a slimy tentacled arm as your neck is snapped." << endl;
			cout << "It is over." << endl;
			return false; //break out of the while loop after the person is dead
		}

		if ((hazards[4] == hazards[5]) && (hazards[5] % 2 == 1)) //if the room is odd where the wumpus and person meets
		{
			int low = 21;
			cout << "You hear a slithering sound, as the Wumpus slips away." << endl;
			cout << "Whew, that was close!" << endl;

			for (int i = 0; i < 3; i++)
			{
				if (hazards[4] > adjacentPositions[hazards[4]][i]) //compare rooms to see which one is the lowest
				{
					low = adjacentPositions[hazards[4]][i];
				}
			}

			hazards[4] = low; //wumpus goes to the lowest numbered room
		}
	}

	return true;
}

bool pitExperienceAlive(int(&hazards)[7])
{
	if (hazards[5] == hazards[2] || hazards[5] == hazards[3]) //if person is at one of the two pits then the person dies
	{
		cout << "Aaaaaaaaahhhhhh.... " << endl;
		cout << "     You fall into a pit and die." << endl;
		return false;
	}
	return true;
}

struct Node {
	int data[7]; //bat1, bat2, pit1, pit2, wumpus, person, arrow
	Node *pNext;
};

void prepend(Node *&pHead, int hazards[7])
{
	Node *pTemp = new Node; //make a new Node
	for (int i = 0; i < 7; i++)
	{
		pTemp->data[i] = hazards[i]; //store data in the Node
	}
	pTemp->pNext = pHead; //point to where pHead is pointing to
	pHead = pTemp; //then make the pHead point the new Node
}

void undo(Node *&pHead, int (&hazards)[7], int &counter)
{
	pHead = pHead->pNext; //now the pHead points to the previous Node
	for (int i = 0; i < 7; i++)
	{
		hazards[i] = pHead->data[i]; //make the new data what the header is point to now which is the previous Node
	}

	counter--;
	//Node *pTemp = new Node; // make a new Node where the new information will be stored waiting to be copied over
	
}

//--------------------------------------------------------------------------------
int main()
{
	Node *pHead = NULL;
	Node *pTemp = new Node;

	// Seed the random number generator.  Change seed to time(0) to change output each time.
	srand(time(0));
	//srand(1);   // Use this version in what you turn in

	static int adjacentPositions[21][3]; //all the adjacent postition that branch out from their locations
  //index 0 should be null and index 1 is the location 1
	adjacentPositions[1][0] = 2; adjacentPositions[1][1] = 5; adjacentPositions[1][2] = 8; //location 1
	adjacentPositions[2][0] = 1; adjacentPositions[2][1] = 3; adjacentPositions[2][2] = 10; //location 2
	adjacentPositions[3][0] = 2; adjacentPositions[3][1] = 4; adjacentPositions[3][2] = 12; //location 3
	adjacentPositions[4][0] = 3; adjacentPositions[4][1] = 5; adjacentPositions[4][2] = 14; //location 4
	adjacentPositions[5][0] = 1; adjacentPositions[5][1] = 4; adjacentPositions[5][2] = 6; //location 5
	adjacentPositions[6][0] = 5; adjacentPositions[6][1] = 7; adjacentPositions[6][2] = 15; //location 6
	adjacentPositions[7][0] = 6; adjacentPositions[7][1] = 8; adjacentPositions[7][2] = 17; //location 7
	adjacentPositions[8][0] = 1; adjacentPositions[8][1] = 7; adjacentPositions[8][2] = 9; //location 8
	adjacentPositions[9][0] = 8; adjacentPositions[9][1] = 10; adjacentPositions[9][2] = 18; //location 9
	adjacentPositions[10][0] = 2; adjacentPositions[10][1] = 9; adjacentPositions[10][2] = 11; //location 10
	adjacentPositions[11][0] = 10; adjacentPositions[11][1] = 12; adjacentPositions[11][2] = 19; //location 11
	adjacentPositions[12][0] = 3; adjacentPositions[12][1] = 11; adjacentPositions[12][2] = 13; //location 12
	adjacentPositions[13][0] = 12; adjacentPositions[13][1] = 14; adjacentPositions[13][2] = 20; //location 13
	adjacentPositions[14][0] = 4; adjacentPositions[14][1] = 13; adjacentPositions[14][2] = 15; //location 14
	adjacentPositions[15][0] = 6; adjacentPositions[15][1] = 14; adjacentPositions[15][2] = 16; //location 15
	adjacentPositions[16][0] = 15; adjacentPositions[16][1] = 17; adjacentPositions[16][2] = 20; //location 16
	adjacentPositions[17][0] = 7; adjacentPositions[17][1] = 16; adjacentPositions[17][2] = 18; //location 17
	adjacentPositions[18][0] = 9; adjacentPositions[18][1] = 17; adjacentPositions[18][2] = 19; //location 18
	adjacentPositions[19][0] = 11; adjacentPositions[19][1] = 18; adjacentPositions[19][2] = 20; //location 19
	adjacentPositions[20][0] = 13; adjacentPositions[20][1] = 16; adjacentPositions[20][2] = 19; //location 20


	int hazards[7]; //(0)bats1, (1)bats2, (2)pit1, (3)pit2, (4)Wumpus, (5)person, (6)arrow


	//you only want first 6 numbers randomized becasue arrow will be -1 since player starts with it
	for (int i = 0; i < 6; i++)
	{
		hazards[i] = rand() % 20 + 1;
	}
	hazards[0] = 3; //testing purpose
	hazards[1] = 5; //testing purpose
	hazards[2] = 11; //testing purpose
	hazards[3] = 7; //testing purpose
	hazards[4] = 14; //testing purpose
	hazards[5] = 13; //setting person position manually rand not working proparly
	hazards[6] = -1;

	pTemp->pNext = NULL; //make a Node and start it off with a NULL pointer
	pHead = pTemp;

	string userInput = ""; //gets user input
	int counter = 1; //keeps track of how many times the code has run
	int moveLocation = -1;
	bool validMove = false;

	while (userInput != "x" && userInput != "X") //keep running until player enters x
	{
		cout << "You are in room " << hazards[5] << "."; //print what room the person is in

		checkForHazard(adjacentPositions, hazards); //print out if there are any hazards nearby

		cout << counter << ". Enter your move (or 'D' for directions): ";
		cin >> userInput;
		cout << endl;

		if (userInput == "u" || userInput == "U")
		{
			if (pHead->pNext == NULL)
			{
				cout << "Sorry, you can't undo past the beginning of the game.  Please retry." << endl;
			}

			else
			{
				undo(pHead, hazards, counter);
			}
		}

		if (userInput == "p" || userInput == "P")
		{
			displayCave();
		}

		if (userInput == "d" || userInput == "D")
		{
			displayInstructions();
		}

		if (userInput == "r" || userInput == "R") //take this branch if r is entered
		{
			changeHazards(hazards, counter); //reset the hazards
			prepend(pHead, hazards); // add a node in the front of the node train
		}


		if (userInput == "m" || userInput == "M") //take this branch if m is entered
		{
			move(adjacentPositions, hazards, moveLocation, counter, validMove);

			if (wumpusExperienceAlive(adjacentPositions, hazards) == false)
			{
				break;
			}

			if (pitExperienceAlive(hazards) == false)
			{
				break;
			}

			if (hazards[5] == hazards[0] || hazards[5] == hazards[1]) //if person is at one of the same rooms as the bats
			{
				int randomRoom = hazards[5];
				while (randomRoom == hazards[5])
				{
					randomRoom = rand() % 20 + 1;
				}
				hazards[5] = 10;

				cout << "Woah... you're flying!" << endl;
				cout << "You've just been transported by bats to room " << hazards[5] << endl;

				int tempRoom = hazards[0];
				while (tempRoom == hazards[5])
				{
					tempRoom = rand() % 20 + 1;
				}
				hazards[0] = 2;
			}

			if (pitExperienceAlive(hazards) == false) //check again to see if bats dropped the player in a pit
			{
				break;
			}

			prepend(pHead, hazards); // add a node in the front of the node train
		}

		if (userInput == "c" || userInput == "C") //take this branch if c is entered
		{
			cout << "Cheating! Game elements are in the following rooms:" << endl;
			cout << "Player Wumpus Bats1 Bats2 Pit1 Pit2 Arrow" << endl;
			cout << "  " << hazards[5] << "      " << hazards[4] << "      " << hazards[0] << "     " << hazards[1] << "   " << hazards[2] << "    " << hazards[3] << "    " << hazards[6] << endl;
		}

		//shooting the arrow
		if (userInput == "s" || userInput == "S") //take the branch if c is entered
		{
			if (hazards[6] == -1)
			{
				counter++; //increase the count of moves
				cout << "Enter the number of rooms (1..3) into which you want to shoot, followed by the rooms themselves: " << endl;
				int arrowDistance = 0;
				int targetLocation = -1;
				bool targetLocationReached = false;
				bool wumpusIsDead = false; //status of wumpus
				bool personIsDead = false; //status of person

				hazards[6] = hazards[5]; //the location of person turns into location of arrow

				cin >> arrowDistance; //how far the arrow needs to go

				for (int i = 0; i < arrowDistance; i++) //runs how many times the distance is
				{
					cin >> targetLocation;
					for (int j = 0; j < 3; j++) //checks all three postion if it is the next target location of arrow
					{
						if (adjacentPositions[hazards[6]][j] == targetLocation)
						{
							hazards[6] = targetLocation;
							targetLocationReached = true;
							break;
						}

						else
						{
							targetLocationReached = false;
						}
					}

					if (targetLocation == hazards[5]) //if the arrow you are shooting is coming back to you
					{
						personIsDead = true;
						cout << "	You just shot yourself. " << endl;
						cout << "Maybe Darwin was right.  You're dead." << endl;
						break;
					}

					if (hazards[6] == hazards[4])
					{
						wumpusIsDead = true;
						cout << "Wumpus has just been pierced by your deadly arrow!" << endl;
						cout << "Congratulations on your victory, you awesome hunter you." << endl;
					}

					if (targetLocationReached == false) //if the target location is not adjacent to the room the person is in
					{
						cout << "Room " << targetLocation << " is not adjacent.  Arrow ricochets..." << endl;
						int lowest = 21;
						for (int j = 0; j < 3; j++)
						{
							if (adjacentPositions[hazards[6]][j] < lowest) //could be problem here
							{
								lowest = adjacentPositions[hazards[6]][j];
							}
						}
						hazards[6] = lowest; //arrow goes to the lowest number room

						if (hazards[6] == hazards[5]) //if the arrow randomly hits the person
						{
							cout << "You just shot yourself, and are dying." << endl;
							cout << "It didn't take long, you're dead.	" << endl;
							personIsDead = true;
						}

						if (hazards[6] == hazards[4]) //if the arrow randomly hits the wumpus
						{
							wumpusIsDead = true;
							cout << "Your arrow ricochet killed the Wumpus, you lucky dog!" << endl;
							cout << "Accidental victory, but still you win!" << endl;
						}

					}
				}

				if (wumpusIsDead == true)
				{
					break;
				}

				if (personIsDead == true)
				{
					break;
				}

				//wumpus is not killed after the arrow is shot so the wumpus moves
				int lowest = 21;
				for (int i = 0; i < 3; i++)
				{
					if (adjacentPositions[hazards[4]][i] < lowest)
					{
						lowest = adjacentPositions[hazards[4]][i];
					}
				}
				hazards[4] = lowest; //arrow goes to the lowest number room
			}

			else
			{
				cout << "Sorry, you can't shoot an arrow you don't have.  Go find it." << endl;
				counter++;
			}
		}
	}

	cout << "\nExiting Program ..." << endl;
	return 0;
}//end main()
