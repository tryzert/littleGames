#ifndef TETRIS_H
#define TETRIS_H
#include <QDebug>
#include <QApplication>
#include <QTime>
#include <QMainWindow>
#include <QPushButton>
#include <QKeyEvent>
#include <QScreen>
#include <QRect>
#include <QPainter>
#include <QList>
#include <QBasicTimer>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QGuiApplication>
#include <board.h>
#include <settings.h>

class Tetris : public QMainWindow
{
    Q_OBJECT

public:
    Tetris(QWidget *parent = nullptr);
    ~Tetris();

    Board *board;

    void initUI();
    void initLayout();

    void initHomePageLayout();
    void initGamePageLayout();
    void initAiPageLayout();
    void initSettingsPageLayout();
    void initRecordsPageLayout();

    void buttonBindEvent();

    void setWindowGeometry();
    void drawSquare(QPainter* painter, int x, int y, int colorValue);
    void drawBoard(QPainter *painter);

private:
    //home page
    QPushButton *startGameButton;
    QPushButton *viewAiButton;
    QPushButton *settingsButton;
    QPushButton *recordsButton;

    //start game page
    QPushButton *toHomePageButton;
    QPushButton *pauseGameButton;

    QPushButton *continueGameButton;
    QPushButton *newGameButton;


    //Ai game page

    //settings page

    //records page


    QBasicTimer timer;

    void startGameButtonClicked();
    void viewAiButtonClicked();
    void settinsButtonClicked();
    void recordsButtonClicked();

    void toHomePageButtonClicked();
    void pauseGameButtonClicked();

    void continueGameButtonClicked();
    void newGameButtonClicked();

    int pageIndex;
    bool isGameRunning;

    void showHomePage();
    void hideHomePage();
    void showGamePage();
    void hideGamePage();
    void showAiPage();
    void hideAiPage();
    void showSettingsPage();
    void hideSettingsPage();
    void showRecordsPage();
    void hideRecordsPage();


protected:
    void timerEvent(QTimerEvent *event);
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent* event);
};



#endif // TETRIS_H
