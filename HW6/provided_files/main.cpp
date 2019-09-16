#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include "board.h"


int main(int argc, char* argv[]) {

  // Handle the command line arguments
  assert (argc >= 2);

  // Default values
  bool loop_analysis = false;
  bool all_solutions = false;
  bool single_loop = false;
  bool inverse = false;
  bool ascii_art = true;
  
  // puzzle file (regular or inverse) is always first argument
  std::string puzzle_file = argv[1];
  
  // loop through the optional arguments
  for (int i = 2; i < argc; i++) {
    if (std::string(argv[i]) == "--all_solutions") {
      all_solutions = true;
    } else if (std::string(argv[i]) == "--loop_analysis") {
      loop_analysis = true;
    } else if (std::string(argv[i]) == "--single_loop") {
      loop_analysis = true;
      single_loop = true;
    } else if (std::string(argv[i]) == "--inverse") {
      inverse = true;
    } else if (std::string(argv[i]) == "--no_ascii_art") {
      ascii_art = false;
    } else {
      std::cerr << "UNKNOWN OPTION: " << argv[i] << std::endl;
      assert(0);
    }
  }
  // the inverse and all_solutions flags should not be used together
  if (inverse) { assert (!all_solutions); }
  

  if (!inverse) {

    // ------------------------------------------------------------------------
    // Regular mode: Find the path that matches the input cell labels
    Board b(puzzle_file);

    std::vector<Board> solutions;
    std::vector<Board> multiloop_solutions;
    
    if(!all_solutions){
      //if all solutions is not selected
      if(b.solvePuzzle(loop_analysis, single_loop)){
        //solve the puzzle for one solution
        if(ascii_art){
          b.print();
          //and print if ascii art is specified
        }
        solutions.push_back(b);
        //then store in vector for further use
      }
    }else{
      //otherwise of all solutions are specified
      while(b.solvePuzzleAll(solutions, multiloop_solutions,
       loop_analysis, single_loop)){
        //while loop to run the function until there are
        //no more unique solution
        if(ascii_art){
          b.print();
        }
        if(b.multiStatus()){
          //then add to the proper vector
          //depending on if it is multi
          //looped board or not 
          multiloop_solutions.push_back(b);
        }else{
          solutions.push_back(b);
        }
      }
    }
    
    if (solutions.size() + multiloop_solutions.size() == 0) {
      std::cout << "No Solutions" << std::endl;
    }
    else if (all_solutions) {
      if (loop_analysis) {
        std::cout << "Found " << solutions.size() << " Single Loop Solution(s)";
        if (!single_loop) {
          std::cout << " and " << multiloop_solutions.size() << " Multi-Loop Solution(s)";
        }
        std::cout << std::endl;
      } else {
        std::cout << "Found " << solutions.size() << " Solution(s)" << std::endl;
      }
    }

  } else {

    // ------------------------------------------------------------------------
    // Inverse mode: Find a cell labeling whose solution is the input path
    Board b(puzzle_file, true);

    b.generatePuzzle();

    if (ascii_art) {
      b.print(true);
    } else {
      b.printPuzzle();
    }
    
 }
}
