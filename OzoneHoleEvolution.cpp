//===============================================================================
// Written by Andrew Byerly
// February 29th, 2024
// OzoneHoleEvolution.cpp
// This program is intended to read stdin from a .txt file, the data in each test
// file should follow the following rules: first specify the number of holes,
// then specify the x followed by the y location of each aforementioned hole.
// Each file should  have 2 of these data sets, the first one being the original
// locations of the  ozone holes, and the second being the locations of where the
// ozone holes are predicted to be after the simulation (in this case the 
// simulation lasts 24 months, but the duration can be modified via the const
// int MONTHS). After reading in the two sets of data and storing them in their
// own respective 2D arrays, the program will print out the original location of
// the ozone holes, the location of the ozone holes for the prediction data, and
// finally the location of the ozone holes after the simulation. All of which are
// represented in the form of a 15x15 grid. Additionally, the program will print
// out whether or not the prediction locations were indeed accurate predictors of
// where the ozone holes are located after the simulation.
// Note: Throughout the program I will reference arrays, 2D arrays, and grids,
// each of which are interchangable. I just use whichever one I feel fits the 
// context the best, but in the end they're all referencing the same thing.
//===============================================================================

#include <iostream>
using namespace std;

// initialize and store values in each of the constants that we will be using throughout the program.
const int ROWS = 15;
const int COLS = 15;
const int EXPAND = 2;
const int HOLE = 1;
const int NOHOLE = 0;
const int MONTHS = 24;
const int ROWNUMS[] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int COLNUMS[] = {-1, 0, 1, -1, 1, -1, 0, 1};
const int NUMADJACENTCOORDS = 8;

// create function declarations with parameters for each of the functions that will be used throughout the program.
void createBuffer(int grid[][COLS+EXPAND]);
void readInGrid(int grid[][COLS+EXPAND]);
void printOutGrid(int grid[][COLS+EXPAND]);
void copy2DArray(int original[][COLS+EXPAND], int copy[][COLS+EXPAND]);
void ozoneSimulation(int grid[][COLS+EXPAND], int nextGrid[][COLS+EXPAND]);
bool equalGridChecker(int gridA[][COLS+EXPAND], int gridB[][COLS+EXPAND]);
int adjacentHoleCounter(int grid[][COLS+EXPAND], int row, int col);

//===============================================================================
// main()
// This is the main function and it will act as the backbone of the program.
// In this function we will create each of the 2D arrays needed in the
// computation of the program as well as call the functions to create a buffer,
// read in the locations of the holes, print out the 2D arrays in the form of
// 15x15 grids, and carry out the overall simulation. Arguably the most important
// part of the main function comes at the end where it evaluates the 
// 'equalGridChecker' function and prints out whether or not the prediction
// locations satisfy the simulated conditions.
//===============================================================================
int main() {

    // create each of the 2D arrays to be used throughout 'main' and the entire program.
    int simGrid[ROWS+EXPAND][COLS+EXPAND];
    int prevSimGrid[ROWS+EXPAND][COLS+EXPAND];
    int oGrid[ROWS+EXPAND][COLS+EXPAND];
    int pGrid[ROWS+EXPAND][COLS+EXPAND];

    // create the buffer grid (17x17 2D array of 0's) for both oGrid and pGrid.
    createBuffer(oGrid);
    createBuffer(pGrid);

    // read in and store the locations of the original ozone holes and the predicted locations
    // of the ozone holes after the simulation in their respective arrays/grids.
    readInGrid(oGrid);
    readInGrid(pGrid);

    // copy the data from the original array and store it in array that is to be simulated.
    copy2DArray(oGrid, simGrid);
    
    // print out the oGrid 2D array in the form of a 15x15 grid.
    cout << "Original Grid:" << endl;
    printOutGrid(oGrid);
    cout << endl;

    // print out the pGrid 2D array in the form of a 15x15 grid.
    cout << "Prediction Grid:" << endl;
    printOutGrid(pGrid);
    cout << endl;

    // for each month to be simulated (determined by MONTHS const, in this case 24), copy the 
    // current locations grid data to the previous locations grid data, then simulate the changing
    // ozone holes, storing their new locations in the current sim to be copied over next iteration.
    for (int i = 0; i < MONTHS; i++) {
        copy2DArray(simGrid, prevSimGrid);
        ozoneSimulation(prevSimGrid, simGrid);
    }

    // print out the fully simulated simGrid 2D array in the form of a 15x15 grid.
    cout << "Simulated Grid After " << MONTHS << " Months:" << endl;
    printOutGrid(simGrid);

    // if the fully simulated grid is equal to the prediction grid then print out that it was
    // a valid prediction, invalid if otherwise.
    if (equalGridChecker(pGrid, simGrid)) {
        cout << "The input prediction was valid!" << endl;
    } else {
        cout << "The input prediction was invalid!" << endl;
    }

    return 0;
}

