#include "tetris.h"

Tetris::Tetris(QWidget *parent)
    : QMainWindow(parent)
{
    initUI();
    timer.start(20, Qt::PreciseTimer, this);
    this->isGameRunning = false;
    buttonBindEvent();
    board = new Board();
}

Tetris::~Tetris(){
    delete board;
}


void Tetris::initUI()
{
    this->setFocusPolicy(Qt::StrongFocus);
    this->setWindowTitle("俄罗斯方块");
    setWindowGeometry();
    initLayout();



//    this->show();
}

void Tetris::initLayout()
{
    this->initHomePageLayout();
    this->initGamePageLayout();
    this->initAiPageLayout();
    this->initSettingsPageLayout();
    this->initRecordsPageLayout();
//    this->showHomePage();
}


void Tetris::initHomePageLayout()
{
    //home page

    startGameButton = new QPushButton(this);
    startGameButton->setText("开始游戏");
    startGameButton->setGeometry((tz::windowWidth - tz::homePageButtonWidth) / 2,
                                 (tz::windowHeight - tz::homePageButtonHeight) / 2 - tz::homePageButtonHeight - 100,
                                 tz::homePageButtonWidth,
                                 tz::homePageButtonHeight);

    viewAiButton = new QPushButton(this);
    viewAiButton->setText("观战机器人");
    viewAiButton->setGeometry((tz::windowWidth - tz::homePageButtonWidth) / 2,
                              (tz::windowHeight - tz::homePageButtonHeight) / 2 - tz::homePageButtonHeight - 50,
                              tz::homePageButtonWidth,
                              tz::homePageButtonHeight);

    settingsButton = new QPushButton(this);
    settingsButton->setText("游戏设置");
    settingsButton->setGeometry((tz::windowWidth - tz::homePageButtonWidth) / 2,
                                (tz::windowHeight - tz::homePageButtonHeight) / 2 - tz::homePageButtonHeight,
                                tz::homePageButtonWidth,
                                tz::homePageButtonHeight);

    recordsButton = new QPushButton(this);
    recordsButton->setText("查看战绩");
//    recordsButton->setDisabled(true);
    recordsButton->setGeometry((tz::windowWidth - tz::homePageButtonWidth) / 2,
                               (tz::windowHeight - tz::homePageButtonHeight) / 2 - tz::homePageButtonHeight + 50,
                               tz::homePageButtonWidth,
                               tz::homePageButtonHeight);
}


void Tetris::initGamePageLayout()
{
    this->toHomePageButton = new QPushButton(this);
    this->toHomePageButton->setText("< 返回首页");
    this->toHomePageButton->setGeometry(10, 3, 80, 30);
    this->toHomePageButton->hide();

    this->pauseGameButton = new QPushButton(this);
    this->pauseGameButton->setText("暂停游戏/P");
    this->pauseGameButton->setGeometry(tz::windowWidth - 90, 3, 80, 30);
//    this->pauseGameButton->setDisabled(true);
    this->pauseGameButton->hide();

    this->continueGameButton = new QPushButton(this);
    this->continueGameButton->setText("继续游戏");
    this->continueGameButton->setGeometry((tz::windowWidth - tz::homePageButtonWidth) / 2,
                                          (tz::windowHeight - tz::homePageButtonHeight) / 2 - tz::homePageButtonHeight - 50,
                                          tz::homePageButtonWidth,
                                          tz::homePageButtonHeight + 10);
    this->continueGameButton->hide();

    this->newGameButton = new QPushButton(this);
    this->newGameButton->setText("新游戏");
    this->newGameButton->setGeometry((tz::windowWidth - tz::homePageButtonWidth) / 2,
                                          (tz::windowHeight - tz::homePageButtonHeight) / 2 + tz::homePageButtonHeight - 50,
                                          tz::homePageButtonWidth,
                                          tz::homePageButtonHeight + 10);
    this->newGameButton->hide();
}


void Tetris::initAiPageLayout()
{

}


void Tetris::initSettingsPageLayout()
{

}



void Tetris::initRecordsPageLayout()
{

}



