
#include "Trail.h"




Trail::Trail() {
this->breadcrumbs = new Breadcrumb*[this->initialSize];
}

Trail::~Trail() {
   //Deconstrutor
   for(int x =0; x < this->length; x++)
   {
     delete this->breadcrumbs[x];
   }
}

//Milestone 4
void Trail::setMaxSize(int max)
{ 
   //reset size of the array
   this->breadcrumbs = new Breadcrumb*[max];
}



int Trail::size() {
   return this->length;
}

Breadcrumb* Trail::getPtr(int i) {
   
   return this->breadcrumbs[i];
}

void Trail::addCopy(Breadcrumb* t) {
   this->breadcrumbs[length] = t;
   this->length++;
}

bool Trail::contains(int x, int y) {
   
   for(int z = 0; z < this->length; z++)
   {
      if(this->breadcrumbs[z]->getX() == x)
      {
         if(this->breadcrumbs[z]->getY() == y)
         {
           return true;
           
         }
      }
   }
   return false;
}
