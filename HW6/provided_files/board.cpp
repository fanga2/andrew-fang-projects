#include <iostream>
#include <iomanip>
#include <cassert>

#include "board.h"


// ============================================================================
// CONSTRUCTOR
Board::Board(const std::string& filename, bool inverse) {

  // open up the file
  std::ifstream istr(filename);
  assert (istr.good());
  
  // Regular mode: Find the path that matches the input cell labels
  if (!inverse) {
    multi_loop = false;
    //automatically sets multi_loop to false
    std::string s;
    int row = 0;
    // read each row
    while (istr >> s) {
      board.push_back(std::vector<int>());
      // read each cell/column
      for (int i = 0; i < s.size(); i++) {
        if (s[i] == '.') {
          // we represent unlabeled cells with -1
          board[row].push_back(-1);
        } else {
          int foo = atoi(std::string(1,s[i]).c_str());
          assert (foo >= 0 && foo <= 4);
          board[row].push_back(foo);
        }
      }
      assert (board[row].size() == board[0].size());
      row++;
    }
    // all of the edges are currently unknown, which we represent with -1
    horizontal = std::vector<std::vector<int> >(board.size()+1,std::vector<int>(board[0].size(),-1));
    vertical   = std::vector<std::vector<int> >(board.size(),std::vector<int>(board[0].size()+1,-1));
  }

  // Inverse mode: Find a cell labeling whose solution is the input path
  else {
    // read the horizontal edge data
    char str[1000];
    int row = 0;
    std::string s;
    while (1) {
      // note: we use getline here because we want to handle the
      // blank line between horizontal and vertical edge data
      istr.getline(str,1000);
      s = str;
      if (s == "") break;
      horizontal.push_back(std::vector<int>());
      for (int i = 0; i < s.size(); i++) {
        if (s[i] == '.') {
          // no edge is represented with the value zero
          horizontal[row].push_back(0);
        } else {
          // edge is represented with the value 1
          assert (s[i] == '-');
          horizontal[row].push_back(1);
        }
      }
      assert (horizontal[row].size() == horizontal[0].size());
      row++;
    }
    assert (horizontal.size() >= 2);
    // read the vertical edge data
    row = 0;
    while (istr >> s) {
      vertical.push_back(std::vector<int>());
      for (int i = 0; i < s.size(); i++) {
        if (s[i] == '.') {
          // no edge is represented with the value zero
          vertical[row].push_back(0);
        } else {
          // edge is represented with the value 1
          assert (s[i] == '|');
          vertical[row].push_back(1);
        }
      }
      assert (vertical[row].size() == horizontal[0].size()+1);
      row++;
    }
    assert (vertical.size() +1 == horizontal.size());
    // note that the cell data dimensions are slightly different than
    // the horizontal and vertical edge data.  The vertical data has
    // an extra column, and the horizontal data has an extra row.
    board = std::vector<std::vector<int> >(horizontal.size()-1,std::vector<int>(horizontal[0].size(),-1));
  }
}


// ============================================================================
// SMALL HELPER ROUTINES FOR ASCII ART PRINTING CHARACTERS
char vChar(int i)  {
  if (i == -1) return '?';
  if (i == 0) return ' ';
  assert (i == 1); return '|';
}
char hChar(int i) {
  if (i == -1) return '?';
  if (i == 0) return ' ';
  assert (i == 1); return '-';
}
char valueChar(int i) {
  if (i == -1) return ' ';
  if (i == 0) return '0';
  if (i == 1) return '1';
  if (i == 2) return '2';
  if (i == 3) return '3';
  assert (i == 4); return '4';
}


