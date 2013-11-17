#ifndef MIDI_SEQ_H
#define MIDI_SEQ_H

#include <QtGui>
#include <QMainWindow>
#include <QTimer>
#include <alsa/asoundlib.h>
#include <vector>

namespace Ui {
    class MIDI_SEQ;
}

class MIDI_SEQ : public QMainWindow {
    friend class TIMER_THREAD;

    Q_OBJECT

public:
    MIDI_SEQ(QWidget *parent = 0);
    ~MIDI_SEQ();

protected:

private:
    Ui::MIDI_SEQ *ui;

    struct event {
        struct event *next;		// linked list
        unsigned char type;		// SND_SEQ_EVENT_xxx
        unsigned char port;		// port index
        unsigned int tick;
        union {
            unsigned char d[3];	// channel and data bytes
            int tempo;
            unsigned int length;	// length of sysex data
        } data;
        std::vector<unsigned char> sysex;
    };  // end struct event definition

    struct track {
        struct event *first_event;	// list of all events in this track
        int end_tick;			// length of this track
        struct event *current_event;	// used while loading and playing
    };  // end struct track definition

    static snd_seq_t *seq;
    static snd_seq_addr_t *ports;
    static double song_length_seconds;
    static bool minor_key;
    static int sf;  // sharps/flats
    static double BPM,PPQ;
    static unsigned int event_num;

    int queue;
    std::vector<struct event> all_events;
    QTimer *timer;
    inline void check_snd(const char *, int);
    inline int read_id(void);
    inline int read_byte(void);
    inline void skip(int);
    static bool tick_comp(const struct event& e1, const struct event& e2);
    int read_int(int);
    int read_var(void);
    int read_32_le(void);
    int read_smf(char *);
    int read_riff(char *);
    int read_track(int, char *);
    void play_midi(unsigned int);
    void send_CC(char *, int);
    void send_SysEx(char *, int);
    void init_seq();
    void close_seq();
    void connect_port();
    void disconnect_port();
    int parseFile(char *);
    void getPorts(QString buf="");
    void getRawDev(QString buf="");
    void startPlayer(int startTick=0);
    void stopPlayer();

private slots:
    void on_progressBar_sliderReleased();
    void on_progressBar_sliderPressed();
    void on_PortBox_currentIndexChanged(QString );
    void on_Pause_button_toggled(bool);
    void on_Play_button_toggled(bool);
    void on_Panic_button_clicked();
    void on_Open_button_clicked();
    void on_MIDI_Volume_Master_valueChanged(int);
    void on_MIDI_Exit_button_clicked();
    void on_MIDI_GMGS_button_toggled(bool);
    void tickDisplay();
};

#endif // MIDI_SEQ_H
