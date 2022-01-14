// Implementation file for Find dialog
// (NDE, 2014-10-27)

#include <QtWidgets>
#include "finddialog.h"
#include <QHBoxLayout>

FindDialog::FindDialog(QWidget* parent): QDialog(parent)
{
  createWidgets();
  arrangeWidgets();
  //makeConnections();

  setWindowTitle("Export");
  setFixedHeight(sizeHint().height());
}


void FindDialog::createWidgets()
{   title=new QLineEdit();
    file_path=new QLineEdit();

    exp=new QPushButton("Export");

    video_quality=new QComboBox();

    video_quality->addItem("High(1080p)");

    video_quality->addItem("Medium(720p)");

    video_quality->addItem("low(540p)");



    Browse=new QPushButton("Browse");

    play_speed=new QComboBox();


    play_speed->addItem("0.25s");

    play_speed->addItem("0.5s");

    play_speed->addItem("0.75s");

    play_speed->addItem("1s");




}


void FindDialog::arrangeWidgets()
{
    QFormLayout *form=new QFormLayout ();

    QHBoxLayout *hlayout=new QHBoxLayout();


    hlayout ->addWidget(file_path);
    hlayout->addWidget(Browse);
    setLayout(form);

    form->addRow("Title",title);

    form->addRow("Quality",video_quality);

    form->addRow("Play-rate:",play_speed);

    form->addRow("Location:",hlayout);

    form->addRow(" ",exp);



}


void FindDialog::makeConnections(){


    Browse->connect(Browse ,SIGNAL(released()),this,SLOT(input_dir()));



}

void FindDialog::input_dir(){

    QFileDialog *dir=new QFileDialog(this);
    //dir->setOption(QFileDialog::DontUseNativeDialog,true);


dir->show();




}