//==================================================================================
// createBuffer()
// This function will take a 2D array of integers 'grid' and store the value of
// 'NOHOLE' in each of it's grid spots (in the case of this program it's a 15x15
// grid by default, but the buffer makes it 17x17 so it's easier to check). 
// Parameters:
//    A 2D array of integers 'grid' that is to be filled with 'NOHOLE'.
// Return Value:
//    None, this function is of void return type, does not need to return anything
//    because it changes an array which is passed by reference by default.
//==================================================================================
void createBuffer(int grid[][COLS+EXPAND]) {

    // iterates over each of the expanded rows and columns, storing 'NOHOLE' in each.
    for (int i = 0; i < ROWS+EXPAND; i++) {
        for (int j = 0; j < COLS+EXPAND; j++) {
            grid[i][j] = NOHOLE;
        }
    }

}

//==================================================================================
// readInGrid()
// This function will take a 2D array of integers 'grid' and store the value of
// 'HOLE' in each of the grid spots that the stdin from the .txt file specifies is
// a hole (in the case of this program it's a 15x15 grid by default, but the buffer
// makes it 17x17 so we must add one to the row and col positison to ensure the hole
// is properly placed). 
// Parameters:
//    A 2D array of integers 'grid' that is to be stored with the 'HOLE' locations.
// Return Value:
//    None, this function is of void return type, does not need to return anything
//    because it changes an array which is passed by reference by default.
//==================================================================================
void readInGrid(int grid[][COLS+EXPAND]) {

    // creates three separate integer values to store the stdin from the .txt file.
    int numHoles;
    int holeRow;
    int holeCol;

    // read in and store the number of holes.
    cin >> numHoles;

    // iterate for each hole, storing the value of 'Hole' in each specified location.
    for (int i = 0; i < numHoles; i++) {
        cin >> holeRow;
        cin >> holeCol;

        grid[holeRow+1][holeCol+1] = HOLE;
    }

}

//==================================================================================
// printOutGrid()
// This function will take a 2D array of integers 'grid' and print out the array in
// the form of a 15x15 grid (in the case of this program it's a 15x15 grid by
// default, but the buffer makes it 17x17 so we must start iterating at row and col
// 1 to ensure that only the non-buffer grid is displayed). 
// Parameters:
//    A 2D array of integers 'grid' that is to be printed.
// Return Value:
//    None, this function is of void return type, does not need to return anything
//    because it changes an array which is passed by reference by default.
//==================================================================================
void printOutGrid(int grid[][COLS+EXPAND]) {

    // iterate through each row and column, starting at one and going up to the number
    // of rows and cols inclusive. Print out the value of each grid spot followed by a
    // space and returning line when the row ends.
    for (int i = 1; i <= ROWS; i++) {
        for (int j = 1; j <= COLS; j++) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }

}

//==================================================================================
// copy2DArray()
// This function will take 2 2D arrays of integers 'original' and 'copy' storing the
// exact values of the 'original' array in the 'copy' array (we do not need to make
// any adjustments for the buffer portion of the grid as we are copying the entire
// grid, not the mention the buffer will always contain 'NOHOLE').
// Parameters:
//    A 2D array of integers 'original' to represent the array to be copied.
//    A 2D array of integers 'copy' to represent the array to be copied to.
// Return Value:
//    None, this function is of void return type, does not need to return anything
//    because it changes an array which is passed by reference by default.
//==================================================================================
void copy2DArray(int original[][COLS+EXPAND], int copy[][COLS+EXPAND]) {

    // iterate through each row and column, storing the exact value of the 'original'
    // array in the corresponding 'copy' array location.
    for (int i = 0; i < ROWS+EXPAND; i++) {
        for (int j = 0; j < COLS+EXPAND; j++) {
            copy[i][j] = original[i][j];
        }
    }

}

