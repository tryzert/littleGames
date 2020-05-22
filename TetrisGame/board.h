#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include <QVector>
#include <QtGlobal>
#include <QTime>
#include <ctime>
#include <QDebug>
#include <QThread>
//#include <QBasicTimer>
#include <settings.h>


class Board
{
public:
    Board();
    ~Board();
    void initBox();

    void moveLeft();
    void moveRight();

    void moveDown();
    void dropDown();

    void rotateLeft();
    void rotateRight();

//    int box[tz::boxWidth * tz::boxHeight];
    int box[tz::boxHeight][tz::boxWidth];
//    std::vector<std::vector<int>> box;
    int speed;
    int dx, dy;
    int score;
    int currentShapeColor;
    int nextShapeColor;
    int currentShape[4][2];
//    std::vector<std::vector<int> > currentShape;// = {{0, 0}, {0, 0}, {0, 0}, {0, 0}};
//    QVector<4, QVector(int)> currentShape;
    int nextShape[4][2];
//    std::vector<std::vector<int> > nextShape;//{{0, 0}, {0, 0}, {0, 0}, {0, 0}};

private:
    void generateRandomShape();
    void clearFullLine(int row);
    void clearFullLines();
    void swapTwoLines(int row1, int row2);
    bool isShapeMovable(int direction);
    bool isShapeRotatable(int direction);
    bool isLineFull(int row);
    bool isLineEmpty(int row);
    void nextToCurrent();

//    std::vector<std::vector<std::vector<int>>>
    int shapes[8][4][2] = {
        {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
        {{0, -3}, {0, -2}, {0, -1}, {0, -4}},//3
        {{0, -2}, {0, -3}, {0, -1}, {1, -1}},
        {{0, -2}, {0, -3}, {0, -1}, {-1, -1}},//
        {{0, -2}, {0, -3}, {0, -1}, {1, -2}},//
        {{0, -1}, {0, -2}, {1, -1}, {1, -2}},//
        {{0, -1}, {0, -2}, {-1, -1}, {1, -2}},//
        {{0, -1}, {0, -2}, {1, -1}, {-1, -2}}//
    };
};



#endif // BOARD_H
