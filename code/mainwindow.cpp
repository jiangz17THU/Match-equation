#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "string.h"
#include "AI.h"
#include<qDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->mode1->setText("自定义模式");
    ui->mode2->setText("题库模式");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_mode1_clicked()
{
    ui->mode1->setText("开始游戏");
    mode=1;

}

void MainWindow::on_mode2_clicked()
{
    ui->mode2->setText("开始游戏");
    mode=2;
}


void MainWindow::on_inputButton_clicked()
{
    string a ;
    int *num=new int[6];
    char signal;
    QString text = ui->input->text();
    string equation = text.toStdString().c_str();

    signal=(char)equation[2];

    num[0]=(int)equation[0]-48;
    num[1]=(int)equation[1]-48;
    num[2]=(int)equation[3]-48;
    num[3]=(int)equation[4]-48;
    num[4]=(int)equation[6]-48;
    num[5]=(int)equation[7]-48;
    ui->a->display(num[0]);
    ui->b->display(num[1]);
    ui->c->display(num[2]);
    ui->d->display(num[3]);
    ui->e->display(num[4]);
    ui->f->display(num[5]);
    SCANF_SIGNAL=signal;
    if(text[2]!='*')
        ui->sigalchange->setText(QString(text[2]));
    else
        ui->sigalchange->setText("x");
  if(play(num[0],num[1],num[2],num[3],num[4],num[5]))
       a="HAVE A SOLUTION!";
  else
       a="NO ANSWER!" ;


    QString qstr = QString::fromStdString(a);

     ui->attention->setText(qstr);

}

void MainWindow::on_dis_answer_clicked()
{
    ui->sigalchange->setText( QString (QChar(signal_output[0])));

    ui->a->display(output[0]);
    ui->b->display(output[1]);
    ui->c->display(output[2]);
    ui->d->display(output[3]);
    ui->e->display(output[4]);
    ui->f->display(output[5]);
}

int num1, num2, num3, num4, num5, num6, m;
void MainWindow::on_givequestion_clicked()  //出题
{
    char random[3] = { '+','-','x' };

    while (1)
    {
        srand(time(NULL));
        int num = rand() % 1000000;
        m = rand() % 3;
        num1 = num / 100000;
        num2 = (num / 10000) % 10;
        num3 = (num / 1000) % 10;
        num4 = (num / 100) % 10;
        num5 = (num / 10) % 10;
        num6 = num % 10;
        SCANF_SIGNAL = random[m];
        mode=1;
        if (play(num1, num2, num3, num4, num5, num6))
            break;
    }
    ui->a->display(num1);
    ui->b->display(num2);
    ui->c->display(num3);
    ui->d->display(num4);
    ui->e->display(num5);
    ui->f->display(num6);
    ui->sigalchange->setText( QString (QChar(SCANF_SIGNAL)));

}

void MainWindow::on_inputanswer_clicked()
{
            int* num = new int[6];//玩家的答案 数字部分
            char ans_signal;

            QString text = ui->playeranswer->text();
            string equation = text.toStdString().c_str();
            ans_signal=(char)equation[2];

            num[0]=(int)equation[0]-48;
            num[1]=(int)equation[1]-48;
            num[2]=(int)equation[3]-48;
            num[3]=(int)equation[4]-48;
            num[4]=(int)equation[6]-48;
            num[5]=(int)equation[7]-48;


            int correct = 0;
            for (int i = 0; i < 6; i++)
            {
                if (num[i] == output[i])
                    correct++;
            }
            if ((correct == 6) && (ans_signal == checkSignal))
                ui->result->setText("YOU WIN !");
            else
                ui->result->setText("YOU LOSE...");

}



void MainWindow::on_see_answer_clicked()
{
    ui->sigalchange->setText( QString (QChar(signal_output[0])));

    ui->a->display(output[0]);
    ui->b->display(output[1]);
    ui->c->display(output[2]);
    ui->d->display(output[3]);
    ui->e->display(output[4]);
    ui->f->display(output[5]);
}



