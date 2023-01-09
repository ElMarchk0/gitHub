#include <iostream>
#include "Gameboard.h"
#include <iomanip>
#include <cassert>


Gameboard::Gameboard() {
  empty();
}

void Gameboard::empty() {
  for(int row = 0; row < MAX_Y; row++){
    for(int column = 0; column < MAX_X; column++){
      setContent(column, row, EMPTY_BLOCK);
    }
  }
}

void Gameboard::printToConsole() const {
  for(int row = 0; row < MAX_Y; row++){
    for(int column = 0; column < MAX_X; column++){
      if(getContent(column, row) == EMPTY_BLOCK){
        std::cout << std::setw(2) << '.';
      } else {
        std::cout << std::setw(2) << getContent(column, row);
      }
    }
    std::cout << std::endl;
  }
}

int Gameboard::getContent(Point p) const {
  int xAxis = p.getX();
  int yAxis = p.getY();
  assert(isValidPoint(p));
  return grid[yAxis][xAxis];
}

int Gameboard::getContent(int xAxis, int yAxis) const {
  assert(isValidPoint(xAxis, yAxis));
  return grid[yAxis][xAxis];
}

void Gameboard::setContent(Point p, int content) {
  int xAxis = p.getX();
  int yAxis = p.getY();
  if(isValidPoint(p)) grid[yAxis][xAxis] = content;
}

void Gameboard::setContent(int xAxis, int yAxis, int content) {
  if(isValidPoint(xAxis, yAxis)) grid[yAxis][xAxis] = content;
}

void Gameboard::setContent(const std::vector<Point>& pts, int content) {
  for(Point p : pts){
    setContent(p, content);
  }
}

bool Gameboard::areAllLocsEmpty(const std::vector<Point>& pts) const {
  for(Point p : pts){
    if(isValidPoint(p) && getContent(p) != EMPTY_BLOCK ){
      return false;
    }
  }
  return true;
}

int Gameboard::removeCompletedRows() {
  std::vector<int> completedRows = getCompletedRowIndices();
  removeRows(completedRows);
  return completedRows.size();
}

const Point Gameboard::getSpawnLoc() {
  return spawnLoc;
}

bool Gameboard::isValidPoint(Point pt) {
  int xAxis = pt.getX();
  int yAxis = pt.getY();
  return xAxis >= 0 && xAxis < MAX_X && yAxis >= 0 && yAxis < MAX_Y;
}

bool Gameboard::isValidPoint(int xAxis, int yAxis) {
  return xAxis >= 0 && xAxis < MAX_X && yAxis >= 0 && yAxis < MAX_Y;
}

const bool Gameboard::isRowCompleted(int rowIndex)const {
  for(int i = 0; i < MAX_X; i++){
    if(grid[rowIndex][i] == EMPTY_BLOCK){
      return false;
    }
  }
  return true;
}

void Gameboard::fillRow(int rowIndex, int content) {
  for(int column = 0; column < MAX_X; column++){
    setContent(column, rowIndex, content);
  }
}

const std::vector<int> Gameboard::getCompletedRowIndices() const{
  std::vector<int> completedRows;
  for(int row = 0; row < MAX_Y; row++){
    if(isRowCompleted(row)){
      completedRows.push_back(row);
    }
  }
  return completedRows;
}

void Gameboard::copyRowIntoRow(int sourceRow, int targetRow) {
  for(int i = 0; i < MAX_X; i++){
    grid[targetRow][i] = grid[sourceRow][i];
  }
}

void Gameboard::removeRow(int rowIndex) {
  for(int y = rowIndex-1; y >= 0; y--){
    copyRowIntoRow(y, y + 1);
    fillRow(y, EMPTY_BLOCK);
  }
  fillRow(0, EMPTY_BLOCK);
}

void Gameboard::removeRows(const std::vector<int>& rows) {
  for(int row: rows){
    removeRow(row);
  }
}
