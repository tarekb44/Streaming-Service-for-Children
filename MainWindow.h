#ifndef CW2_MAINWINDOW_H
#define CW2_MAINWINDOW_H

#include <vector>
#include <iostream>
#include "the_player.h"

using namespace std;
// forward-declare Qt classes
class QWidget;
class QPushButton;
class CustomButton;
class QLineEdit;
class QScrollArea;
class QGroupBox;
class Button;
class QLabel;
class QBoxLayout;
class TheButton;
class TheButtonInfo;
class ThePlayer;


class MainWindow: public QWidget {
public:
    QVBoxLayout* indexLayout;
    QVBoxLayout* playerLayout;
    QVBoxLayout* bodyLayout;
    QBoxLayout* indexBodyLayout;
    QBoxLayout* playerBodylayout;
    MainWindow();
    void createBody();


    void createHeader(QVBoxLayout *main);
    void createVideos( vector<TheButtonInfo> videos );
    void createPlayerWindow(vector<TheButtonInfo> videos);
    void createSlider(QLayout *, ThePlayer *);
    void createLabel(QLabel *label, string name, QLayout *layout, int fontSize);
    void createScrollBar(QWidget *, QLayout *);
    void removeBody( QLayout* );



private:
    // Layouts

    // Custom Buttons
    CustomButton* logo;
    CustomButton* movies;
    CustomButton* tvShows;
    CustomButton* search;
    CustomButton* user;
    CustomButton* ac;
    CustomButton* ad;
    CustomButton* cm;
    CustomButton* dr;
    CustomButton* hor;
    CustomButton* sm;

    QLabel* movieLabel;
    QLabel* action;

    QLineEdit * searchField;

    QScrollArea* scrollBar;
    QWidget *line;

    vector<TheButton*> buttons;

    void initialiseLayout( QLayout * );
    void addBlock( QLayout * );
    void addBlock( QLayout *, int );
    void createButtons();
    void createFields();
    void createLabels();
    void drawLine();
    void addStylesheet();
    void videoPlayer(vector<TheButtonInfo> videos, QLayout *);






};


#endif //CW2_MAINWINDOW_H
