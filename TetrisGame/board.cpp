#include "board.h"

Board::Board()
{
    this->initBox();
}

Board::~Board() {

}


void Board::initBox() {
    this->speed = 1;
    this->score = 0;
    for (int i = 0; i < tz::boxHeight; i++) {
        for (int j = 0; j < tz::boxWidth; j++)
            this->box[i][j] = 0;
    }
    this->generateRandomShape();
    this->nextToCurrent();
}


void Board::generateRandomShape()
{
    qsrand(unsigned(QTime(0, 0, 0).secsTo(QTime::currentTime())));
    this->nextShapeColor = 0;
    while (this->nextShapeColor == 0) {
        this->nextShapeColor = qrand() % 8;
    }

    for (int i = 0; i < 4; i++) {
        this->nextShape[i][0] = this->shapes[this->nextShapeColor][i][0] + tz::boxWidth / 2;
        this->nextShape[i][1] = this->shapes[this->nextShapeColor][i][1];
    }
}


void Board::clearFullLine(int row)
{
    for (int i = 0; i < tz::boxWidth; i++)
        this->box[row][i] = 0;
}


void Board::clearFullLines()
{
    int row1 = 0, row2 = tz::boxHeight;
    for (int i = 0; i < 4; i++) {
        row1 = std::max(row1, this->currentShape[i][1]);
        row2 = std::min(row2, this->currentShape[i][1]);
    }
    int fullLines = 0;
    for (int i = row1; i >= row2; i--) {
        if (this->isLineFull(i)) {
            fullLines++;
            this->score++;
            this->clearFullLine(i);
        }
    }
    if (fullLines == 0)
        return;

    //merge pieces
    int emptyRow = row1, notEmptyRow = emptyRow - 1;
    while (emptyRow > 0 && notEmptyRow >= 0) {
        while (!this->isLineEmpty(emptyRow)) {
            emptyRow--;
//            notEmptyRow--;
        }
        if (emptyRow == 0) break;
        notEmptyRow = emptyRow - 1;
        while (this->isLineEmpty(notEmptyRow)) {
            notEmptyRow--;
        }
        if (notEmptyRow < 0) break;
        this->swapTwoLines(emptyRow, notEmptyRow);
    }
}


void Board::swapTwoLines(int row1, int row2)
{
    for (int i = 0; i < tz::boxWidth; i++)
        std::swap(this->box[row1][i], this->box[row2][i]);
}


void Board::nextToCurrent()
{
    this->currentShapeColor = this->nextShapeColor;
    for (int i = 0; i < 4; i++) {
        this->currentShape[i][0] = this->nextShape[i][0];
        this->currentShape[i][1] = this->nextShape[i][1];
    }
    this->generateRandomShape();
}




//0:left, 1:right, 2:down
bool Board::isShapeMovable(int direction)
{
    for (int i = 0; i < 4; i++) {
        int x = this->currentShape[i][0], y = this->currentShape[i][1];
        if (direction == 0) {
            if (x < 1)
                return false;
            if (y >= 0 && this->box[y][x - 1] > 0)
                return false;
        }
        else if (direction == 1) {
            if (x + 2 > tz::boxWidth)
                return false;
            if (y >= 0 && this->box[y][x + 1] > 0)
                return false;
        }
        else {
            if (y + 2 > tz::boxHeight)
                return false;
            if (y > -1 && this->box[y + 1][x] > 0)
                return false;
        }
    }
    return true;
}


//0:rotate left, 1:rotate right
//bool Board::isShapeRotatable(int direction)
//{

////    return true;
//    return false;
//}

bool Board::isLineFull(int row)
{
    for (int i = 0; i < tz::boxWidth; i++) {
        if (this->box[row][i] == 0)
            return false;
    }
    return true;
}


bool Board::isLineEmpty(int row)
{
    for (int i = 0; i < tz::boxWidth; i++) {
        if (this->box[row][i] > 0)
            return false;
    }
    return true;
}


void Board::moveLeft()
{
    if (this->isShapeMovable(0)) {
        for (int i = 0; i < 4; i++)
            this->currentShape[i][0]--;
    }
}


void Board::moveRight()
{
    if (this->isShapeMovable(1)) {
        for (int i = 0; i < 4; i++)
            this->currentShape[i][0]++;
    }
}


void Board::moveDown()
{
    if (this->isShapeMovable(2)) {
        if (this->dy < tz::gridSize) {
            this->dy += this->speed;
        } else {
            for (int i = 0; i < 4; i++)
                this->currentShape[i][1]++;
            this->dy %= tz::gridSize;
        }
    } else {
//        qDebug() << this->currentShape[0][0] << this->currentShape[0][1] << this->currentShapeColor;
        for (int i = 0; i < 4; i++) {
            this->box[this->currentShape[i][1]][this->currentShape[i][0]] = this->currentShapeColor;
        }
        this->clearFullLines();
//        QThread::sleep(1);

        this->nextToCurrent();
        this->generateRandomShape();
    }

}


void Board::dropDown()
{
    this->speed += 100;
    this->moveDown();
    this->speed -= 100;
}



void Board::rotateLeft()
{
    if (this->currentShapeColor == 5)
        return;
    int sp[4][2];
    sp[0][0] = this->currentShape[0][0];
    sp[0][1] = this->currentShape[0][1];
    for (int i = 1; i < 4; i++) {
        sp[i][0] = this->currentShape[i][1] - this->currentShape[0][1] + this->currentShape[0][0];
        sp[i][1] = -this->currentShape[i][0] + this->currentShape[0][0] + this->currentShape[0][1];
    }
    for (int i = 1; i < 4; i++) {
        if (sp[i][0] < 0 || sp[i][0] > tz::boxWidth - 1)
            return;
        if (sp[i][1] > 0 && this->box[sp[i][1]][sp[i][0]] > 0)
            return;
        if (sp[i][1] > tz::boxHeight - 1)
            return;
    }
    for (int i = 1; i < 4; i++) {
        this->currentShape[i][0] = sp[i][0];
        this->currentShape[i][1] = sp[i][1];
    }
}


void Board::rotateRight()
{
    if (this->currentShapeColor == 5)
        return;
    int sp[4][2];
    sp[0][0] = this->currentShape[0][0];
    sp[0][1] = this->currentShape[0][1];
    for (int i = 1; i < 4; i++) {
        sp[i][0] = -this->currentShape[i][1] + this->currentShape[0][1] + this->currentShape[0][0];
        sp[i][1] = this->currentShape[i][0] - this->currentShape[0][0] + this->currentShape[0][1];
    }
    for (int i = 1; i < 4; i++) {
        if (sp[i][0] < 0 || sp[i][0] > tz::boxWidth - 1)
            return;
        if (sp[i][1] > 0 && this->box[sp[i][1]][sp[i][0]] > 0)
            return;
        if (sp[i][1] > tz::boxHeight - 1)
            return;
    }
    for (int i = 1; i < 4; i++) {
        this->currentShape[i][0] = sp[i][0];
        this->currentShape[i][1] = sp[i][1];
    }
}












