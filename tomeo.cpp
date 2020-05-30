/*
 *
 *    ______
 *   /_  __/___  ____ ___  ___  ____
 *    / / / __ \/ __ `__ \/ _ \/ __ \
 *   / / / /_/ / / / / / /  __/ /_/ /
 *  /_/  \____/_/ /_/ /_/\___/\____/
 *              video for children streaming
 *
 * 2811 cw2 November 2019 by Tarek Bessalah
 */

#include <iostream>
#include <QApplication>
#include <QtMultimediaWidgets/QVideoWidget>
#include <QMediaPlaylist>
#include <string>
#include <vector>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtCore/QFileInfo>
#include <QtWidgets/QFileIconProvider>
#include <QImageReader>
#include <QtCore/QDir>
#include <QtCore/QDirIterator>
#include <QtWidgets/QSlider>
#include "the_player.h"
#include "the_button.h"
#include "MainWindow.h"
#include "CustomButton.h"

using namespace std;

// read in videos and thumbnails to this directory
vector<TheButtonInfo> getInfoIn (string loc) {

    vector<TheButtonInfo> out =  vector<TheButtonInfo>();
    QDir dir(QString::fromStdString(loc) );
    QDirIterator it(dir);

    while (it.hasNext()) { // for all files

        QString f = it.next();

        if (!f.contains(".png")) { // if it isn't an image
            QString thumb = f.left( f .length() - 4) +".png";
            if (QFile(thumb).exists()) { // but a png thumbnail exists
                QImageReader *imageReader = new QImageReader(thumb);
                QImage sprite = imageReader->read(); // read the thumbnail
                if (!sprite.isNull()) {
                    QIcon* ico = new QIcon(QPixmap::fromImage(sprite)); // voodoo to create an icon for the button
                    QUrl* url = new QUrl(QUrl::fromLocalFile( f )); // convert the file location to a generic url
                    out . push_back(TheButtonInfo( url , ico  ) ); // add to the output list
                }
                else
                    cerr << "warning: skipping video because I couldn't process thumbnail " << thumb.toStdString() << endl;
            }
            else
                cerr << "warning: skipping video because I couldn't find thumbnail " << thumb.toStdString() << endl;
        }
    }

    return out;
}

int main(int argc, char *argv[]) {

    // let's just check that Qt is operational first
    cout << "Qt version: " << QT_VERSION_STR << endl;

    // create the Qt Application
    QApplication app(argc, argv);

    // collect all the videos in the folder

    vector<TheButtonInfo> videos;

    if (argc == 1)
        videos = getInfoIn(  "/home/csunix/sc18h2r/Desktop/cw2/2811_videos");
    else
        videos = getInfoIn( "/home/csunix/sc18h2r/Desktop/cw2/2811_videos" );

    if (videos.size() == 0) {
        cerr << "no videos found! download from https://vcg.leeds.ac.uk/wp-content/static/2811/the/videos.zip into /tmp/XXX, and update the code on line 77";
        exit(-1);
    }

    MainWindow *window = new MainWindow;
    window->createHeader(window->playerLayout);
    // the widget that will show the video
    QVideoWidget *videoWidget = new QVideoWidget;

    // the QMediaPlayer which controls the playback
    ThePlayer *player = new ThePlayer;
    player->setVideoOutput(videoWidget);

    // a row of buttons
    QWidget *buttonWidget = new QWidget();
    // a list of the buttons
    vector<TheButton*> buttons;
    // the buttons are arranged horizontally
    QGridLayout *layout = new QGridLayout();
    buttonWidget->setLayout(layout);

    // video titles
    vector<string> videoTitles;
    videoTitles.push_back("Plankton • Episode 1");
    videoTitles.push_back("Plankton • Episode 2");
    videoTitles.push_back("Simpsons • Episode 1");
    videoTitles.push_back("Plankton • Episode 5");
    videoTitles.push_back("Spongebob • Episode 5");
    videoTitles.push_back("Patrick • Episode 6");
    videoTitles.push_back("Cindy • Episode 7");

    vector<string> labels;
    labels.push_back("Watch again");
    labels.push_back("Favourite");
    labels.push_back("Favourite");
    labels.push_back("Favourite");
    labels.push_back("Recommended");
    labels.push_back("Recommended");
    labels.push_back("Recommended");
    labels.push_back("Favourite");

    // create the four buttons
    int j = 1, k = 0;
    for ( int i = 0; i < 7; i++ ) {
        if(i%3==0){
            k=0;
            j += 2;
            window->createLabel(new QLabel(), labels[i], layout, 14);
        }
        TheButton *button = new TheButton(buttonWidget);
        QVBoxLayout *container = new QVBoxLayout;
        button->connect(button, SIGNAL(jumpTo(TheButtonInfo* )), player, SLOT (jumpTo(TheButtonInfo* ))); // when clicked, tell the player to play.
        buttons.push_back(button);
        container->addWidget(button);
        window->createLabel(new QLabel, videoTitles[i], container, 10);
        layout->addLayout(container,j,k);
        button->init(&videos.at(i));
        k++;

    }

    // tell the player what buttons and videos are available
    player->setContent(&buttons, & videos);

    // create the main window and layout
    QVBoxLayout *top = new QVBoxLayout();
    top->addWidget(videoWidget);
    window->createSlider(top, player);
    top->addWidget(buttonWidget);

    // add the video and the buttons to the top level widget
    window->createHeader(window->indexLayout);
    window->indexLayout->addLayout(top);
    window->setLayout(window->indexLayout);
    window->createScrollBar(buttonWidget, layout);
    // showtime!
    window->show();

    // wait for the app to terminate
    return app.exec();
}

