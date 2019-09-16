#ifndef _BOARD_H_
#define _BOARD_H_

#include <string>
#include <vector>
#include <fstream>
#include <cassert>

class Board {
public:

  // CONSTRUCTOR
  Board(const std::string& filename, bool inverse=false);

  // PRINT FUNCTIONS
  void print(bool inverse = false) const;
  void printPuzzle() const;
  void printInverse() const;

  //ACCESSORS
  bool multiStatus(){return multi_loop;}

  // NAIVE SOLVER METHODS
  void zeroEdges();
  void fourEdges();
  
  // NAIVE GENERATOR METHOD 
  void labelAllCells();

  //SOLVER METHODS
  bool solvePuzzle(bool analyze_loop, bool only_single, int w = 0, int h = 0);
  bool solvePuzzleAll(const std::vector<Board>& existing_boards,
   const std::vector<Board>& existing_multi,
   bool analyze_loop, bool only_single, int w = 0, int h = 0);

  //GENERATOR METHOD
  void generatePuzzle();
private:

  // helper function for labelAllCells
  int countEdges(int i, int j);
  bool otherSolutions();

  //helper function for building a puzzle
  int pointOrientation(int j, int i);

  // helper function for solving the puzzle
  int checkCell(int j, int i);
  bool pointCheck(int j, int i);
  bool checkAll();
  bool matching(const Board& other_board);
  void loopAnalysis();
  int countAllEdges();
  int countEdgesLoop(int w = 0, int h = 0, int direction = 0,
   bool found_loop = false,
   int start_w = -1, int start_h = -1);

  // REPRESENTATION
  std::vector<std::vector<int> > board;
  std::vector<std::vector<int> > horizontal;
  std::vector<std::vector<int> > vertical;
  bool multi_loop;
};


#endif
