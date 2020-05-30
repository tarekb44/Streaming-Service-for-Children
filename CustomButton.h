#ifndef CW2_CUSTOMBUTTON_H
#define CW2_CUSTOMBUTTON_H
#include <QtWidgets/QPushButton>
class QPushButton;
class CustomButton: public QPushButton {
public:
    CustomButton();
    CustomButton(const QString &, int, int);
    void addIcon(const QString , int, int);
};


#endif //CW2_CUSTOMBUTTON_H
