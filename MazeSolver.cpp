
#include "MazeSolver.h"


MazeSolver::MazeSolver() {
   solution = new Trail();

}

MazeSolver::~MazeSolver() {
   delete solution;
}

//Milestone 4
void MazeSolver::setMazeSize(int r, int c)
{
   //setting the MazeSize for solve method
   rows = r;
   cols = c;
}

void MazeSolver::solve(Maze maze) {
   solution->setMaxSize(rows*cols); //reset max size of the trails

   Breadcrumb* b = new Breadcrumb(0,0,true);
   //initialize starting points
   
   for(int x = 0; x < cols; x++)
   {
      for(int y = 0; y < rows; y++)
      {
       
         if(maze[y][x] == 'S')
         {
            b = new Breadcrumb(x,y,false);
            solution->addCopy(b);
         }
       
      }
   }

   //solving the maze 

   /*
      Algorithm:
      Repeate until b =nullptr
      1. Identify the neighbors
      2. Check if neighbors is OPEN
      3. Check if neighbors is in the solution
      4. If yes, Moving checking points to neigbors
      5. Add checking points to solution
      6. Check if the next neighbors is 'E'
      7. If no, continue the loop untill the neighbors is 'E'
      8. If yes, add 'E' neighbor to solution and b = nullptr
      9. Else, the solver got stuck, trace back the solution until
      find a new (checkingpoint)
   */
   while ( b != nullptr)
   {
      if(maze[b->getY()-1][b->getX()] == OPEN &&
      solution->contains(b->getX(), b->getY()-1) ==false)
      {
         b = new Breadcrumb(b->getX(), b->getY()-1,false);
         solution->addCopy(b);

         if(maze[b->getY()-1][b->getX()] == 'E')
         {
            solution->addCopy(new Breadcrumb(b->getX(),b->getY()-1,false));   
            b = nullptr;
         }
      }

      else if(maze[b->getY()][b->getX()+1] == OPEN &&
      solution->contains(b->getX()+1, b->getY()) ==false)
      {
         b = new Breadcrumb(b->getX()+1, b->getY(),false);
         solution->addCopy(b);

         if(maze[b->getY()][b->getX()+1] == 'E')
         {
            solution->addCopy(new Breadcrumb(b->getX()+1,b->getY(),false));   
            b = nullptr;
         }
         
      }

      else if(maze[b->getY()+1][b->getX()] == OPEN&&
      solution->contains(b->getX(), b->getY()+1) ==false)
      {
         b = new Breadcrumb(b->getX(), b->getY()+1,false);
         solution->addCopy(b);

         if(maze[b->getY()+1][b->getX()] == 'E')
         {
            solution->addCopy(new Breadcrumb(b->getX(),b->getY()+1,false));
            b = nullptr;
         }
      }

      else if(maze[b->getY()][b->getX()-1] == OPEN&&
      solution->contains(b->getX()-1, b->getY()) ==false)
      {
         b = new Breadcrumb(b->getX()-1, b->getY(),false);
         solution->addCopy(b);  

         if(maze[b->getY()][b->getX()-1] == 'E')
         {
            solution->addCopy(new Breadcrumb(b->getX()-1,b->getY(),false));
            b = nullptr;
         }
      }
      
      else
      {  
        
         for (int i = solution->size()-1; i >=0; i--)
         {
            if(b->getX() == solution->getPtr(i)->getX() 
            && b->getY() == solution->getPtr(i)->getY()
             
            )
            {
               solution->getPtr(i)->setStale(true);
               b = solution->getPtr(i-1);
               i = 0;
            }
         }
      }



   }
}



Trail* MazeSolver::getSolution() {
   //Make a deep copy of the maze
  Trail* DCsolution = new Trail();
   DCsolution->setMaxSize(rows*cols);
   for(int l = 0; l < this->solution->size();l++)
   {
      if(this->solution->getPtr(l)->isStale()==false)
      {
      DCsolution->addCopy(
         new Breadcrumb(this->solution->getPtr(l)->getX(),
                        this->solution->getPtr(l)->getY(), 
                        this->solution->getPtr(l)->isStale())
      );
      }
   }
   this->solution->~Trail();


   return DCsolution;
}
