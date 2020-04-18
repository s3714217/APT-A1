
#include "Breadcrumb.h"

Breadcrumb::Breadcrumb(int x, int y, bool stale) {
   this->x = x;
   this->y = y;
   this->stale = stale;
}

Breadcrumb::~Breadcrumb() {
   
}

int Breadcrumb::getX() {
   // TODO
   return this->x;
}

int Breadcrumb::getY() {
   // TODO
   return this->y;
}

bool Breadcrumb::isStale() {
   // TODO
   return this->stale;
}

void Breadcrumb::setStale(bool stale) {
   this->stale = stale;
}
