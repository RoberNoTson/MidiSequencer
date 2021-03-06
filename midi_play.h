#ifndef MIDI_PLAY_H
#define MIDI_PLAY_H

#include <QtGui>
#include <QMainWindow>
#include <QTimer>
#include <alsa/asoundlib.h>
#include <vector>

namespace Ui {
    class MIDI_PLAY;
}

class MIDI_PLAY : public QMainWindow {
    friend class TIMER_THREAD;

    Q_OBJECT

public:
    MIDI_PLAY(QWidget *parent = 0);
    ~MIDI_PLAY();

protected:

private:
    Ui::MIDI_PLAY *ui;

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

    struct tempo_chg {
      unsigned int tick;
      int new_tempo;
    };

    static snd_seq_t *seq;
    static snd_seq_addr_t *ports;
    static snd_seq_queue_tempo_t *queue_tempo;
    static double song_length_seconds;
    static bool minor_key;
    static int sf;  // sharps/flats
    static double BPM,PPQ;
    static unsigned int event_num;

    int queue;
    std::vector<struct event> all_events;
    std::vector<struct tempo_chg> tempoTable;
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
    void on_progressBar_sliderMoved(int);
    void on_PortBox_currentIndexChanged(QString );
    void on_Pause_button_toggled(bool);
    void on_Play_button_toggled(bool);
    void on_Panic_button_clicked();
    void on_Open_button_clicked();
    void on_MIDI_Tempo_Master_valueChanged(int);
    void on_MIDI_Volume_Master_valueChanged(int);
    void on_MIDI_Exit_button_clicked();
    void on_MIDI_GMGS_button_toggled(bool);
    void on_MIDI_Transpose_valueChanged(int);
    void tickDisplay();
    void on_MIDI_Volume_1_valueChanged(int);
    void on_MIDI_Volume_2_valueChanged(int);
    void on_MIDI_Volume_3_valueChanged(int);
    void on_MIDI_Volume_4_valueChanged(int);
    void on_MIDI_Volume_5_valueChanged(int);
    void on_MIDI_Volume_6_valueChanged(int);
    void on_MIDI_Volume_7_valueChanged(int);
    void on_MIDI_Volume_8_valueChanged(int);
    void on_MIDI_Volume_9_valueChanged(int);
    void on_MIDI_Volume_10_valueChanged(int);
    void on_MIDI_Volume_11_valueChanged(int);
    void on_MIDI_Volume_12_valueChanged(int);
    void on_MIDI_Volume_13_valueChanged(int);
    void on_MIDI_Volume_14_valueChanged(int);
    void on_MIDI_Volume_15_valueChanged(int);
    void on_MIDI_Volume_16_valueChanged(int);
    void on_MIDI_Expression_1_valueChanged(int);
    void on_MIDI_Expression_2_valueChanged(int);
    void on_MIDI_Expression_3_valueChanged(int);
    void on_MIDI_Expression_4_valueChanged(int);
    void on_MIDI_Expression_5_valueChanged(int);
    void on_MIDI_Expression_6_valueChanged(int);
    void on_MIDI_Expression_7_valueChanged(int);
    void on_MIDI_Expression_8_valueChanged(int);
    void on_MIDI_Expression_9_valueChanged(int);
    void on_MIDI_Expression_10_valueChanged(int);
    void on_MIDI_Expression_11_valueChanged(int);
    void on_MIDI_Expression_12_valueChanged(int);
    void on_MIDI_Expression_13_valueChanged(int);
    void on_MIDI_Expression_14_valueChanged(int);
    void on_MIDI_Expression_15_valueChanged(int);
    void on_MIDI_Expression_16_valueChanged(int);
};

#endif // MIDI_PLAY_H