// ============================================================================
// PRINT AN ASCII ART REPRESENTATION OF THE CURRENT BOARD
// Note: Yes, this function exceeds normal line width.  
void Board::print(bool inverse) const {
  // loop over each row of the board
   if(!inverse){ 
    //does not print solution if invers
    if(multi_loop){
      //prints solution based of if it is
      //multiloop or not
      std::cout << "Multi-Loop Solution:" << std::endl;
    }else{
      std::cout << "Solution:" << std::endl;
    }
  }
  for (int j = 0; j < board.size(); j++) {
    assert (board[0].size() == board[j].size());
    // what is the rightmost vertical edge for this row?
    char right = vChar(vertical[j][board[j].size()]);
    // print the horizontal edges above the current row
    for (int i=0; i<board[j].size(); i++) { char top =hChar(horizontal[j][i]); std::cout<<"+" + std::string(5,top);                 } std::cout<<"+"<<std::endl; 
    // loop over the cells in the row
    for (int i=0; i<board[j].size(); i++) { char left=vChar(vertical[j][i]);   std::cout<<left<<"     ";                            } std::cout<<right<<std::endl;
    for (int i=0; i<board[j].size(); i++) { char left=vChar(vertical[j][i]);   std::cout<<left<<"  "<<valueChar(board[j][i])<<"  "; } std::cout<<right<<std::endl;
    for (int i=0; i<board[j].size(); i++) { char left=vChar(vertical[j][i]);   std::cout<<left<<"     ";                            } std::cout<<right<<std::endl;
  }
  // print the horizontal edges below the bottom row
  for   (int i=0; i<board[0].size(); i++) { char top =hChar(horizontal[board.size()][i]); std::cout<<"+" + std::string(5,top);      } std::cout<<"+"<<std::endl;
  std::cout << std::endl;
  //add an extra space.
}


// print the non-ascii art version of the cell count data
// (can be used as input for the regular Slitherlink puzzle solver)
void Board::printPuzzle() const {
  for (int j = 0; j < board.size(); j++) {
    for (int i = 0; i < board[j].size(); i++) {
      if (board[j][i] == -1) {
        // unlabeled cells represented with .
        std::cout << ".";
      } else {
        std::cout << board[j][i];
      }
    }
    std::cout << std::endl;
  }
}


// print the non-ascii art version of the path data
// (can be used as input for the inverse Slitherlink puzzle generator)
void Board::printInverse() const {
  for (int j = 0; j < horizontal.size(); j++) {
    for (int i = 0; i < horizontal[j].size(); i++) {
      // it's an error to print a path with unknown edges
      assert (horizontal[j][i] != -1);
      if (horizontal[j][i] == 0) {
        // 'no edge' represented with .
        std::cout << ".";
      } else {
        assert (horizontal[j][i] == 1);
        // 'edge present' represented with -
        std::cout << "-";
      }
    }
    std::cout << std::endl;
  }
  // blank line between the data
  std::cout << std::endl;
  for (int j = 0; j < vertical.size(); j++) {
    for (int i = 0; i < vertical[j].size(); i++) {
      assert (vertical[j][i] != -1);
      if (vertical[j][i] == 0) {
        // 'no edge' represented with .
        std::cout << ".";
      } else {
        assert (vertical[j][i] == 1);
        // 'edge present' represented with |
        std::cout << "|";
      }
    }
    std::cout << std::endl;
  }
}


// ============================================================================
// NAIVE SOLVER METHODS

void Board::zeroEdges() {
  for (int j = 0; j < board.size(); j++) {
    for (int i = 0; i < board[j].size(); i++) {
      // cells labeled with 0 should have all edges set to 0 (no edge)
      if (board[j][i] == 0) {
        horizontal[j][i] = 0;
        horizontal[j+1][i] = 0;
        vertical[j][i] = 0;
        vertical[j][i+1] = 0;
      }
    }
  }
}

void Board::fourEdges() {
  for (int j = 0; j < board.size(); j++) {
    for (int i = 0; i < board[j].size(); i++) {
      // cells labeled with 4 should have all edges set to 1 (edge present)
      if (board[j][i] == 4) {
        horizontal[j][i] = 1;
        horizontal[j+1][i] = 1;
        vertical[j][i] = 1;
        vertical[j][i+1] = 1;
      }
    }
  }
}


// ============================================================================
// NAIVE GENERATOR METHODS

void Board::labelAllCells() {
  for (int j = 0; j < board.size(); j++) {
    for (int i = 0; i < board[0].size(); i++) {
      // simply label all cells to match their edge count (not very interesting)
      board[j][i] = countEdges(j,i);
    }
  }
}


