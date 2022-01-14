// Header file for Find dialog (implemented in finddialog.cpp)
// (NDE, 2014-10-27)

#pragma once

#include <QDialog>

class QCheckBox;   // forward reference
class QLabel;
class QLineEdit;
class QPushButton;
class QComboBox;

class FindDialog: public QDialog
{
  Q_OBJECT

  public:
    FindDialog(QWidget* = 0);

  private:
    void createWidgets();
    void arrangeWidgets();
    void makeConnections();

     QLineEdit* title;


    QLineEdit* file_path;
    QComboBox * video_quality;
    QComboBox* play_speed;

    QPushButton* Browse;

    QPushButton *exp;

    public slots:


        void input_dir();




};
