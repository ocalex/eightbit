#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    byts.resize(8);
    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &MainWindow::exe);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete timer;
}

void MainWindow::set_mask(QString mask){
    mas= "*"+mask+"*";
    qDebug()<< mas;
}
void MainWindow::set_folder_from(QString fol){
    folder_from = fol;
    qDebug()<< folder_from;

}
void MainWindow::set_folder_to(QString fol){

    folder_to  = fol;
    qDebug()<< folder_to;

}
void MainWindow::set_byts(QString bi){

    if(bi.length() == 8){

   byts = bi.toUtf8();
                        }

    qDebug()<< byts;
}

void MainWindow::set_add_number(bool ad){

    add_number = ad;

}
void MainWindow::set_not_override(bool over){

    not_override = over;

}

void MainWindow::set_delete_old(bool old){

    delete_old = old;

}


void MainWindow::exe(){


    QDir directory(folder_from);

    QStringList files = directory.entryList(QStringList() << mas);

    qDebug()<<directory;


    foreach(QString filename, files)            {

        QString temp_from = folder_from +'\\' + filename;
        QString temp_to = folder_to+'\\' + filename;



        if( QFile::exists(temp_to)){
            if(add_number) {

                int number = 1;
                while(QFile::exists(temp_to)){
                temp_to = folder_to +'\\'+QString::number(number) + filename;
                 ++number;
                }

            }

            else if(not_override) continue;

                                    }

        QFile new_file(temp_to);


        QFile file(temp_from);                //открыл файл
      QFileInfo fi(file);
      qDebug()<< fi.lastRead();

         if (!file.open(QIODevice::ReadOnly)){
             qDebug()<<"not open";
             return;
                                             }
           new_file.open(QIODevice::ReadWrite);
           QDataStream out(&new_file);


         while (!file.atEnd()) {
             QByteArray line = file.readLine();
             xor_byte(line);
             qDebug()<<line;

             out << line << '\n';


                                  }



                                                         }

 if(delete_old) del_list(files);
 if(mil_sec) timer_sig();

}
void MainWindow::xor_byte(QByteArray &arr){

    unsigned int s = 0;

        while(s < arr.size()){


           arr[s] = byts[s%8]^arr[s];

            ++s;

}
}



void MainWindow::del_list(QStringList &fil){
    qDebug()<< "I am here delete";

    for (unsigned int i =0; i < fil.size(); ++i){


        QFile::remove(folder_from+"\\"+fil[i]);
        qDebug()<<fil[i];
    }



}
void MainWindow::set_timer(QTime t){

    mil_sec = (-1)*t.msecsTo(QTime(0, 0, 0));
    qDebug()<< mil_sec;

    if(mil_sec) this->timer_sig();

}
void MainWindow::timer_sig(){


    timer->start(mil_sec);

}