// helper function for naive generator method
int Board::countEdges(int j, int i) {
  int answer = 0;
  if (horizontal[j][i]   ==  1) answer++;
  if (horizontal[j+1][i] ==  1) answer++;
  if (vertical[j][i]   ==  1) answer++;
  if (vertical[j][i+1] ==  1) answer++;
  return answer;
}

int Board::checkCell(int j, int i){
  //checks a given cell to see if it has the right number of edges
  if(board[i][j] != -1){
    int temp = countEdges(i, j);
    if(temp != board[i][j]){
      if(temp > board[i][j]){
        //if more edges than the number return -1
        //to show th board is impossible.
        return -1;
      }else{
        return 0;
        //otherwise return 0 to show the board is
        //possible but incomplete
      }
    }
  }
  return 1;
}

bool Board::checkAll(){
  //checks all the cells and points at the very end
  //to see if the grid is impossible or incomplete
  for(int i = 0; i <= board.size(); i++){
    for(int j = 0; j <= board[0].size(); j++){
      if(j != board[0].size() && i != board.size()){  
        if(checkCell(j, i) != 1) return false;
      }
      if(!pointCheck(j, i)) return false;
    }
  }
  return true;
}

bool Board::pointCheck(int j, int i){
  //checks the upper left "point" of a cell to ensure that
  //each "point" of each cell has exactly 2  or 0 lines
  //coming out from it.
  int counter = 0;
  if(j != 0 && horizontal[i][j-1] == 1) counter++;
  if(i != 0 && vertical[i-1][j] == 1) counter++;
  if(j != board[0].size() && horizontal[i][j] == 1) counter++;
  if(i != board.size() && vertical[i][j] == 1) counter++;
  if(counter == 2 || counter == 0) return true;
  return false;
}

bool Board::solvePuzzle(bool analyze_loop, bool only_single, int w, int h){
  //algorithim for only a single solution.
  bool correct = true;
  //boolean variable storing the results of the cell check.
  if(w == board[0].size() && h == board.size()){   
    if(!checkAll()){
      return false;
      //if we get to the very end of the board, we check
      //the entire thing to ensure that there is no incompleteness
      //otherwise return false, otherwise returning true,
      //as such, this can be considered the base case.
    }
    if(analyze_loop){
      //if the loop requires analysis
      loopAnalysis();
      if(only_single){
        //if single loop is declared and the firs result is a multiloop
        //result return false and try again
        if(multi_loop) return false;
      }
    }
  }else if(w == board[0].size()){
    //when checking the right edge, each edge vertical is either
    //present or not present so first we try vertical to 1
    vertical[h][w] = 1;
    if(!pointCheck(w, h)) correct = false;
    if(checkCell(w-1, h) == -1) correct = false;
    //perform necessary checks, namely of the cell that adding
    //the line would impact
    if(!correct || !solvePuzzle(analyze_loop, only_single, 0, h+1)){
      //if the check fails or a later result returns false, change
      //the edge to not be present
      correct = true;
      vertical[h][w] = 0;
      if(!pointCheck(w, h)) correct = false;
      if(checkCell(w-1, h) == -1) correct = false;
      //check again
      if(!correct || !solvePuzzle(analyze_loop, only_single, 0, h+1)){
        //if nothing works return false
        return false;
      }
    }
  }else if(h == board.size()){
    //if along the bottom edge, each edge horizontal is either
    //present or not present so we try horizontal to one 
    horizontal[h][w] = 1;
    if(!pointCheck(w, h)) correct = false;
    if(checkCell(w, h-1) == -1) correct = false;
    //check the cell it impacts
    if(!correct || !solvePuzzle(analyze_loop, only_single, w+1, h)){
      //if the check fails or a later result returns false, change to
      //0 and try again
      correct = true;
      horizontal[h][w] = 0;
      if(!pointCheck(w, h)) correct = false;
      if(checkCell(w, h-1) == -1) correct = false;
      //check again
      if(!correct || !solvePuzzle(analyze_loop, only_single, w+1, h)){
        //if nothing works return false
        return false;
      }
    }
  }else{
    horizontal[h][w] = 1;
    vertical[h][w] = 1; 
    //in a normal cell, set the horizontal and coresponding vertical
    //edge to 1 
    if(!pointCheck(w, h)) correct = false;   
    if(checkCell(w, h) == -1) correct = false;
    if(w != 0 && checkCell(w-1, h) == -1) correct = false;
    if(h != 0 && checkCell(w, h-1) == -1) correct = false;
    //then analyze the "point" in the upper left cornere of the cell
    //and check to see if the current cell or those above and to the left
    //of it are either complete or incomplete and not impossible
    if(!correct || !solvePuzzle(analyze_loop, only_single, w+1, h)){
      //if that fails, attempt to only have the upper edge present
      correct = true;
      horizontal[h][w] = 1;
      vertical[h][w] = 0;
      if(!pointCheck(w, h)) correct = false;
      if(checkCell(w, h) == -1) correct = false;
      if(h != 0 && checkCell(w, h-1) == -1) correct = false;
      //perform the necessary checks once again 
      //(though only on two cells this time)
      // and then try again
      if(!correct || !solvePuzzle(analyze_loop, only_single, w+1, h)){
        //if the second check fails or if a later result returns false
        //try again with only the left edge present
        correct = true;
        horizontal[h][w] = 0;
        vertical[h][w] = 1;
        if(!pointCheck(w, h)) correct = false;
        if(checkCell(w, h) == -1) correct = false;
        if(w != 0 && checkCell(w-1, h) == -1) correct = false;
        if(!correct || !solvePuzzle(analyze_loop, only_single, w+1, h)){
          //if third check fails, try again with no edges against the cell
          correct = true;
          horizontal[h][w] = 0;
          vertical[h][w] = 0;
          if(!pointCheck(w, h)) correct = false;
          //final check
          if(!correct || !solvePuzzle(analyze_loop, only_single, w+1, h)){
            //if this fails a final time return false.
            return false;
          }
        }
      }
    }
  }
  //returns true if none of the false cases are met.
  return true;  
}

