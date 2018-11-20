#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QKeyEvent>
#include <QKeySequence>
#include <QString>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->filePath->setText(QString::fromUtf8(shepherd.fm.path().c_str()));
    ui->bufferWindow->setReadOnly(true);
    ui->bufferWindow->setText(QString::fromUtf8(shepherd.buf().c_str()));
    ui->statusBar->showMessage("currentWindow : " + QString::number(shepherd.win()) +
                            " numberOfWin : " + QString::number(shepherd.number_of_win()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::
add_modifier_to_key(QKeyEvent *key_event) {
    int key=key_event->key();
    if(key_event->modifiers() & Qt::ControlModifier) {
        key += Qt::CTRL;
    }
    if(key_event->modifiers() & Qt::ShiftModifier) {
        key += Qt::SHIFT;
    }
    if(key_event->modifiers() & Qt::AltModifier) {
        key += Qt::ALT;
    }
    if(key_event->modifiers() & Qt::MetaModifier) {
        key += Qt::META;
    }
    return key;
}

void MainWindow::change_window() {
    ui->filePath->setText(QString::fromUtf8(shepherd.file_path().c_str()));
    ui->bufferWindow->setText(QString::fromUtf8(shepherd.buf().c_str()));
}

void MainWindow::keyPressEvent(QKeyEvent *key_event) {
    if(key_event->type() == QKeyEvent::KeyPress) {
        int key=add_modifier_to_key(key_event);
        if(QKeySequence(key)==QKeySequence(Qt::CTRL + Qt::Key_T)) {
            if(shepherd.mode()==1) {
                shepherd.set_window(ui->bufferWindow->toPlainText().toUtf8().constData());
                shepherd.create_win();
                change_window();
            }
        }
        if(QKeySequence(key)==QKeySequence(Qt::CTRL + Qt::Key_W)) {
            if(shepherd.mode()==1) {
                shepherd.delete_curwin();
                ui->bufferWindow->setText(QString::fromUtf8(shepherd.buf().c_str()));
            }
        }
        if(QKeySequence(key)==QKeySequence(Qt::CTRL + Qt::Key_Q)) {
            if(shepherd.mode()==1) {
                shepherd.set_window(ui->bufferWindow->toPlainText().toUtf8().constData());
                if(shepherd.change_win(shepherd.win()-1)) {
                    change_window();
                }
            }
        }
        if(QKeySequence(key)==QKeySequence(Qt::CTRL + Qt::Key_E)) {
            if(shepherd.mode()==SHEPHERD_W_MODE) {
                shepherd.set_window(ui->bufferWindow->toPlainText().toUtf8().constData());
                if(shepherd.change_win(shepherd.win()+1)) {
                    change_window();
                }
            }
        }
        if(QKeySequence(key)==QKeySequence(Qt::CTRL + Qt::Key_S)) {
            if(shepherd.mode()==SHEPHERD_W_MODE) {
                shepherd.set_window(ui->bufferWindow->toPlainText().toUtf8().constData());
                shepherd.write_cur_window();
            }
        }
        if(QKeySequence(key)==QKeySequence(Qt::CTRL + Qt::Key_Space)) {
            on_saveOrGoto_clicked();
        }
        if(QKeySequence(key)==QKeySequence(Qt::CTRL + Qt::Key_F1)) {
            shepherd.change_mode(SHEPHERD_FM_MODE);
            ui->filePath->setText(QString::fromUtf8(shepherd.file_path().c_str()));
            ui->bufferWindow->setReadOnly(true);
            ui->bufferWindow->setText(QString::fromUtf8(shepherd.buf().c_str()));
        }
        if(QKeySequence(key)==QKeySequence(Qt::CTRL + Qt::Key_F2)) {
            shepherd.change_mode(SHEPHERD_W_MODE);
            ui->filePath->setText(QString::fromUtf8(shepherd.file_path().c_str()));
            ui->bufferWindow->setReadOnly(false);
            ui->bufferWindow->ensureCursorVisible();
            ui->bufferWindow->setText(QString::fromUtf8(shepherd.buf().c_str()));
        }
        if(QKeySequence(key)==QKeySequence(Qt::CTRL + Qt::Key_F12)) {
            qApp->exit();
        }
    }
}

void MainWindow::on_bufferWindow_textChanged()
{
    ui->statusBar->showMessage("currentWindow : " + QString::number(shepherd.win()) +
                            " numberOfWin : " + QString::number(shepherd.number_of_win()));
}

void MainWindow::on_saveOrGoto_clicked()
{
    shepherd.change_file_path(ui->filePath->text().toUtf8().constData());
    if(shepherd.mode()==SHEPHERD_FM_MODE) {
        ui->bufferWindow->setText(QString::fromUtf8(shepherd.buf().c_str()));
    }
}
