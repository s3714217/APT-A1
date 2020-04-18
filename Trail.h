
#ifndef COSC_ASS_ONE_TRAIL
#define COSC_ASS_ONE_TRAIL

#include "Breadcrumb.h"
#include "Types.h"

class Trail {
public:

   /*                                           */
   /* DO NOT MOFIFY ANY CODE IN THIS SECTION    */
   /*                                           */


   // Constructor/Desctructor.
   Trail();
   ~Trail();

   // Number of elements in the Trail
   int size();

   // Get a pointer to the i-th trail element in the array - useful for making breadcrumbs stale.
   Breadcrumb* getPtr(int i);

   // Add a COPY trail element to the BACK of the trail.
   void addCopy(Breadcrumb* trail);
   //Reset the maze size for dynamic array implementation
   void setMaxSize(int max);
   // Check if the trail contain a breadcrumb at the location
   bool contains(int x, int y);

   /*                                           */
   /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
   /*                                           */

private:
   /*                                           */
   /* DO NOT MOFIFY ANY CODE IN THIS SECTION    */
   /*                                           */

   // Trail of breadcrumb objects
  
   Breadcrumb** breadcrumbs;
   int initialSize = 0;
   // Number of breadcrumbs currently in the trail
   int length;

   /*                                           */
   /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
   /*                                           */
};

#endif // COSC_ASS_ONE_TRAIL
