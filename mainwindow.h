#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QByteArray>
#include <QTimer>
#include <QFileSystemWatcher>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QString mas;
    QString folder_from;
    QString folder_to;

    bool not_override=false;
    bool add_number=false;
    bool delete_old=false;
    QTimer *timer;

    int mil_sec=0;
    QByteArray byts;


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void set_mask(QString mask);
    void set_folder_from(QString fol);
    void set_folder_to(QString fol);
    void set_byts(QString bi);
    void set_add_number(bool ad);
    void set_not_override(bool over);
    void set_delete_old(bool old);
    void del_list(QStringList &fil);
    void set_timer(QTime t);




    void timer_sig();
    void exe();



private:
    void xor_byte(QByteArray &arr);

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