//==================================================================================
// copy2DArray()
// This function will take 2 2D arrays of integers 'curGrid' and 'nextGrid', it will
// act as the primary focus of the program as it will examine the current month grid
// and determine the value of the value of each location in the next month grid
// (curGrid -> nextGrid). I will explain the computation in the in-line comments.
// Parameters:
//    A 2D array of integers 'curGrid' to represent the array of the current month.
//    A 2D array of integers 'copy' to represent the array of the next month.
// Return Value:
//    None, this function is of void return type, does not need to return anything
//    because it changes an array which is passed by reference by default.
//==================================================================================
void ozoneSimulation(int curGrid[][COLS+EXPAND], int nextGrid[][COLS+EXPAND]) {

    // iterate over each row and column in the grids (we start at one as we do not want to mess with the buffer values).
    for (int i = 1; i <= ROWS; i++) {
        for (int j = 1; j <= COLS; j++) {
            // Persists: The hole persists into the next month if it has two or three adjacent ozone holes in the current month.
            if (curGrid[i][j] == HOLE && adjacentHoleCounter(curGrid, i, j) == 2 || adjacentHoleCounter(curGrid, i, j) == 3) {nextGrid[i][j] = HOLE;}
            // Growth: A new hole will appear in a cell in the next month if in the current month the cell does not host an ozone hole and it has exactly three adjacent ozone holes in the current month.
            if (curGrid[i][j] == NOHOLE && adjacentHoleCounter(curGrid, i, j) == 3) {nextGrid[i][j] = HOLE;}
            // Disappearance: An ozone hole disappears starting in the next month if in the current month it has only 1 or 0 adjacent ozone holes in the current month.
            if (curGrid[i][j] == HOLE && adjacentHoleCounter(curGrid, i, j) == 1 || adjacentHoleCounter(curGrid, i, j) == 0) {nextGrid[i][j] = NOHOLE;}
            // Disappearance: An ozone hole will also disappear starting in the next month if in the current month it has 4 or more adjacent ozone holes.
            if (curGrid[i][j] == HOLE && adjacentHoleCounter(curGrid, i, j) >= 4) {nextGrid[i][j] = NOHOLE;}
        }
    }

}

//==================================================================================
// equalGridChecker()
// This function will take 2 2D arrays of integers 'gridA' and 'gridB', it will
// evaluate to true if the two grids are exactly equal to each other and false if
// they have even one value different.
// Note: I only iterate through the 15x15 values, but it would also work iterating
// through the 17x17 values as all the buffer values are the same. I just chose to
// iterate through the 15x15 values for the sake of runtime.
// Parameters:
//    A 2D array of integers 'gridA' to represent the first array to be compared.
//    A 2D array of integers 'gridB' to represent the second array to be compared.
// Return Value:
//    This function will either return true if the two grids are equal to each other
//    or false if they aren't exactly equal to each other.
//==================================================================================
bool equalGridChecker(int gridA[][COLS+EXPAND], int gridB[][COLS+EXPAND]) {

    // start iteration at 1 and start by saying the grids are equal by default.
    bool equal = true;
    int rowCount = 1;
    int colCount = 1;

    // while the grids are equal to each other, iterate through each 15x15 value and
    // compare them, setting equal to false if they aren't the same.
    while(rowCount <= ROWS && equal) {
        while(colCount <= COLS && equal) {
            if (gridA[rowCount][colCount] != gridB[rowCount][colCount]) {equal = false;}
            colCount++;
        }
        rowCount++;
    }

    // return if the grids are equal or not.
    return equal;
}

//==================================================================================
// adjacentHoleCounter()
// This function will take a 2D array of integers 'grid' as well as two integers,
// row and col that will specify the specific row and col we are examining. We will
// then iterate through each possible set of coordinates that are adjacent to the
// value at the given row and col. If the adjacent coordinate is a 'HOLE' then we
// increment count by 1, returning the count after the iteration.
// Parameters:
//    A 2D array of integers 'grid' that contains the values to be checked.
//    An integer value 'row' that specifies the row of the value to be checked.
//    An integer value 'col' that specifies the col of the value to be checked
// Return Value:
//    This function will return an integer value that represents the number of
//    adjacent values to the given value at (row, col) that have the value 'HOLE'.
//==================================================================================
int adjacentHoleCounter(int grid[][COLS+EXPAND], int row, int col) {

    // start by initializing the count and setting it to 0.
    int count = 0;

    // iterate through each possible comibation of adjacent coordinates, checking if
    // each combination has a hole relative to the value being checked at (row, col).
    for(int i = 0; i < NUMADJACENTCOORDS; i++) {
        if (grid[row+ROWNUMS[i]][col+COLNUMS[i]] == HOLE) {count++;}
    }

    // return the number of adjacent holes.
    return count;
}