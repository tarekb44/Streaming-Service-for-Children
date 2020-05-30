#include <QtWidgets>
#include <QtMultimediaWidgets/QVideoWidget>
#include <QMediaPlaylist>
#include "MainWindow.h"
#include "CustomButton.h"
#include "the_button.h"
#include "the_player.h"
#include <iostream>
#include <string>
using namespace std;

MainWindow::MainWindow() {
    setWindowTitle("Tomeo");;
    setFixedSize(703,1024);
    indexLayout = new QVBoxLayout();
    playerLayout = new QVBoxLayout();
    //initialiseLayout(mainLayout);
    addStylesheet();
    createButtons();
    createFields();
    createLabels();

    //setLayout(mainLayout);
}

void MainWindow::initialiseLayout( QLayout *layout ) {
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);
}

// Creates an empty block
void MainWindow::addBlock( QLayout *layout ) {
    QPushButton *block = new QPushButton;
    block->setFlat(true);
    block->setDisabled(true);
    layout->addWidget(block);
}

// Creates n empty blocks
void MainWindow::addBlock( QLayout *layout, int size ) {
    for ( int i = 0; i < size; i++ ) {
        QPushButton *block = new QPushButton;
        block->setFlat(true);
        block->setDisabled(true);
        layout->addWidget(block);
    }
}

// adding an external stylesheet to the project
void MainWindow::addStylesheet() {
    QFile file("/home/csunix/sc18h2r/Desktop/cw2/static/qss/main.qss");
    if(!file.exists()) {
        exit(0);
    }
    file.open(QFile::ReadOnly);
    QString stylesheet = QLatin1String(file.readAll());
    setStyleSheet(stylesheet);
}

void MainWindow::createLabel(QLabel *label, string name, QLayout *layout, int fontSize) {
    label->setText(QString::fromStdString(name));
    label->setStyleSheet("font:" + QString::number(fontSize) + "pt; font-weight:bold;");
    layout->addWidget(label);
}

// Creates icons as buttons for the app
void MainWindow::createButtons() {
    logo = new CustomButton("Tomeo",100,100);
    //movies = new CustomButton("Movies",100,100);
    //tvShows = new CustomButton("TV Shows",100,100);
    user = new CustomButton("User",100,100);
    search =  new CustomButton("Search",50,50);
    ac =  new CustomButton("Search",100,100);
    ad =  new CustomButton("Search",100,100);
    cm =  new CustomButton("Search",100,100);
    dr =  new CustomButton("Search",100,100);
    hor =  new CustomButton("Search",100,100);
    sm =  new CustomButton("Search",100,100);



    logo->addIcon("logo.png", 100,100);
    //movies->addIcon("movie.png", 100,100);
    //tvShows->addIcon("tv-shows.png", 100,100);
    user->addIcon("user.png", 100,100);
    search->addIcon("search.png", 50,50);
    ac->addIcon("search.png", 100,100);
    ad->addIcon("search.png", 100,100);
    cm->addIcon("search.png", 100,100);
    dr->addIcon("search.png", 100,100);
    hor->addIcon("search.png", 100,100);
    sm->addIcon("search.png", 100,100);
}

void MainWindow::createFields() {
    searchField =  new QLineEdit();

    searchField->setPlaceholderText("Search");
}

void MainWindow::createLabels() {
    action = new QLabel();
    action->setText("Action");

    QHBoxLayout *horizonalLine = new QHBoxLayout;
    CustomButton *button = new CustomButton("A", 650,30);
    button->addIcon("arrow.png",20,20);
    button->setStyleSheet("Text-align:left");
    button->setDisabled(true);
    movieLabel = new QLabel();
    movieLabel->setText("Watch Again");
    horizonalLine->addWidget(movieLabel);
    horizonalLine->addWidget(button);
    //mainLayout->addLayout(horizonalLine);
}

// Creates Header
void MainWindow::createHeader( QVBoxLayout *main) {
    QVBoxLayout *headerLayout = new QVBoxLayout;
    initialiseLayout(headerLayout);
    QHBoxLayout *childOne = new QHBoxLayout;
    QHBoxLayout *childTwo = new QHBoxLayout;
    childOne->addWidget(logo);
    addBlock(childOne,1);
    childOne->addWidget(searchField);
    childOne->addWidget(search);
    addBlock(childOne,1);
    childOne->addWidget(user);

    //childTwo->addWidget(movies);
    //childTwo->addWidget(tvShows);
    //childTwo->addWidget(ac);
    QVBoxLayout *icon = new QVBoxLayout;
    icon->addWidget(ac);
    icon->addWidget(action);
    childTwo->addLayout(icon);
    childTwo->addWidget(ad);
    childTwo->addWidget(cm);
    childTwo->addWidget(dr);
    childTwo->addWidget(hor);
    childTwo->addWidget(sm);

    headerLayout->addLayout(childOne);
    drawLine();
    headerLayout->addWidget(line);
    //headerLayout->addLayout(childTwo);

    main->addLayout(headerLayout);

    QObject::connect(logo, SIGNAL(clicked()), playerLayout, SLOT(removeBody(indexLayout)));

}

