#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_mode1_clicked();

    void on_mode2_clicked();


    void on_inputButton_clicked();

    void on_dis_answer_clicked();

    void on_inputanswer_clicked();



    void on_see_answer_clicked();

    void on_givequestion_clicked();

private:
    Ui::MainWindow *ui;
};


#endif // MAINWINDOW_H
