HOMEWORK 6: INVERSE SLITHERLINK RECURSION


NAME:  Andrew Fang



COLLABORATORS AND OTHER RESOURCES:

Cameron, Milo, Prashant



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  29



DESCRIPTION: A homework assignment which takes a Slitherlink board and builds a grid around it according to the rules of slitherlink or builds a possible board based on a given grid. I can print out a single solution, a solution with only one loop and all possible solutions. The text file input is a rectangular grid of numbers and the reverse board is a collection of + and - in order to create a grid. There are example text files included.



ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:
(order notation & concise paragraph, < 200 words)
The dimensions of the board (w and h) 
The number of labeled cells in the puzzle (n)? 
The number of edges in the closed loop fence path (e)?
Etc. 

The order notation of my algorithim is O((4^wh*2^w*2^h)wh) in worst case without any loop analysis as we need to go though each cell for 4 possibilities and worst case we must go though all possibilities and when we do we check at the end with wh as the size of that function. The all solutions would be O((4^wh*2^w*2^h)w^2h^2) as we have to check at the end and also have to check against each possible solution which size would be wh. With the addition of loop analysis it becomes O((4^wh*2^w*2^h)w^2h^2*e) for a single loop and O((4^wh*2^w*2^h)w^3h^3*e) for the second loop as we must find the total number of edges and compare it to the total edge number to find if it is multiloop or single loop multiplying wh and e to each scenerio in worst case. Finally, my inverse algorithim is O((4^wh*2^w*2^h)w^3h^3) as it seraches through ever cell trying to remove it and then performs a all solutions check multiplying all solutions by wh. 

SUMMARY OF PERFORMANCE OF YOUR PROGRAM ON THE PROVIDED PUZZLES:
# of solutions & approximate wall clock running time for different
puzzles for a single solution or all solutions.  

puzzle 5:
single solution: .031s
all solutions: .078s
all solutions loop analysis: .087s
all solutions loop analysis single loop: .040s

inverse4:
inverse:.507s

MISC. COMMENTS TO GRADER:  
(optional, please be concise!)