bool Board::solvePuzzleAll(const std::vector<Board>& existing_boards,
 const std::vector<Board>& existing_multi, bool analyze_loop,
 bool only_single, int w, int h){
  //algorithim for multiple solutions, it is the same as the
  //algorithim for a single solution except for when
  //we reach the end of the grid. 
  bool correct = true;
  if(w == board[0].size() && h == board.size()){   
    if(!checkAll()){     
      return false;
    }
    //perform the normal check of everything at the end
    for(int i = 0; i < existing_boards.size(); i++){
      //then check to see if the current board matches
      //any of the calculated existing boards to ensure
      //that each solution is different
      if(matching(existing_boards[i])) return false;
      //if it is the same return false;
    }
    if(analyze_loop){
      //same loop analysis as in the single loop
      //removing a multi-looped solutions
      loopAnalysis();
      if(only_single){
        if(multi_loop){
          return false;
        }
      }else{
        //if not single looped then we have a seprate vector
        //of calculated multi-loop boards which we must compare
        //and reject the current board if it does match
        //an existing solution
        for(int i = 0; i < existing_multi.size(); i++){
          if(matching(existing_multi[i])) return false;
        }
      }
    }
  }else if(w == board[0].size()){
    vertical[h][w] = 1;
    if(!pointCheck(w, h)) correct = false;
    if(checkCell(w-1, h) == -1) correct = false;
    if(!correct || !solvePuzzleAll(existing_boards, existing_multi,
     analyze_loop, only_single, 0, h+1)){
      //note all function declarations of solvePuzzleAll now pass in
      //a vector of existing boards and existing multi-loop boards
      //to ensure that we don't repeat the same board again
      //otherwise the function is exactly the same as a single loop
      //solution.
      correct = true;
      vertical[h][w] = 0;
      if(!pointCheck(w, h)) correct = false;
      if(checkCell(w-1, h) == -1) correct = false;
      if(!correct || !solvePuzzleAll(existing_boards,
       existing_multi, analyze_loop, only_single, 0, h+1)){
        return false;
      }
    }
  }else if(h == board.size()){
    horizontal[h][w] = 1;
    if(!pointCheck(w, h)) correct = false;
    if(checkCell(w, h-1) == -1) correct = false;
    if(!correct || !solvePuzzleAll(existing_boards, existing_multi,
     analyze_loop, only_single, w+1, h)){
      correct = true;
      horizontal[h][w] = 0;
      if(!pointCheck(w, h)) correct = false;
      if(checkCell(w, h-1) == -1) correct = false;
      if(!correct || !solvePuzzleAll(existing_boards, existing_multi,
       analyze_loop, only_single, w+1, h)){
        return false;
      }
    }
  }else{
    horizontal[h][w] = 1;
    vertical[h][w] = 1;  
    if(!pointCheck(w, h)) correct = false;   
    if(checkCell(w, h) == -1) correct = false;
    if(w != 0 && checkCell(w-1, h) == -1) correct = false;
    if(h != 0 && checkCell(w, h-1) == -1) correct = false;
    if(!correct || !solvePuzzleAll(existing_boards, existing_multi,
     analyze_loop, only_single, w+1, h)){
      correct = true;
      horizontal[h][w] = 1;
      vertical[h][w] = 0;
      if(!pointCheck(w, h)) correct = false;
      if(checkCell(w, h) == -1) correct = false;
      if(h != 0 && checkCell(w, h-1) == -1) correct = false;
      if(!correct || !solvePuzzleAll(existing_boards, existing_multi,
       analyze_loop, only_single, w+1, h)){
        correct = true;
        horizontal[h][w] = 0;
        vertical[h][w] = 1;
        if(!pointCheck(w, h)) correct = false;
        if(checkCell(w, h) == -1) correct = false;
        if(w != 0 && checkCell(w-1, h) == -1) correct = false;
        if(!correct || !solvePuzzleAll(existing_boards, existing_multi,
         analyze_loop, only_single, w+1, h)){
          correct = true;
          horizontal[h][w] = 0;
          vertical[h][w] = 0;
          if(!pointCheck(w, h)) correct = false;
          if(!correct || !solvePuzzleAll(existing_boards, existing_multi,
           analyze_loop, only_single, w+1, h)){
            return false;
          }
        }
      }
    }
  }
  return true;  
}

