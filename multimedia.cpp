#include "multimedia.h"
#include "the_player.h"

#include <QtWidgets>
#include <iostream>
#include "finddialog.h"


Multimedia::Multimedia()
{
    create_widgets();
    arrange_widgets();
    make_connections();
}

void Multimedia::create_widgets()
{
    video = new QVideoWidget();
    player = new ThePlayer();
    player->setVideoOutput(video);

    play_button = new QPushButton(">");
    pause_button = new QPushButton("||");
    delete_button = new QPushButton("Delete Video");

    rate_25 = new QPushButton();

    rate_50 = new QPushButton();
    rate_75 = new QPushButton();
    rate_100 = new QPushButton();

    rate_25->setText("0.25");
    rate_50->setText("0.50");

    rate_75->setText("0.75");
    rate_100->setText("1");





    fwd=new QPushButton();

    bwd=new QPushButton();

    fs=new QPushButton("Full-screen");





    exp=new QPushButton("Export");



    slider = new QSlider(Qt::Horizontal);







}

void Multimedia::arrange_widgets()
{
    QHBoxLayout* multimedia_controls = new QHBoxLayout();
    multimedia_controls->addWidget(pause_button);
    multimedia_controls->addWidget(play_button);


    multimedia_controls->addWidget(bwd);
    fwd->setText(">>");


    multimedia_controls->addWidget(fwd);
   bwd->setText("<<");


    multimedia_controls->addWidget(fs);


    multimedia_controls->addWidget(exp);


    multimedia_controls->addWidget(delete_button);






    QLabel* rate_label = new QLabel("Playback\nRate");
    rate_label->setFont(QFont("Default", 13));

    rate_label->setAlignment(Qt::AlignCenter);
    rate_label->setScaledContents(true);

    QHBoxLayout* rate_controls = new QHBoxLayout();
    rate_controls->addWidget(rate_label);
    rate_controls->addWidget(rate_25);
    rate_controls->addWidget(rate_50);
    rate_controls->addWidget(rate_75);
    rate_controls->addWidget(rate_100);

    QGridLayout* v_layout = new QGridLayout();
    v_layout->addWidget(video,0,0);
    v_layout->addWidget(slider,1,0);
    v_layout->addLayout(multimedia_controls,2,0);
    v_layout->addLayout(rate_controls, 3, 0);

    v_layout->setRowMinimumHeight(0, 40);
    setLayout(v_layout);
}

void Multimedia::make_connections()
{
    play_button->connect(play_button,SIGNAL(released()),player,SLOT(play()));
    pause_button->connect(pause_button,SIGNAL(released()),player,SLOT(pause()));

    connect(rate_25, &QPushButton::released, [this]() {
        emit player->setPlaybackRate(0.25);

        emit this->mark_button(rate_25);
    });

    connect(rate_50, &QPushButton::released, [this]() {
        emit player->setPlaybackRate(0.50);
        emit this->mark_button(rate_50);
    });

    connect(rate_75, &QPushButton::released, [this]() {
        emit player->setPlaybackRate(0.75);

        emit this->mark_button(rate_75);
    });

    connect(rate_100, &QPushButton::released, [this]() {
        emit player->setPlaybackRate(1.0);

        emit this->mark_button(rate_100);
    });

    player->connect(player,SIGNAL(durationChanged(qint64)),this,SLOT(setup_slider(qint64)));
    player->connect(player,SIGNAL(positionChanged(qint64)),this,SLOT(change_pos_slider(qint64)));

    slider->connect(slider,SIGNAL(sliderMoved(int)),this,SLOT(change_pos_player(int)));
    fwd->connect(fwd,SIGNAL(released()),this,SLOT(forward()));
    bwd->connect(bwd,SIGNAL(released()),this,SLOT(backward()));
    exp->connect(exp,SIGNAL(released()),this,SLOT(show_export_form()));
    fs->connect(fs,SIGNAL(released()),this,SLOT(change_to_full_screen()));
}

void Multimedia::show_export_form()
{

    FindDialog* exp=new FindDialog();


    exp->show();


}


void Multimedia::mark_button(QPushButton* b){

 if(curr_button!=NULL){


   curr_button->setFlat(false);

 }



 curr_button=b;



 curr_button->setFlat(true);





}




