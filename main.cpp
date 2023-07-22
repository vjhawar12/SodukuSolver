/* 
Vedant Jhawar
This program asks users for a soduku puzzle and solves it for them. 
It stores the puzzle in a text file and this puzzle can be viewed later on. 
Main.cpp
*/

// importing header files
#include <iostream>
#include <fstream> 
#include <unistd.h>
#include <vector>

#define CANNOT_VIEW 505

// the array of possible values to be entered
const int values[] = {1, 2, 3, 4, 5, 6, 7, 8, 9}; 
// the size of each row and column
const int N = 9;
// the log file name
const std::string logFileName = "log.txt";

// bool method to check if a particular number can be entered in a particular subgrid
bool isSubgridSafe(int board[N][N], int x1, int x2, int y1, int y2, int row, int col, int val) {
  // looping through the subgrid
  for (int i = x1; i < x2; i++) {
    for (int j = y1; j < y2; j++) {
      // if that number has already been entered return false
      if (i != row && col != j && board[i][j] == val) {
        return false; 
      }
    }
  }
  // else this is safe
  return true; 
}

// bool method to check if a partiulcar number can be entered in a particular square
bool isSafe(int board[N][N], int row, int col, int val) {
  // if the row or column is invalid return false
  if (row < 0 || col < 0 || row >= N || col >= N) {
    return false; 
  }
  // loop through the row/column
  for (int i = 0; i < N; i++) {
    // check if that number has already been entered
    if (i != col && board[row][i] == val) {
      return false; 
    }
    // check if that number has already been entered
    if (i != row && board[i][col] == val) {
      return false; 
    }
  }
  // checking first subgrid
  if (row <= 2 && row >= 0 && col <= 2 && col >= 0) {
    if (!isSubgridSafe(board, 0, 2, 0, 2, row, col, val)) {
      return false; 
    }
  }
  // checking second subgrid
  if (row <= 2 && row >= 0 && col <= 5 && col >= 3) {
    if (!isSubgridSafe(board, 0, 2, 3, 5, row, col, val)) {
      return false; 
    }
  }
  // checking third subgrid
  if (row <= 2 && row >= 0 && col <= 8 && col >= 6) {
    if (!isSubgridSafe(board, 0, 2, 6, 8, row, col, val)) {
      return false; 
    }
  }
  // checking fourth subgrid
   if (row <= 5 && row >= 3 && col <= 2 && col >= 0) {
    if (!isSubgridSafe(board, 3, 5, 0, 2, row, col, val)) {
      return false; 
    }
  }
  // checking fifth subgrid
  if (row <= 5 && row >= 3 && col <= 5 && col >= 3) {
    if (!isSubgridSafe(board, 3, 5, 3, 5, row, col, val)) {
      return false; 
    }
  }
  // checking sixth subgrid
  if (row <= 5 && row >= 3 && col <= 8 && col >= 6) {
    if (!isSubgridSafe(board, 3, 5, 6, 8, row, col, val)) {
      return false; 
    }
  }
  // checking sevents subgrid
  if (row <= 8 && row >= 6 && col <= 2 && col >= 0) {
    if (!isSubgridSafe(board, 6, 8, 0, 2, row, col, val)) {
      return false; 
    }
  }
  // checking eighth subgrid
  if (row <= 8 && row >= 6 && col <= 5 && col >= 3) {
    if (!isSubgridSafe(board, 6, 8, 3, 5, row, col, val)) {
      return false; 
    }
  }
  // checking ninth subgrid
  if (row <= 8 && row >= 6 && col <= 8 && col >= 6) {
    if (!isSubgridSafe(board, 6, 8, 6, 8, row, col, val)) {
      return false; 
    }
  }
  // if it deosn't fail any of the above conditions its safe
  return true;
}

// bool helper function to recursively solve a soduku using backtracking
bool solve(int board[N][N], int row, int col) {
  // if max row has been reached then return true - board is solved
  if (row == N) {
    return true;
  }
  // if max col has been reached then move to the next row
  if (col == N) {
    if (solve(board, row + 1, 0)) {
      return true;
    }
  }
  // if empty square found try to solve
  if (board[row][col] == 0) {
    // loop and solve
    for (int j = 0; j < N; j++) {
      // check if square safe
      if (isSafe(board, row, col, values[j])) {
        // place value and continue solving in this direction
        board[row][col] = values[j]; 
        if (solve(board, row, col + 1)) {
          // board solved
          return true;
        }
        // backtrack since this soluiton doesn't work
        board[row][col] = 0; 
      }
    }
    return false; 
  }
  // recursively solve
  if (solve(board, row, col + 1)) {
    return true;
  }
  // board not solved
  return false; 
}

// bool  function to recursively solve a soduku using backtracking by calling solve function
void solveBoard(int board[N][N], std::string fileName) {
  // if board can be solved add it to file
  if (solve(board, 0, 0)) {
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        // writing to file
        std::cout << board[i][j] << " "; 
      }
      std::cout << "\n"; 
    }
  }  
}

