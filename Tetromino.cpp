#include <iostream>
#include "Tetromino.h"
#include <iostream>

TetColor Tetromino::getColor() const {
  return color;
}
TetShape Tetromino::getShape() const {
  return shape;
}

TetShape Tetromino::getRandomShape(){
  return static_cast<TetShape>(rand() % static_cast<int>(TetShape::COUNT));
}

Tetromino::Tetromino() {}

void Tetromino::setShape(TetShape shape) {
  this->shape = shape;
  color = static_cast<TetColor>(shape);

  switch(shape){
    case TetShape::S:
      blockLocs = {Point(-1,0),Point(0,1),Point(0,0),Point(1,1)};
      break;
    case TetShape::Z:
      blockLocs = {Point(-1,1),Point(0,1),Point(0,0),Point(1,0)};
      break;
    case TetShape::L:
      blockLocs = {Point(0,1),Point(0,0),Point(0,-1),Point(1,-1)};
      break;
    case TetShape::J:
      blockLocs = {Point(-1,-1),Point(0,-1),Point(0,0),Point(0,1)};
      break;
    case TetShape::O:
      blockLocs = {Point(1,1),Point(0,1),Point(0,0),Point(1,0)};
      break;
    case TetShape::I:
      blockLocs = {Point(0,2),Point(0,1),Point(0,0),Point(0,-1)};
      break;
    case TetShape::T:
      blockLocs = {Point(-1,0),Point(0,0),Point(0,-1),Point(1,0)};
      break;
  }
}

void Tetromino::rotateClockwise() {
  if(shape != TetShape::O){
    for(Point& pt : blockLocs){
      pt.multiplyX(-1);
      pt.swapXY();
    }
  }
}

void Tetromino::printToConsole() const {
  for (int y = 3; y >= -3; y--) {
    for (int x = -3; x <= 3; x++) {
      bool pointExists = false;
      for(Point pt : blockLocs) {
        if (pt.getX() == x && pt.getY() == y) {
          pointExists = true;
          break;
        }
      }
      if(pointExists){
        std::cout << 'x';

      } else{
        std::cout << '.';
      }
    }
    std::cout << std::endl;
  }
}












