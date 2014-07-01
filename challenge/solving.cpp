#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

class Puzzle
{
    //Dimension
    int n;
    int** matrix;
    int rowHole, columnHole;
    int closeness;
    char originMovement;

    public:
    
    Puzzle(int n)
    {
        this->n = n;
	closeness = 0;
	originMovement = ' ';

        matrix = new int* [n];
	for(int i=0; i < n; i++)
	{
	    matrix[i] = new int[n];
	    for(int column = 1; column <= n; column++)
	    {
		scanf("%d", &(matrix[i][column]));
		if(matrix[i][column] == 0)
		{
	            rowHole = i;
		    columnHole = column;
		}
	    }
	}
    }

    Puzzle(const Puzzle& puzzle)
    {
        n = puzzle.n;
	rowHole = puzzle.rowHole;
	columnHole = puzzle.columnHole;
	closeness = puzzle.closeness;
	originMovement = puzzle.originMovement;

	matrix = new int*[n];

	for(int row = 0; row < n; row++)
	{
            matrix[row] = new int[n];
	    for(int column = 0; column < n; column++)
	    {
	        matrix[row][column] = puzzle.matrix[row][column];
	    }
	}
    }

    // Get the metric that tell how close is the Puzzle to the final configuration
    void calculateCloseness()
    {
	closeness = 0;

	for(int i=0; i < n; i++)
	{
	    for(int column = 1; column <= n; column++)
	    {
		if(column == n && i == (n-1))
		{
		    if(matrix[i][column] == 0)
		    {
		        closeness++;
		    }
		}
                else
		{
	            if(matrix[i][column] == i*n + column)
		    {
		        closeness++;
		    }
		}
	    }
	}
    }
    
    int getRowHole()
    {
        return rowHole;
    }
    
    void setRowHole(int rowHole)
    {
        this->rowHole = rowHole;
    }

    int getColumnHole()
    {
        return columnHole;
    }

    void setColumnHole(int columnHole)
    {
        this->columnHole = columnHole;
    }

    char getOriginMovement()
    {
        return originMovement;
    }

    void setOriginMovement(char originMovement)
    {
        this->originMovement = originMovement;
    }

    int getN()
    {
        return n;
    }
    int getTile(int row, int column)
    {
        return matrix[row][column];
    }

    void setTile(int row, int column, int content)
    {
        matrix[row][column] = content;
    }

    ~Puzzle()
    {
        for(int index = 0; index < n; index++)
	{
            delete matrix[index];
	}

	delete matrix;
    }
};

class Game
{
   Puzzle* currentPuzzle;
   vector<char> sequence; // sequence of moviments to get in the final configuration.

    public:
   // Initializes the game
   Game(int n)
   {
       currentPuzzle = new Puzzle(n);
   }

   vector<char> getSequenceMovements()
   {
       return sequence;
   }

   // Play one hop.
   void nextHop()
   {
       vector<Puzzle*> possibleNextConfigurations;

       // Discover next possible configurations
       // Try "U": up moviment with the hole
       if(currentPuzzle.getRowHole() > 0)
       {
           Puzzle *puzzle = new Puzzle(*currentPuzzle);
	   int tmp = puzzle->getTile(puzzle->getRowHole()-1, puzzle->getColumnHole())
           puzzle->setTile(puzzle->getRowHole()-1, puzzle->getColumnHole(), 0);
	   puzzle->setTile(puzzle->getRowHole(), puzzle->getColumnHole(), tmp);
	   puzzle->setRowHole(puzzle->getRowHole() - 1);
	   puzzle->calculateCloseness();
	   puzzle->setOriginMovement('U');
	   possibleNextConfigurations.push_back(puzzle);
       }

       // Try "D": down moviment with the hole
       if(currentPuzzle.getRowHole() < currentPuzzle.getN() - 1)
       {
           Puzzle *puzzle = new Puzzle(*currentPuzzle);
	   int tmp = puzzle->getTile(puzzle->getRowHole()+1, puzzle->getColumnHole())
           puzzle->setTile(puzzle->getRowHole()+1, puzzle->getColumnHole(), 0);
	   puzzle->setTile(puzzle->getRowHole(), puzzle->getColumnHole(), tmp);
	   puzzle->setRowHole(puzzle->getRowHole() + 1);
	   puzzle->calculateCloseness();
	   puzzle->setOriginMovement('D');
	   possibleNextConfigurations.push_back(puzzle);
       }

       // Try "L": left moviment with the hole
       if(currentPuzzle.getColumnHole() > 0)
       {
           Puzzle *puzzle = new Puzzle(*currentPuzzle);
	   int tmp = puzzle->getTile(puzzle->getRowHole(), puzzle->getColumnHole()-1)
           puzzle->setTile(puzzle->getRowHole(), puzzle->getColumnHole()-1, 0);
	   puzzle->setTile(puzzle->getRowHole(), puzzle->getColumnHole(), tmp);
	   puzzle->setColumnHole(puzzle->getColumnHole() - 1);
	   puzzle->calculateCloseness();
	   puzzle->setOriginMovement('L');
	   possibleNextConfigurations.push_back(puzzle);
       }

       // Try "R": right moviment with the hole
       if(currentPuzzle.getColumnHole() < currentPuzzle.getN() - 1)
       {
           Puzzle *puzzle = new Puzzle(*currentPuzzle);
	   int tmp = puzzle->getTile(puzzle->getRowHole(), puzzle->getColumnHole()+1)
           puzzle->setTile(puzzle->getRowHole(), puzzle->getColumnHole()+1, 0);
	   puzzle->setTile(puzzle->getRowHole(), puzzle->getColumnHole(), tmp);
	   puzzle->setColumnHole(puzzle->getColumnHole() + 1);
	   puzzle->calculateCloseness();
	   puzzle->setOriginMovement('R');
	   possibleNextConfigurations.push_back(puzzle);
       }
       
       struct puzzle_less_than
       {
           inline bool operator() (const Puzzle* puzzle1, const Puzzle* puzzle2)
	   {
               return (puzzle1->getCloseness() < puzzle2->getCloseness());
	   }
       };

       // Decide what moviment to do according to the closiness metric.
       sort(possibleNextConfigurations.begin(), possibleNextConfigurations.end(), puzzle_less_than());
       delete currentPuzzle;

       currentPuzzle = possibleNextConfigurations.pop_back();
       sequence.push_back(currentPuzzle->getOriginMovement());

       for(int index = 0; index < possibleNextConfigurations.size(); index++)
       {
           delete possibleNextConfigurations[index];
       }
   }

   void playPuzzle()
   {
       while(currentPuzzle->getCloseness() < currentPuzzle->getN() * currentPuzzle->getN())
       {
           nextHop();
       }
   }

   ~Game()
   {
       delete currentPuzzle;
   }

}


int main()
{
    int amountCases;
    scanf("%d", &amountCases);

    for(int index = 0; index < amountCases; index++)
    {
        int dimension;
	scanf("%d", &dimension);
	Game game(dimension);
	game.playPuzzle();

	for(vector<char>::iterator it = game.getSequenceMovements().begin(); it != game.getSequenceMovements().end(); it++)
	{
	    printf(*it);
	}
	printf("\n");

    }

    return 0;
}
