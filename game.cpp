#include <iostream>
#include <stdlib.h>
#include <vector>

char gridChar(signed int i)
{
	switch (i) {
	case -1:
		return 'X';
		break;
	case 0:
		return ' ';
		break;
	case 1:
		return 'O';
		break;
	default:
		return 'N';
		break;
	}
}
void draw(std::vector<char>& b) {

	// Draw the board.
	std::cout << " " << gridChar(b[0]) << " | " << gridChar(b[1]) << " | " << gridChar(b[2]) << std::endl;
	std::cout << "---+---+---\n";
	std::cout << " " << gridChar(b[3]) << " | " << gridChar(b[4]) << " | " << gridChar(b[5]) << std::endl;
	std::cout << "---+---+---\n";
	std::cout << " " << gridChar(b[6]) << " | " << gridChar(b[7]) << " | " << gridChar(b[8]) << std::endl;
}

int win(const std::vector<char>& board)
{
	// Determines if a player has won, returns 0 otherwise.
	std::vector<std::vector<int>> wins = { { 0, 1, 2 }, { 3, 4, 5 }, { 6, 7, 8 }, { 0, 3, 6 }, { 1, 4, 7 }, { 2, 5, 8 }, { 0, 4, 8 }, { 2, 4, 6 } };
	// Variable 'wins' represent all possible victory combinations on the board.
	unsigned int i;
	for (i = 0; i < 8; ++i)
	{
		if (board[wins[i][0]] != 0 &&
			board[wins[i][0]] == board[wins[i][1]] &&
			board[wins[i][0]] == board[wins[i][2]])
			return board[wins[i][2]]; // Return the position which was the 'winning move'.
	}
	return 0;
}
int minimax(std::vector<char>& board, int player)
{
	// How is the position like for the player (their turn) on board?
	signed int winner = win(board);
	if (winner != 0) { return winner * player; }

	signed int move = -1;
	signed int score = -2; // Losing moves are preferred to no move.
	unsigned int i = 0;
	for (; i < 9; ++i)
	{
		// For all moves,
		if (board[i] == 0) // If legal
		{
			board[i] = player;// Try the move.
			signed int thisScore = -minimax(board, player * -1); // Recursive minimax()
			if (thisScore > score)// Do we have any gains? 
			{
				score = thisScore;
				move = i;
			} // Pick the move that's worst for the opponent.
			board[i] = 0; // Reset board after try.
		}
	}
	if (move == -1){ return 0; } // Only in use for second last move before draw.
	return score;
}
void moveComputerAI(std::vector<char> board)
{
	std::cout << "Computer's move." << std::endl;
	signed int move = -1; // Minimum value less than 0.
	signed int score = -2; // Corresponds to human player win as {0, 1, 2}.
	unsigned int i;
	for (i = 0; i < 9; ++i)
	{
		if (board[i] == 0)
		{
			board[i] = 1; // Test every available move on the board.
			unsigned int tempScore = -minimax(board, -1);
			board[i] = 0; // Validate the move.
			if (tempScore > score)
			{
				score = tempScore;
				move = i;
				// Optimal gains.
			}
		}
	}
	// Returns a score based on minimax tree at a given node.
	board[move] = 1;
}
void movePlayer(std::vector<char>& board)
{
	std::cout << "Your move." << std::endl;
	// Accept move from player within legal limits.
	int t = 0;
	std::cout << "Enter your move position from 1-9." << std::endl;
	scanf("%d", &t);
	signed int move = t - 1; // Compromise for 0 begin of array.
	while (move >= 9 || move < 0 || board[move] != 0)
	{
		std::cout << "Illegal entry. Re-enter." << std::endl;
		scanf("%d", &t);
		move = t - 1;
	}

	board[move] = -1;
	system("cls");
}
void initTicTacToe(void)
{
	std::vector<char> board({ 0, 0, 0, 0, 0, 0, 0, 0, 0 });

	// Computer squares are 1, player squares are -1.

	std::cout << "Welcome to tic-tac-toe game. You are pitted against computer AI." << std::endl;
	std::cout << "Computer: O, You: X\nPlay (1)st or (2)nd? \n";
	unsigned int player = 0;
	while ((scanf("%d", &player) > 0 && player != 1 && player != 2)) {
		std::cout << "Illegal entry. Re-enter." << std::endl;
	}
	unsigned int turn = 0;
	for (turn = 0; turn < 9 && win(board) == 0; ++turn)
	{
		if ((turn + player) % 2 == 0) {
			draw(board);
			moveComputerAI(board);
		}
		else
		{
			draw(board);
			movePlayer(board);
		}
	}
	switch (win(board))
	{
	case 0:
		std::cout << "A draw.\n";
		break;
	case 1:
		draw(board);
		std::cout << "You lose.\n";
		break;
	case -1:
		std::cout << "You win. Inconceivable!\n";
		break;
	}
}
int main()
{
	system("cls");
	initTicTacToe();
	std::cin.ignore();
}
