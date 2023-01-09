#include "GridTetromino.h"
#include "Tetromino.h"

GridTetromino::GridTetromino(){
  this->gridLoc = Point(0,0);
}

Point GridTetromino::getGridLoc() const{
  return this->gridLoc;
}

void GridTetromino::setGridLoc(int x, int y) {
  this->gridLoc = Point(x, y);
}

void GridTetromino::setGridLoc(const Point& newGridLoc) {
  this->gridLoc = newGridLoc;
}

void GridTetromino::move(int xOffset, int yOffset) {
  gridLoc.setX(gridLoc.getX() + xOffset);
  gridLoc.setY(gridLoc.getY() + yOffset);
}

std::vector<Point> GridTetromino::getBlockLocsMappedToGrid() const{
  std::vector<Point> mappedLocs;
  for(Point pt : blockLocs) {
    mappedLocs.push_back(Point(pt.getX() + gridLoc.getX(), pt.getY() + gridLoc.getY()));
  }
  return mappedLocs;
}