bool Board::matching(const Board& other_board){
  if(board.size() != other_board.board.size() ||
   board[0].size() != other_board.board[0].size()){
    //ensures that the compared boards must be the same size.
    std::cerr <<
    "WARNING: comparing boards of unequal size" << std::endl;
    assert(0);
  }
  //only compares the vertical and horizontal 2d vectors as the board should
  //be the same and the vertical/horizontal is the most useful
  for(int i = 0; i <= board.size(); i++){
    for(int j = 0; j <= board[0].size(); j++){
      if(i != board.size() &&
       vertical[i][j] != other_board.vertical[i][j]) return false;
      if(j != board[0].size() &&
       horizontal[i][j] != other_board.horizontal[i][j]) return false;
    }
  }
  return true;
}

void Board::loopAnalysis(){
  //a function to perform loop analysis
  //with two more helper functions by
  //comparing the total number of edges in the entire
  //grid with those of a single loop
  if(countAllEdges() != countEdgesLoop()){
    multi_loop = true;
  }else{
    multi_loop = false;
  }
}

int Board::countAllEdges(){
  //counts all the edges in the entire grid
  int counter = 0;
  for(int i = 0; i <= board.size(); i++){
    for(int j = 0; j <= board[0].size(); j++){
      if(i != board.size() && vertical[i][j] == 1) counter++;
      if(j != board[0].size() && horizontal[i][j] == 1) counter++;
    }
  }
  return counter;
}

