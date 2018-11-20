#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "shepherd.hpp"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void keyPressEvent(QKeyEvent *);
    int add_modifier_to_key(QKeyEvent *);
    void change_window();
protected:
    Shepherd shepherd;

private slots:
    void on_bufferWindow_textChanged();
    void on_saveOrGoto_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