void Tetris::buttonBindEvent()
{
    connect(startGameButton, &QPushButton::pressed, this, &Tetris::startGameButtonClicked);
    connect(viewAiButton, &QPushButton::pressed, this, &Tetris::viewAiButtonClicked);
    connect(settingsButton, &QPushButton::pressed, this, &Tetris::settinsButtonClicked);
    connect(recordsButton, &QPushButton::pressed, this, &Tetris::recordsButtonClicked);

    connect(toHomePageButton, &QPushButton::pressed, this, &Tetris::toHomePageButtonClicked);
    connect(pauseGameButton, &QPushButton::pressed, this, &Tetris::pauseGameButtonClicked);

    connect(continueGameButton, &QPushButton::pressed, this, &Tetris::continueGameButtonClicked);
    connect(newGameButton, &QPushButton::pressed, this, &Tetris::newGameButtonClicked);
}




void Tetris::startGameButtonClicked()
{
    this->hideHomePage();
    this->showGamePage();
//    this->isGameRunning = true;
//    this->toHomePageButton->show();
//    this->update();
}


void Tetris::viewAiButtonClicked()
{
    this->hideHomePage();
    this->showAiPage();
}


void Tetris::settinsButtonClicked()
{
    this->hideHomePage();
    this->showSettingsPage();
}


void Tetris::recordsButtonClicked()
{
    this->hideHomePage();
    this->showRecordsPage();
}


void Tetris::toHomePageButtonClicked()
{
    this->showHomePage();
    this->hideGamePage();
    this->hideAiPage();
    this->hideSettingsPage();
    this->hideRecordsPage();
    this->showHomePage();
    this->isGameRunning = false;
}


void Tetris::pauseGameButtonClicked()
{
    this->isGameRunning = false;
    this->pauseGameButton->setDisabled(true);
    this->continueGameButton->show();
    this->newGameButton->show();
}


void Tetris::continueGameButtonClicked()
{
    this->isGameRunning = true;
    this->pauseGameButton->setDisabled(false);
    this->continueGameButton->hide();
    this->newGameButton->hide();
}


void Tetris::newGameButtonClicked()
{
    this->isGameRunning = true;
    this->pauseGameButton->setDisabled(false);

    this->newGameButton->hide();
    this->continueGameButton->hide();
    this->board->initBox();
}

void Tetris::keyPressEvent(QKeyEvent *event)
{
    Q_UNUSED(event);
//    this->board->generateRandomShape();
    switch (event->key()) {
    case Qt::Key_Left:
        this->board->moveLeft();
        break;
    case Qt::Key_Right:
        this->board->moveRight();
        break;
    case Qt::Key_Space:
        this->board->dropDown();
        break;
    case Qt::Key_P:
//        this->isGameRunning = !this->isGameRunning;
        if (this->isGameRunning)
            this->pauseGameButtonClicked();
        else
            this->continueGameButtonClicked();
        break;
    case Qt::Key_Up:
        this->board->rotateLeft();
//        qDebug() << "up";
        break;
    case Qt::Key_Down:
        this->board->rotateRight();
//        qDebug() << "down";
        break;
//    default:

    }
    this->update();
}



void Tetris::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    if (this->isGameRunning){
        this->drawBoard(&painter);
    }

    this->update();
}


void Tetris::setWindowGeometry() {
    this->setFixedSize(tz::windowWidth, tz::windowHeight);
    QList<QScreen*> screens = QGuiApplication::screens();
    QRect sr = screens.at(0)->geometry();
    QRect wd = this->geometry();
    this->move((sr.width() - wd.width()) / 2, (sr.height() - wd.height()) / 2);
}


void Tetris::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);
    if (this->isGameRunning) {
        this->board->moveDown();
    }

    this->update();

}



void Tetris::showHomePage()
{
    this->startGameButton->show();
    this->viewAiButton->show();
    this->settingsButton->show();
    this->recordsButton->show();
    this->hideGamePage();
    this->hideAiPage();
    this->hideSettingsPage();
    this->hideRecordsPage();
}


