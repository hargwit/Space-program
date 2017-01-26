#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "CelestialSystem.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setupGui();
    void setupSystem();

private slots:
    void simulate();

    void on_startButton_clicked();

private:
    Ui::MainWindow *ui;
    CelestialSystem * fSystem;
    enum{kIdle,kRun};
    int fStatus;
    double fFrameRate;
    int fWidth;
    int fHeight;
};

#endif // MAINWINDOW_H
