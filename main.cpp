#include <QtGui/QApplication>
#include "midi_seq.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MIDI_SEQ w;
    w.show();
    return a.exec();
}
