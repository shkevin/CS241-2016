/* ************************************
* Kevin Cox
*
* Takes in a Sudoku puzzle and attempts
* to solve.
*
************************************ */

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXCELLS 9	/*max number for a row or col*/

int isValid(int row, int col, int iterator);
int puzzleSolver(int row, int col, int iterator);
void printPuzzle();
int initialCheck(int row, int col, int iterator);
int solverHelper(int row, int col, int iterator);

int row, col, errorFlag, tempCount;
int puzzle[MAXCELLS][MAXCELLS];

int main()
{
	int c, count;
	c = row = col = count = tempCount = 0;

	while((c = getchar()) != EOF)
	{
		printf("%c", c);

		if (c == '\n')
		{	
            /*Checks for valid initial puzzle*/
            int i, j;
            for (i = 0; i < MAXCELLS; i++)
            {
                for(j = 0; j < MAXCELLS; j++)
                {
                    if (puzzle[i][j] != -2)
                    {
                        if (!initialCheck(i, j, puzzle[i][j])) errorFlag = 1;
                    }
                }
            }
            if ((errorFlag) || (count < 81)) /*adjusts for error*/
			{   
				printf("Error\n");
				errorFlag = 0;
			}
            else                            /*otherwise solve puzzle*/
			{
				if (puzzleSolver(0,0,1)) printPuzzle();				
                else printf("No solution\n");
                printf("%d\n", tempCount);
			}
            tempCount = 0;
			count = row = col = 0;
			printf("\n");
		}
		else
		{
			count++;

            /*checks if there is an error case*/
			if (((!isdigit(c) && c != '.') && (c != '\n')) || ((count > 81)))
			{
				errorFlag = 1;
				continue;
			}
            /*place c into array here and increment col*/
            puzzle[row][col] = c - '0';
			col++;

            /*if the array has reached max col, reset to zero and increment row*/
			if(col >= 9)
			{
				row++;
				col = 0;
			}
		}
	}
	return 0;
}

/*
    prints out the puzzle after processing
*/
void printPuzzle()
{
	int i, j;
	for(i = 0; i < MAXCELLS; i++)
	{
		for(j = 0; j < MAXCELLS; j++)
		{
           printf("%d", puzzle[i][j]); /*print integer*/     
		}
	}
	printf("\n");
}

/*
   checks the rucursive call's validity to place number
*/
int isValid(int row, int col, int iterator)
{
	int rowStart = (row/3) * 3;
    int colStart = (col/3) * 3;
    int i;

    /*
    need to check if the number isn't in the sector, and col/row
    */
    for (i = 0; i < MAXCELLS; i++)
    {
        /*checks if same num in row*/
        if ((i != col) && (puzzle[row][i] == iterator)) return 0; 
        /*checks if same num in col*/
        if ((i != row) && (puzzle[i][col] == iterator)) return 0; 
        /*checks remaining*/
        if(puzzle[rowStart + (i%3)][colStart + (i/3)] == iterator) return 0; 
    }
    return 1;
}

/*
    recursive call. Checks every number for every row/col until solved
*/
int puzzleSolver(int row, int col, int iterator)
{
	 if (row > 8)
     {
        return 1;
     }
     if (puzzle[row][col] != -2)
     {
        if(solverHelper(row, col, iterator)) return 1;
        return 0;
     }

     /*If initial checks fail, find a number that works*/
     for (iterator = 1; iterator < 10; iterator++)
     {	
        if (isValid(row, col, iterator))
        {
            tempCount++;
            puzzle[row][col] = iterator;

            if(solverHelper(row, col, iterator)) return 1;
        }
        puzzle[row][col] = -2;
    }
    return 0;
}

/*checks for an invalid starting board*/
int initialCheck(int row, int col, int iterator)
{
    int i, rowAbove, rowBelow, colLeft, colRight;
    int areaRow, areaCol;
    rowAbove = (row+2) % 3; /*one up*/
    rowBelow = (row+4) % 3; /*one below*/
    colLeft = (col+2) % 3;  /*one left*/
    colRight = (col+4) % 3; /*one right*/
    areaRow = 3*(row/3);    /*gets 3x3 grid for the row*/
    areaCol = 3*(col/3);    /*gets 3x3 grid for the col*/

    /*
    need to check if the number isn't in the sector, and col/row
    */
    for (i = 0; i < MAXCELLS; i++)
    {
        if ((i != col) && (puzzle[row][i] == iterator)) return 0; /*checks if same num in col*/
        if ((i != row) && (puzzle[i][col] == iterator)) return 0; /*checks if same num in row*/
    }
    if (puzzle[rowAbove+areaRow][colLeft+areaCol] == iterator) return 0;    /*upper diagonal left*/
    if (puzzle[rowBelow+areaRow][colLeft+areaCol] == iterator) return 0;    /*lower diagonal left*/
    if (puzzle[rowAbove+areaRow][colRight+areaCol] == iterator) return 0;   /*upper diagonal right*/
    if (puzzle[rowBelow+areaRow][colRight+areaCol] == iterator) return 0;   /*lower diagonal right*/

    return 1;
}

/*
  Extracted logic to clean up the recursive calls.
  checks the appropriate place to recurse.   
*/
int solverHelper(int row, int col, int iterator)
{
    if (col < 8)
    {
        if (puzzleSolver(row, col+1, iterator)) return 1;
    }
    else 
    {
        if (puzzleSolver(row+1, 0, iterator)) return 1;
    }
    return 0;
}
