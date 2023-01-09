#include "Point.h"


int Point::getX() const {
  return x;
}

int Point::getY() const {
  return y;
}

void Point::setX(int x) {
  this->x = x;
}

void Point::setY(int y) {
  this->y = y;
}

void Point::setXY(int x, int y) {
  this->x = x;
  this->y = y;
}

void Point::swapXY() {
  int xPoint = getX();
  int yPoint = getY();
  setX(yPoint);
  setY(xPoint);
}

Point::Point(int x, int y) {
  setXY(x, y);
}

void Point::multiplyX(int factor) {
  int x = getX();
  setX(x * factor);
}

void Point::multiplyY(int factor) {
  int y = getY();
  setY(y * factor);
}

std::string Point::toString() {
  return std::string("[]");
}




