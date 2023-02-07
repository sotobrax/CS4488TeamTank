#include "MainHeader.h"
#include "Tank.h"
#include <QGraphicsPixmapItem>
#include "map_creator.h"
#include <QScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QScreen* primaryScreen = QApplication::primaryScreen();


    MapCreator map_creator;
    //map_creator.setFile(":/sounds/my_map.txt"); NOT SURE why this doesn't work
    map_creator.setFile("C:\\Users\\pawan\\OneDrive\\Documents\\GitHub\\CS4488TeamTank\\TankTest\\my_map.txt");
    //Create scene on the heap
    QGraphicsScene* scene = new QGraphicsScene();

    int w = primaryScreen->geometry().width() / 2;
    int h = primaryScreen->geometry().height() / 2;

    //Create rectangle for scene
    //MyRect* player = new MyRect();
    Tank *tank = new Tank();

    //by default l and w of rect is 0 need to change
   // tank->setPixmap(QPixmap("tank1.png"));
   // tank->setPos(70, 40);

    //(0, 0, 70,40);
    //add item to scene
    scene->addItem(tank);

    //add a view, this is what displays the graphics
    QGraphicsView* view = new QGraphicsView(scene);

    //Create map using map_creator
    map_creator.CreateMap(scene);

    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //view->setBackgroundBrush(QBrush(Qt::black));
    view->setAlignment(Qt::AlignCenter);
    view->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    view->setRenderHint(QPainter::Antialiasing);
    //view->resize(w * 2 - 40, h * 2 - 100);


    QBrush back_brush(QColor(255, 243, 240)); //bricks & box
   //QBrush back_brush(QColor(224, 255, 224)); //forest

    scene->setBackgroundBrush(back_brush);

  //  scene->addLine(-w, -h + 75, w, -h + 75, QPen(Qt::black));//upper bound
    //scene->addLine(-w, h, w, h, QPen(Qt::black));//lower bound
    //scene->addLine(-w, -h + 75, -w, h, QPen(Qt::black));//left bound
    //scene->addLine(w, -h + 75, w, h, QPen(Qt::black));//right bo


    //makes focuable
    tank-> setFlag(QGraphicsItem::ItemIsFocusable);
    tank->setFocus();
    //Play music
    QMediaPlayer music;
    QAudioOutput audioPlayer;
    audioPlayer.setVolume(.05);
    music.setAudioOutput(&audioPlayer);
    music.setSource(QUrl("qrc:/sounds/backgroundMusic.mp3"));
    music.play();

    view->show();
    view->setFixedSize(1200, 900);
    scene->setSceneRect(0, 0, 1200, 900);
    
    tank->setPos(view->width() / 2 -50, view->height() - 50);
    // spawn enemies
    QTimer* timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), tank, SLOT(spawn()));
    timer->start(2000);

    return a.exec();

}