// Draws a horizontal line
void MainWindow::drawLine() {
    line = new QWidget;
    line->setFixedHeight(2);
    line->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    line->setStyleSheet(QString("background-color: #c0c0c0;"));
}

void MainWindow::createVideos(vector<TheButtonInfo> videos) {
    QWidget *buttonWidget = new QWidget();
    for ( int i = 0; i < videos.size(); i++ ) {
        TheButton *button = new TheButton(buttonWidget);
        //button->connect(button, SIGNAL(jumpTo(TheButtonInfo* )), player, SLOT (jumpTo(TheButtonInfo* ))); // when clicked, tell the player to play.
        buttons.push_back(button);
        //layout->addWidget(button);
        button->init(&videos.at(i));
    }
}

void MainWindow::createBody() {
    QWidget *buttonWidget = new QWidget();
    QGridLayout *grid = new QGridLayout;
    //QHBoxLayout *layout = new QHBoxLayout();
    buttonWidget->setLayout(grid);
    int j = 0; int k = 0;
    for( int i=0;i<buttons.size();i++){
        if(i%2==0){
            j++;
            k = 0;
        }
        //grid->addWidget(buttons[i],j,k);
        k++;
    }

    indexLayout->addWidget(buttonWidget);
}

void MainWindow::videoPlayer(vector<TheButtonInfo> videos, QLayout *layout) {
    QVideoWidget *videoWidget = new QVideoWidget;
    ThePlayer *player = new ThePlayer;
    player->setVideoOutput(videoWidget);

    player->setContent(&buttons,&videos);
    layout->addWidget(videoWidget);

}

void MainWindow::createPlayerWindow(vector<TheButtonInfo> videos){
    QHBoxLayout* parentLayout = new QHBoxLayout();
    QVBoxLayout* rightLayout = new QVBoxLayout();
    QVBoxLayout* leftLayout = new QVBoxLayout();

    for( int i=0;i<buttons.size();i++){
        leftLayout->addWidget(buttons[i]);
    }

    parentLayout->addLayout(rightLayout,70);
    parentLayout->addLayout(leftLayout,30);
    rightLayout->addStretch();
    leftLayout->addStretch();
    indexLayout->addLayout(parentLayout);
}

void MainWindow::createSlider(QLayout * layout, ThePlayer* p ) {
/*
    QTimer *timer = new QTimer;
    timer->start(0);
    QSlider *slider = new QSlider(Qt::Horizontal);*/
    QSlider *volume = new QSlider(Qt::Horizontal);
    CustomButton *playButton = new CustomButton("play",60,60);
    CustomButton *puaseButton = new CustomButton("pause",60,60);
    CustomButton *replayButton = new CustomButton("pause",60,60);
    CustomButton *volumeIcon = new CustomButton("volume",60,50);
    volumeIcon->addIcon("volume.png",30,30);
    playButton->addIcon("play.png", 50,50);
    replayButton->addIcon("replay.png", 50,50);
    puaseButton->addIcon("pause.png", 50,50);


    QVBoxLayout *container = new QVBoxLayout;
    QHBoxLayout *rowOne = new QHBoxLayout;

    rowOne->addWidget(playButton,5);
    rowOne->addWidget(puaseButton,5);
    rowOne->addWidget(replayButton,5);
    addBlock(rowOne,4);
    //rowOne->addWidget(slider,85);
    addBlock(rowOne);
    //createLabel new QLabel, "00:00:00", rowOne, 12);
    rowOne->addWidget(volumeIcon);
    rowOne->addWidget(volume);
    container->addLayout(rowOne);
    addBlock(container);
    layout->addItem(container);
    QObject::connect(volume, SIGNAL(valueChanged(int)), p, SLOT(setVolume(int)));
    QObject::connect(puaseButton, SIGNAL(clicked()), p, SLOT(pause()));
    QObject::connect(playButton, SIGNAL(clicked()), p, SLOT(play()));
    QObject::connect(replayButton, SIGNAL(clicked()), p, SLOT(stop()));
    QObject::connect(replayButton, SIGNAL(clicked()), p, SLOT(play()));
}

void MainWindow::createScrollBar(QWidget *w, QLayout *scrollAreaContent) {
    QScrollArea *scrollArea = new QScrollArea;
    w->setLayout(scrollAreaContent);
    scrollArea->setWidget(w);
    scrollArea->viewport()->setBackgroundRole(QPalette::Light);
    scrollArea->viewport()->setAutoFillBackground(true);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollArea->setMinimumHeight(350);
    indexLayout->addWidget(scrollArea);

}

void MainWindow::removeBody( QLayout *layout) {
    setLayout(layout);
}