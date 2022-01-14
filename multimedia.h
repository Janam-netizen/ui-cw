#ifndef MULTIMEDIA_H
#define MULTIMEDIA_H

#include <QWidget>
#include <QPushButton>
#include <QVideoWidget>
#include <QSlider>
#include "the_player.h"
#include  "finddialog.h"
#include <iostream>
/// Class that contains the main video player and
/// multimedia control buttons
class Multimedia : public QWidget {
    Q_OBJECT
public:
    Multimedia();
    ThePlayer* player;

private:

       std::vector<QPushButton*>* buttons;

    void create_widgets();
    void arrange_widgets();
    void make_connections();


    QVideoWidget* video;

    // Multimedia Controls

    QPushButton* curr_button;
    QPushButton* play_button;
    QPushButton* pause_button;
    QPushButton* delete_button;

    // Playback Rate Controls
    QPushButton* rate_25;
   QPushButton* rate_50;
   QPushButton* rate_75;
    QPushButton* rate_100;
    
    //Rewind and forward buttons

    QPushButton* fwd;


    QPushButton* bwd;

    QPushButton* exp;
    
    

    QPushButton* fs;








    QSlider* slider;



public slots:
    void setup_slider(qint64 dur) { slider->setRange(0,dur); }
    void change_pos_slider(qint64 val) { slider->setValue(int(val)); }
    void change_pos_player(int val) { player->setPosition(qint64(val)); }

    void change_to_full_screen(){;
       this->showFullScreen();}

    void forward(){player->setPosition(player->position()+qint64(500));}
    void backward(){player->setPosition(player->position()-qint64(500));}

    void show_export_form();
    
    //

    void mark_button(QPushButton*b);

};

#endif // MULTIMEDIA_H
