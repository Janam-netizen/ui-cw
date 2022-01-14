//    ______
//   /_  __/___  ____ ___  ___  ____
//    / / / __ \/ __ `__ \/ _ \/ __ \
//   / / / /_/ / / / / / /  __/ /_/ /
//  /_/  \____/_/ /_/ /_/\___/\____/
//              video for sports enthusiasts...
//
//  2811 cw3 : twak 11/11/2021
//
#include <iostream>
#include <QApplication>
#include <QtMultimediaWidgets/QVideoWidget>
#include <QMediaPlaylist>
#include <string>
#include <vector>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QHBoxLayout>
#include <QtCore/QFileInfo>
#include <QtWidgets/QFileIconProvider>
#include <QDesktopServices>
#include <QImageReader>
#include <QMessageBox>
#include <QtCore/QDir>
#include <QtCore/QDirIterator>
#include "the_player.h"
#include "the_button.h"
#include <QScrollArea>
#include <QGroupBox>
#include "multimedia.h"

// read in videos and thumbnails to this directory
std::vector<TheButtonInfo> getInfoIn (std::string loc) {

    std::vector<TheButtonInfo> out =  std::vector<TheButtonInfo>();
    QDir dir(QString::fromStdString(loc) );
    QDirIterator it(dir);

    while (it.hasNext()) { // for all files

        QString f = it.next();

            if (f.contains("."))

#if defined(_WIN32)
            if (f.contains(".wmv"))  { // windows
#else
            if (f.contains(".mp4") || f.contains("MOV"))  { // mac/linux
#endif

            QString thumb = f.left( f .length() - 4) +".png";
            if (QFile(thumb).exists()) { // if a png thumbnail exists
                QImageReader *imageReader = new QImageReader(thumb);
                    QImage sprite = imageReader->read(); // read the thumbnail
                    if (!sprite.isNull()) {
                        QIcon* ico = new QIcon(QPixmap::fromImage(sprite)); // voodoo to create an icon for the button
                        QUrl* url = new QUrl(QUrl::fromLocalFile( f )); // convert the file location to a generic url
                        out . push_back(TheButtonInfo( url , ico  ) ); // add to the output list
                    }
                    else
                        qDebug() << "warning: skipping video because I couldn't process thumbnail " << thumb << endl;
            }
            else
                qDebug() << "warning: skipping video because I couldn't find thumbnail " << thumb << endl;
        }
    }

    return out;
}


int main(int argc, char *argv[]) {

    // let's just check that Qt is operational first
    qDebug() << "Qt version: " << QT_VERSION_STR << endl;

    QApplication app(argc, argv);

    // collect all the videos in the folder
    std::vector<TheButtonInfo> videos;

    if (argc == 2)
        videos = getInfoIn( std::string(argv[1]) );

    if (videos.size() == 0) {

        const int result = QMessageBox::question(
                    NULL,
                    QString("Tomeo"),
                    QString("no videos found! download, unzip, and add command line argument to \"quoted\" file location. Download videos from Tom's OneDrive?"),
                    QMessageBox::Yes |
                    QMessageBox::No );

        switch( result )
        {
        case QMessageBox::Yes:
          QDesktopServices::openUrl(QUrl("https://leeds365-my.sharepoint.com/:u:/g/personal/scstke_leeds_ac_uk/EcGntcL-K3JOiaZF4T_uaA4BHn6USbq2E55kF_BTfdpPag?e=n1qfuN"));
          break;
        default:
            break;
        }
        exit(-1);
    }

    // Contains the video player and the multimedia controls



//-----SCROLL AREA (PREVIEW-PANE)

    Multimedia* multimedia = new Multimedia();


   std::cout<< multimedia->isWindow();
    // create the Qt Application
    // a row of buttons
    QWidget *buttonWidget = new QWidget();
    QVBoxLayout *layout=new QVBoxLayout();
    buttonWidget->setLayout(layout);

    // a list of the buttons
    std::vector<TheButton*> buttons;
    // the buttons are arranged horizontally

    QWidget * previewWidget=new QWidget();
    QGridLayout *preview_layout = new QGridLayout();

    previewWidget->setLayout(preview_layout);

    QScrollArea * area=new QScrollArea(buttonWidget);
    area->setWidget(previewWidget);

    //Make connnections b/w buttons and the player

    for (size_t i = 0; i < videos.size(); ++i) {
        TheButton *button = new TheButton(buttonWidget);
        // when clicked, tell the player to load.
        button->connect(button, SIGNAL(jumpTo(TheButtonInfo* )), multimedia->player, SLOT (jumpTo(TheButtonInfo*)));

        buttons.push_back(button);
        preview_layout->addWidget(button,int(i/2),(i%2));
        button->init(&videos.at(i));
    }

    area->setWidgetResizable(true);
    area->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    // Add Load Folder Button
    QPushButton* load_button = new QPushButton("Load Folder");

    layout->addWidget(area);
    layout->addWidget(load_button);

    // tell the player what buttons and videos are available
    multimedia->player->setContent(&buttons, & videos);


    for (size_t i = 0; i < buttons.size(); ++i) {
        // when clicked, tell the player to load.
        //button->connect(button, SIGNAL(jumpTo(TheButtonInfo* )), multimedia->player, SLOT (jumpTo(TheButtonInfo*)));
        buttons.at(int(i))->connect(buttons.at(int(i)), SIGNAL(mark_button(TheButton*)), multimedia->player, SLOT (mark_button(TheButton*)));




    }

    // Main layout
    QHBoxLayout *base = new QHBoxLayout();
    base->addWidget(multimedia);
    base->addWidget(buttonWidget);

    QWidget window;
    window.setLayout(base);
    window.setWindowTitle("tomeo");
    window.setMinimumSize(800, 680);

    // showtime!
    window.show();

    // wait for the app to terminate
    return app.exec();
}
