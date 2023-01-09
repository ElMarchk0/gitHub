#include <string>

#ifndef TETRIS_POINT_H
#define TETRIS_POINT_H


class Point {
  friend class TestSuite;
public:
  Point() = default;
  Point(int x, int y);
  int getX() const;
  int getY() const;
  void setX(int x);
  void setY(int y);
  void setXY(int x, int y);
  void swapXY();
  void multiplyX(int factor);
  void multiplyY(int factor);
  static std::string toString() ;
private:
  int x = 0;
  int y = 0;
};


#endif //TETRIS_POINT_H
