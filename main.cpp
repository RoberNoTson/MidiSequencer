#include <QtGui/QApplication>
#include "midi_play.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MIDI_PLAY w;
    w.show();
    return a.exec();
}