// method to add a board to file
void addBoardToFile(int board[N][N], std::string fileName, bool append) {
  // creating file object
  std::ofstream file; 
  // if on append mode open with append flag
  if (append) {
    file.open(fileName, std::ios_base::app); 
  } else { // if on write mode open with default write flag
    file.open(fileName);      
  }
  // write to file
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      file << board[i][j] << " ";
    }
    file << "\n"; 
  }
  file << "\n"; 
  // close file once done
  file.close();
}

// method to bubble sort files alphabetically for ease of use
std::vector<std::string> bubblesort(std::vector<std::string> boardNames) {
  // loop through boards with nested for loop for bubble sort
  for (int i = 0; i < boardNames.size(); i++) {
    for (int j = 0; j < boardNames.size(); j++) {
      if (i != j && j < i) {
        // swapping board order based on alphabetically
        std::string temp = boardNames[i];
        boardNames[i] = boardNames[j];
        boardNames[j] = temp; 
      }
    }
  }
  // returning sorted vector 
  return boardNames;
}

// method to save a board in file
void saveBoard(std::string fileName) {
  // creating file object
  std::ofstream file(logFileName, std::ios_base::app); 
  if (file.is_open()) {
    // writing to file and closing it once done
    file << fileName << "\n";
    file.close(); 
  }
}

// method to clear board history
void clearHistory(std::vector<std::string> boardNames) {
  // creating file object
  std::ofstream file(logFileName); 
  // if open overwrite with empty string
  if (file.is_open()) {
    file << ""; 
    file.close(); 
  }
  // loop through boardNames vector and clear all
  for (std::string name : boardNames) {
    std::ofstream file(name); 
    if (file.is_open()) {
      std::remove(name.c_str()); 
    }
  }
}

// method to update list of boards
std::vector<std::string> updateBoardList(std::vector<std::string> boardNames) {
  // creating file object
  std::string line;
  std::ifstream file(logFileName); 
  // adding to boardNames
  if (file.is_open()) {
    while (file) {
      std::getline(file, line);
      boardNames.push_back(line);
    }
  }
  // returning updated vector
  return boardNames; 
}

// method to view a board
void viewBoard(std::string name) {
  // try to open file
  try {
    // creating file object
    std::string line;
    std::ifstream file(name); 
    if (file.is_open()) {
      // iterating over file and printing out its contents
      while (file) {
        std::getline(file, line);
        std::cout << line << std::endl;
      }
    } else { // if file does not exist then throw error
      throw CANNOT_VIEW; 
    }
  } catch (int e) { // catching error and handling it
    if (e == CANNOT_VIEW) {
      std::cout << "File " << name << " does not exist";
    }
  }
}

// method to view an earlier soduku
void viewPreviousSoduku() {
  // gathering fileName input
  std::string fileName; 
  std::cout << "Enter name of soduku file" << std::endl;
  std::cin >> fileName; 
  std::cout << "Opening file " << fileName << std::endl; 
  // opening file after couple seconds delay
  sleep(2); 
  viewBoard(fileName); 
}

// method to view all sodkus
void viewAllSodukus(std::vector<std::string> boardNames) {
  // bubblesorting the names
  boardNames = bubblesort(boardNames); 
  // printing out each board in the vector
    for (std::string name : boardNames) {
      std::cout << name << "\n";
      viewBoard(name);
    }
}

// method to solve a new soduku
void solveNewSudoku(int board[N][N], std::vector<std::string> boardNames) {
  // gathering input
  std::cout << "Enter your soduku puzzle here: (no commas just numbers and space)" << std::endl;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      std::cin >> board[i][j]; 
    }
  }
  // gathering input to save board
  std::string fileName;
  std::cout << "Enter name of soduku file to save it" << std::endl;
  std::cin >> fileName; 
  // adding board to logFile
  addBoardToFile(board, fileName, false); 
  // solving puzzle
  std::cout << "\nSolving puzzle: \n" << std::endl; 
  sleep(3); 
  solveBoard(board, fileName); 
  // saving board
  addBoardToFile(board, fileName, true); 
  saveBoard(fileName);
  // updating vector
  boardNames.push_back(fileName);
}


int main() {
  // vector for boardNames
  std::vector<std::string> boardNames;
  boardNames = updateBoardList(boardNames); 

  // printing out menu
  std::cout << "(1) View a previous soduku" << std::endl;
  std::cout << "(2) Solve new soduku " << std::endl;
  std::cout << "(3) View all sodukus" << std::endl;
  std::cout << "(4) Clear all history" << std::endl;
  // collecting option
  int c = 0;
  std::cin >> c; 
  std::string fileName; 
  int board[N][N]; 

  // if else structure to open the correct method with information
  if (c == 1) {
    viewPreviousSoduku(); 
  } else if (c == 2) {
    solveNewSudoku(board, boardNames);
  } else if (c == 3) {
    viewAllSodukus(boardNames); 
  } else if (c == 4) {
    clearHistory(boardNames);
  }
}