int Board::countEdgesLoop(int w, int h, int direction,
 bool found_loop, int start_w, int start_h){
  //the grid starts when we find a horizontal edge
  if(horizontal[h][w] == 1 && !found_loop){
    found_loop = true;
    start_w = w;
    start_h = h;
  }
  if(!found_loop){
    //if we have not found a loop yet, keep searching
    if(w == board[0].size()) return countEdgesLoop(0, h+1);
    return countEdgesLoop(w+1, h);
  }else{
    if(direction == 0){
      //depending on the direction we follow the path the loop
      //takes us, since the 2 or 0 point rule, there is only one
      //path
      //in the 0 direction to loop can either go up right or down
      //since we start at the first horizontal there is no need to check
      //if the next horizontal is the start point. the return is 1 for
      //the edge the loop is currently on + the rest of the edges int he loop
      if(w != horizontal[0].size()-1 && horizontal[h][w+1] == 1) 
        return 1+countEdgesLoop(w+1, h, 0, found_loop, start_w, start_h);
      if(h != 0 && vertical[h-1][w+1] == 1) 
        return 1+countEdgesLoop(w+1, h-1, 90, found_loop, start_w, start_h);
      if(h != vertical.size() && vertical[h][w+1] == 1) 
        return 1+countEdgesLoop(w+1, h, 270, found_loop, start_w, start_h);
    }else if(direction == 90){
      if(start_h == h && start_w == w) return 1;
      //returns 1 if the next left edge is where the loop started
      //otherwise counts the loop with a 90 degrees direction going
      //up, left, or right
      if(h != 0 && vertical[h-1][w] == 1) 
        return 1+countEdgesLoop(w, h-1, 90, found_loop, start_w, start_h);
      if(w != 0 && horizontal[h][w-1] == 1) 
        return 1+countEdgesLoop(w-1, h, 180, found_loop, start_w, start_h);
      if(w != horizontal[0].size() && horizontal[h][w] == 1) 
        return 1+countEdgesLoop(w, h, 0, found_loop, start_w, start_h);
    }else if(direction == 180){
      //the direction 180 can advance either up, left or down, no
      //need to check for the original horizontal since we can't go
      //backwards in the loop
      if(w != 0 && horizontal[h][w-1] == 1) 
        return 1+countEdgesLoop(w-1, h, 180, found_loop, start_w, start_h);
      if(h != 0 && vertical[h-1][w] == 1) 
        return 1+countEdgesLoop(w, h-1, 90, found_loop, start_w, start_h);
      if(h != vertical.size() && vertical[h][w] == 1) 
        return 1+countEdgesLoop(w, h, 270, found_loop, start_w, start_h);
    }else if(direction == 270){
      if(start_w == w && start_h == h+1) return 1;
      //returns 1 if the right edge path is where the loop started.
      //otherwise the path goes down, left or right
      if(h != vertical.size()-1 && vertical[h+1][w] == 1) 
        return 1+countEdgesLoop(w, h+1, 270, found_loop, start_w, start_h);
      if(w != 0 && horizontal[h+1][w-1] == 1) 
        return 1+countEdgesLoop(w-1, h+1, 180, found_loop, start_w, start_h);
      if(w != horizontal.size() && horizontal[h+1][w] == 1) 
        return 1+countEdgesLoop(w, h+1, 0, found_loop, start_w, start_h);
    }
    return 0;
  }
}

void Board::generatePuzzle(){
  labelAllCells();
  //start by labeling all the words
  for(int i = 0; i < board.size(); i++){
    for(int j = 0; j < board[0].size(); j++){
      //loop through each cell in the board
      int temp = board[i][j];
      board[i][j] = -1;
      //try to set the cell to blank
      if(otherSolutions()){
        //if this creates an alternate solution
        //put the cell back 
        board[i][j] = temp;
      }
    }
  }
}

bool Board::otherSolutions(){
  std::vector<std::vector<int>> copy_vert = vertical;
  std::vector<std::vector<int>> copy_hori = horizontal;
  // sets the current horizontal and vertical in these copy vectors
  std::vector<Board> temp;
  std::vector<Board> temp_multi;
  //the vectors of boards, multi will always remain empty
  vertical = std::vector<std::vector<int> >(board.size(),
    std::vector<int>(board[0].size()+1,-1));
  horizontal = std::vector<std::vector<int> >(board.size()+1,
    std::vector<int>(board[0].size(),-1));
  //clear the vertical and horizontal vectors to prevent
  //problems from already existing lines
  while(solvePuzzleAll(temp, temp_multi, false, false)){
    if(temp.size() >= 1){     
      vertical = copy_vert;
      horizontal = copy_hori;
      return true;
      //if the size is greater than or equal to 1 return true
      //and set the proper lines back
    }
    temp.push_back(*this);
  }
  //otherwise set the horizontal and vertical back to normal
  //and then return false
  vertical = copy_vert;
  horizontal = copy_hori;
  return false;
}