void Tetris::hideHomePage()
{
    this->startGameButton->hide();
    this->viewAiButton->hide();
    this->settingsButton->hide();
    this->recordsButton->hide();
}


void Tetris::showGamePage()
{
    this->toHomePageButton->show();
    this->pauseGameButton->show();
    this->continueGameButton->show();
    this->newGameButton->show();
    this->pauseGameButton->setDisabled(true);
}


void Tetris::hideGamePage()
{
    this->toHomePageButton->hide();
    this->pauseGameButton->hide();
    this->continueGameButton->hide();
    this->newGameButton->hide();
}


void Tetris::showAiPage() {
    this->toHomePageButton->show();
    this->pauseGameButton->show();
    this->pauseGameButton->setDisabled(true);
    this->continueGameButton->show();
    this->newGameButton->show();
}


void Tetris::hideAiPage() {
    this->toHomePageButton->hide();
    this->pauseGameButton->hide();
    this->continueGameButton->hide();
    this->newGameButton->hide();
}


void Tetris::showSettingsPage() {
//    this->hideHomePage();
    this->toHomePageButton->show();
}


void Tetris::hideSettingsPage() {
    this->toHomePageButton->hide();
//    this->showHomePage();
}


void Tetris::showRecordsPage() {
//    this->hideHomePage();
    this->toHomePageButton->show();
}


void Tetris::hideRecordsPage(){
    this->toHomePageButton->hide();
//    this->showHomePage();
}


//draw square
void Tetris::drawSquare(QPainter *painter, int x, int y, int colorValue)
{
    QList<unsigned int> colors = {0x000000, 0xCC6666, 0x66CC66, 0x6666CC, 0xCCCC66, 0xCC66CC, 0x66CCCC, 0xDAAA00};
    if (colorValue == 0)
        return;
    QColor color = QColor(colors[colorValue]);
    int s = tz::gridSize;
    //draw square
    painter->fillRect(x + 1, y + 1, s - 2, s - 2, color);

    //draw line
    painter->setPen(color.lighter());
    painter->drawLine(x, y + s - 1, x, y);
    painter->drawLine(x, y, x + s - 1, y);

    painter->setPen(color.darker());
    painter->drawLine(x + 1, y + s - 1, x + s - 1, y + s - 1);
    painter->drawLine(x + s - 1, y + s - 1, x + s - 1, y + 1);

}


void Tetris::drawBoard(QPainter *painter)
{
    int boxMarginTop = tz::windowHeight - tz::boxHeight * tz::gridSize;

    //draw line
//    painter->setPen(QColor())
    painter->drawLine(0, boxMarginTop, tz::windowWidth, boxMarginTop);
    painter->drawLine(tz::boxWidth * tz::gridSize, boxMarginTop, tz::boxWidth * tz::gridSize, tz::windowHeight);

    //draw shape
    for (int i = 0; i < 4; i++) {
        if (this->board->currentShape[i][1] >= 0) {
            this->drawSquare(painter, this->board->currentShape[i][0] * tz::gridSize,
                    boxMarginTop + this->board->currentShape[i][1] * tz::gridSize, this->board->currentShapeColor);
        }
    }

    //draw board
    for (int i = 0; i < tz::boxHeight; i++) {
        for (int j = 0; j < tz::boxWidth; j++) {
            if (this->board->box[i][j] > 0)
                this->drawSquare(painter, j * tz::gridSize, boxMarginTop + i * tz::gridSize, this->board->box[i][j]);
        }
    }
    //draw side next shape
    for (int i = 0; i < 4; i++) {
        this->drawSquare(painter, (this->board->nextShape[i][0] - 1) * tz::gridSize + tz::windowWidth / 2,
                boxMarginTop + 130 + this->board->nextShape[i][1] * tz::gridSize, this->board->nextShapeColor);
//        qDebug() << this->board->nextShape[i][0] << this->board->nextShape[i][1];
    }

    //draw score
    QString scoreText = "得分:" + QString::number(this->board->score);
    QFont font("songti", 15, QFont::Bold, true);
    painter->setFont(font);
    painter->drawText(tz::windowWidth - 100, tz::windowHeight / 2, scoreText);
}






















