#include "TetrisGame.h"
#include "GridTetromino.h"
#include <cassert>

TetrisGame::TetrisGame(sf::RenderWindow &newWindow, sf::Sprite &newBlockSprite, const Point &gameboardOffset, const Point &nextShapeOffset):
window{newWindow}, blockSprite{newBlockSprite}, gameboardOffset{gameboardOffset}, nextShapeOffset{nextShapeOffset}{
  reset();
  if (!scoreFont.loadFromFile("../fonts/RedOctober.ttf")){
    assert(false && "Missing font: RedOctober.ttf");
  }
  scoreText.setFont(scoreFont);
  scoreText.setCharacterSize(18);
  scoreText.setFillColor(sf::Color::White);
  scoreText.setPosition(425, 325);
}

void TetrisGame::draw() {
  drawGameboard();
  drawTetromino(currentShape, gameboardOffset);
  drawTetromino(nextShape, nextShapeOffset);
  window.draw(scoreText);
}

void TetrisGame::onKeyPressed(sf::Event event) {
  switch(event.key.code){
    case sf::Keyboard::Up:
      attemptRotate(currentShape);
      break;
    case sf::Keyboard::Left:
      attemptMove(currentShape, -1, 0);
      break;
    case sf::Keyboard::Down:
      if(!attemptMove(currentShape, 0, 1)){
        lock(currentShape);
        shapePlacedSinceLastGameLoop = true;
      }
      break;
    case sf::Keyboard::Right:
      attemptMove(currentShape, 1, 0);
      break;
    case sf::Keyboard::Space:
      drop(currentShape);
      lock(currentShape);
      shapePlacedSinceLastGameLoop = true;
      break;
  }
}

void TetrisGame::processGameLoop(float secondsSinceLastLoop) {
  secondsSinceLastTick += secondsSinceLastLoop;
  if(shapePlacedSinceLastGameLoop){
    if(!spawnNextShape()){
      reset();
    } else {
      pickNextShape();
      int rowsRemoved = board.removeCompletedRows();
      score += (SCORE_PER_ROW * (rowsRemoved)) * rowsRemoved;
      updateScoreDisplay();
      determineSecondsPerTick();
    }
    shapePlacedSinceLastGameLoop = false;
  }
  if(secondsSinceLastTick >= secondsPerTick){
    tick();
    secondsSinceLastTick = 0;
  }
}


void TetrisGame::tick() {
  if(!attemptMove(currentShape, 0, 1)){
    lock(currentShape);
    shapePlacedSinceLastGameLoop = true;
  }
}

void TetrisGame::reset() {
  score = 0;
  updateScoreDisplay();
  determineSecondsPerTick();
  board.empty();
  pickNextShape();
  spawnNextShape();
  pickNextShape();
}

void TetrisGame::pickNextShape() {
  nextShape.setShape(Tetromino::getRandomShape());
}

bool TetrisGame::spawnNextShape() {
  currentShape = nextShape;
  currentShape.setGridLoc(board.getSpawnLoc());
  return isPositionLegal(currentShape);
}

bool TetrisGame::attemptRotate(GridTetromino& shape) {
  GridTetromino t = shape;
  t.rotateClockwise();
  if(isPositionLegal(t)){
    shape.rotateClockwise();
    return true;
  }
  return false;
}

bool TetrisGame::attemptMove(GridTetromino& shape, int x, int y) {
  GridTetromino t = shape;
  t.move(x, y);
  if(isPositionLegal(t)){
    shape.move(x,y);
    return true;
  }
  return false;
}

void TetrisGame::drop(GridTetromino& shape) {
  while(attemptMove(shape, 0, 1)){};
}

void TetrisGame::lock(const GridTetromino& shape) {
  for(const Point& pt : shape.getBlockLocsMappedToGrid()){
    board.setContent(pt, static_cast<int>(shape.getColor()));
  }
}

void TetrisGame::drawBlock(const Point& topLeft, int xOffset, int yOffset, TetColor color) {
  blockSprite.setTextureRect(sf::IntRect( (static_cast<int>(color) * BLOCK_WIDTH), 0, BLOCK_WIDTH, BLOCK_HEIGHT));
  blockSprite.setPosition(topLeft.getX()+(xOffset*BLOCK_WIDTH), topLeft.getY()+(yOffset*BLOCK_HEIGHT));
  window.draw(blockSprite);
}

void TetrisGame::drawGameboard() {
  for(int column{ 0 }; column < Gameboard::MAX_Y; column++){
    for(int row{ 0 }; row < Gameboard::MAX_X; row++){
      if(board.getContent(row, column) != Gameboard::EMPTY_BLOCK){
        drawBlock(gameboardOffset, row, column, static_cast<TetColor>(board.getContent(row, column)));
      }
    }
  }
}

void TetrisGame::drawTetromino(const GridTetromino& tetromino, const Point& topLeft) {
  for (const Point& pt : tetromino.getBlockLocsMappedToGrid()) {
    drawBlock(topLeft, pt.getX(), pt.getY(), tetromino.getColor());
  }
}

void TetrisGame::updateScoreDisplay() {
  std::string scoreString = "Score: " + std::to_string(score);
  scoreText.setString(scoreString);
}

bool TetrisGame::doesShapeIntersectLockedBlocks(const GridTetromino& shape) const {
  if(board.areAllLocsEmpty(shape.getBlockLocsMappedToGrid())){
    return false;
  }
  return true;
}

bool TetrisGame::isPositionLegal(const GridTetromino& shape) const {
  if (isWithinBorders(shape) && !doesShapeIntersectLockedBlocks(shape)){
    return true;
  }
  return false;
}

bool TetrisGame::isWithinBorders(const GridTetromino& shape) const {
  for(const Point& pt: shape.getBlockLocsMappedToGrid()){
    if((pt.getX() < 0 || pt.getX() >= Gameboard::MAX_X) || pt.getY() >= Gameboard::MAX_Y){
      return false;
    }
  }
  return true;
}

void TetrisGame::determineSecondsPerTick() {
  secondsPerTick = MIN_SECONDS_PER_TICK, MAX_SECONDS_PER_TICK - (score / 10000.0);
}




