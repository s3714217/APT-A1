
#include <iostream>
#include <string>

#include "Types.h"
#include "MazeSolver.h"
#include "milestone4.h"

/*
  I used divide and conquer to approach the assignment. Splitting up methods
  and milestones into small tasks. Writing test class for small method and 
  unit testing for the program.
 
  The biggest issue encountered is by using server compiler, there aren't any
  detail exception messages that help to debug the program. The way i used is testing
  single parts to narrow down the problems.
 
  The way i choose to implement the program is writing separate method for each milestone
  so i can test them individually. Some additional methods are added to help modifying the
  structure of the application from using fixed size array to dynamic array.
 
  Positive of this implementation:
   - Easy to test
   - Easy to modify
  
  Negative of the implementation:
   - Some code was repeated
   - Efficiency level is medium


*/
char tempMaze[500][500]; //array to store maze while reading stdin
void testBreadcrumb();
void testTrail();
int rowCount = 0; //maze row counting
int finalCcount = 0; //maze col count


// Read a maze from standard input.
void readMazeStdin(Maze maze);

// Print out a Maze to standard output.
void printMazeStdout(Maze maze, Trail* solution);

// Print Direction of the Solver
void printDirection(Trail* solution);

// Measure maze dimensions 
void measureMaze(Maze maze);

int main(int argc, char** argv) {
    /*THESE ARE SOME EXAMPLE FUNCTIONS TO HELP TEST YOUR CODE
    AS YOU WORK ON MILESTONE 2. YOU CAN UPDATE THEM YOURSELF
    AS YOU GO ALONG.
    COMMENT THESE OUT BEFORE YOU SUBMIT!!!
    std::cout << "TESTING - COMMENT THE OUT TESTING BEFORE YOU SUBMIT!!!" << std::endl;
    testBreadcrumb();
    testTrail();
    std::cout << "DONE TESTING" << std::endl << std::endl;
    */
    // Load Maze from stdin
   
    Maze maze = nullptr;
    measureMaze(maze);
    maze = make_maze(rowCount, finalCcount);
    readMazeStdin(maze);

    // Solve using MazeSolver
    MazeSolver* solver = new MazeSolver();
    solver->setMazeSize(rowCount, finalCcount);
    solver->solve(maze);

    //Get the solver solution
    Trail* solution = solver->getSolution();

    // Print Maze to stdout
     printMazeStdout(maze, solution);
  
    //delete all pointers
     delete solver;
     delete_maze(maze, rowCount, finalCcount);
     delete solution;

    return EXIT_SUCCESS;
}

//Mileston 4
void measureMaze(Maze maze)
{ /*
    measure the two dimensions of the maze
  */
   int colCount = 0;
   bool endofline = false;
   bool endofmaze = false;
  
 while (endofmaze == false)
 {
     char c;
     std::cin.get(c);
      
    if( c == '\n')
    {
      if(endofline == true)
      {
        endofmaze = true;
      }
      else
      {
       endofline = true;
       rowCount += 1;
       finalCcount = colCount - 1;
       colCount = 0;
      }
       
       tempMaze[rowCount][colCount] = '\n';
    }
    else
    {
      tempMaze[rowCount][colCount] = c;
      colCount += 1;
      endofline = false;
    }  
  }
}

void readMazeStdin(Maze maze) 
{
 /*
  initializing the maze details
 */
 for (int x = 0; x < rowCount; x++)
 {
   for( int y =0; y < finalCcount; y++)
   {
    maze[x][y] = tempMaze[x][y];
   }
 }

}

//Milestone 3
void printDirection(Trail* solution)
{
  /*
    finding the moving direction of the solver
    print it to the console
  */
  Breadcrumb* temp = new Breadcrumb(0,0,false);
  
  
  for (int x = 0; x < solution->size()-1; x++)
  {
    temp = solution->getPtr(x);

    if(temp->getX() == solution->getPtr(x+1)->getX()
    && temp->getY() == solution->getPtr(x+1)->getY()+1)
    { 
      std::cout << "north"<<'\n';
    }
    else if(temp->getX() == solution->getPtr(x+1)->getX()-1
    && temp->getY() == solution->getPtr(x+1)->getY())
    { 
      std::cout << "east"<<'\n';
    }
    else if(temp->getX() == solution->getPtr(x+1)->getX()
    && temp->getY() == solution->getPtr(x+1)->getY()-1)
    { 
      std::cout << "south"<<'\n';
    }
    else if(temp->getX() == solution->getPtr(x+1)->getX()+1
    && temp->getY() == solution->getPtr(x+1)->getY())
    { 
      std::cout << "west"<<'\n';
    }
  } 
}

void printMazeStdout(Maze maze, Trail* solution) {
    /*
      Getting a deep copy from solver
      Print it to the console
    */
    Breadcrumb* temp = new Breadcrumb(0,0,false);
    
    for(int s = 0; s < solution->size();s++)
    {
      temp = solution->getPtr(s);
      if(temp->isStale() == false && maze[temp->getY()][temp->getX()] != 'S'
      &&maze[temp->getY()][temp->getX()] != 'E')
      { 
       maze[temp->getY()][temp->getX()] = ROUTE;
      }
    }

    delete temp;

    for (int x = 0; x < rowCount; x++)
  {
    for( int y =0; y < finalCcount; y++)
    {
     char c;
     c = maze[x][y];
     std::cout << c;
     }
    std::cout <<'\n';
  }
  printDirection(solution);
}

/*

void testBreadcrumb() {
    std::cout << "TESTING BREADCRUMB" << std::endl;

    // Make a breadcrumb and print out the contents
    Breadcrumb* breadcrumb = new Breadcrumb(1, 1, false);
    std::cout << breadcrumb->getX() << ",";
    std::cout << breadcrumb->getY() << ",";
    std::cout << breadcrumb->isStale() << std::endl;

    // Change breadcrumb stale-ness and print again
    breadcrumb->setStale(true);
    std::cout << breadcrumb->getX() << ",";
    std::cout << breadcrumb->getY() << ",";
    std::cout << breadcrumb->isStale() << std::endl;
}

void testTrail() {
    std::cout << "TESTING TRAIL" << std::endl;

    // Make a simple trail, should be empty size
    Trail* trail = new Trail();
    std::cout << "Trail size: " << trail->size() << std::endl;

    // Add a breadcrumb to the trail, print size, check contains
    Breadcrumb* b1 = new Breadcrumb(1, 1, false);
    trail->addCopy(b1);
    std::cout << "Trail size: " << trail->size() << std::endl;
    std::cout << "Contains (0,0): " << trail->contains(0,0) << std::endl;
    std::cout << "Contains (1,1): " << trail->contains(1,1) << std::endl;

    // Add second breadcrumb
    Breadcrumb* b2 = new Breadcrumb(0, 0, true);
    trail->addCopy(b2);
    std::cout << "Trail size: " << trail->size() << std::endl;
    std::cout << "Contains (0,0): " << trail->contains(0,0) << std::endl;
    std::cout << "Contains (1,1): " << trail->contains(1,1) << std::endl;

    // Test Get-ith - should be 0,0,true
    Breadcrumb* getB = trail->getPtr(1);
    std::cout << getB->getX() << ",";
    std::cout << getB->getY() << ",";
    std::cout << getB->isStale() << std::endl;

    // Print out the trail
  //  std::cout << "PRINTING OUT A TRAIL IS AN EXERCISE FOR YOU TO DO" << std::endl;
}*/
