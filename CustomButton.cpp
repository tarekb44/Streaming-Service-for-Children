#include "CustomButton.h"

CustomButton::CustomButton() {
    new QPushButton();
    setFlat(true);

}

CustomButton::CustomButton(const QString &name, int w, int h ) {
    new QPushButton(name);
    setFlat(true);
    setFixedSize(w,h);
}

void CustomButton::addIcon( const QString iconName, int w, int h ) {
    QPixmap newIcon("/home/csunix/sc18h2r/Desktop/cw2/static/icons/" + iconName );
    QIcon icon(newIcon);
    setIconSize(QSize(w,h));
    setIcon(icon);
}