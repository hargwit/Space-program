#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QTimer>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <QString>
#include <QStringListModel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    fFrameRate(60),
    fWidth(600),
    fHeight(450),
    fStatus(kIdle)
{

    setupSystem();
    setupGui();

    //Start a new timer and attach it to this window
    QTimer *timer = new QTimer(this);
    //Connect the timeout signal from the timer to the simulate slot
    connect(timer, SIGNAL(timeout()), this, SLOT(simulate()));
    //Connect the timeout signal from the timer to the BounceWidget update slot
    connect(timer, SIGNAL(timeout()), ui->spaceWidget, SLOT(update()));
    //Set the timeout time based on the frame rate
    timer->start(1000/fFrameRate);
}

void MainWindow::setupSystem(){
    fSystem=new CelestialSystem();

    //Gravitational constant
    double G =4.0*M_PI*M_PI;

    //Jupiter orbit information
    double rJ=5.2;
    double tJ=sqrt(pow(rJ,3));
    double omegaJ=(2.0*M_PI)/tJ;
    double vJ=omegaJ*rJ;

    //Saturn orbit information
    double rSa=9.5;
    double tSa=sqrt(pow(rSa,3));
    double omegaSa=(2.0*M_PI)/tSa;
    double vSa=omegaSa*rSa;

    //Uranus orbit information
    double rU=19.2;
    double tU=sqrt(pow(rU,3));
    double omegaU=(2.0*M_PI)/tU;
    double vU=omegaU*rU;

    //Neptune orbit information
    double rN=30.0;
    double tN=sqrt(pow(rN,3));
    double omegaN=(2.0*M_PI)/tN;
    double vN=omegaN*rN;

    //Pluto orbit information
    double rP=39.4;
    double tP=sqrt(pow(rP,3));
    double omegaP=(2.0*M_PI)/tP;
    double vP=omegaP*rP;

    //Satellite orbit information
    double rSMA=(rJ+1.0)/2.0;
    double tS=2*M_PI*sqrt(pow(rSMA,3.0)/(G));
    double vS=sqrt(G*(2-(1/rSMA)));

    //Starting Angles
    //double thetaJ=(omegaJ*tS/2.0);
    double thetaJ=1.401;
    double thetaSa=-0.01;
    double thetaU=-M_PI/4;
    double thetaN=-M_PI/2;
    double thetaP=-M_PI;

    //sun already exists
    Body* Jupiter=new Body(9.545838572E-4,TwoVector(-rJ*cos(thetaJ),rJ*sin(thetaJ)),TwoVector(-vJ*sin(thetaJ),-vJ*cos(thetaJ)),"/Users/hargwit/Documents/C++ Projects/SpaceProgram/jupiter.png");
    Body* Saturn=new Body(2.858134272E-4,TwoVector(-rSa*cos(thetaSa),rSa*sin(thetaSa)),TwoVector(-vSa*sin(thetaSa),-vSa*cos(thetaSa)),"/Users/hargwit/Documents/C++ Projects/SpaceProgram/saturn.png");
    Body* Uranus=new Body(4.36575308E-5,TwoVector(-rU*cos(thetaU),rU*sin(thetaU)),TwoVector(-vU*sin(thetaU),-vU*cos(thetaU)),"/Users/hargwit/Documents/C++ Projects/SpaceProgram/uranus.png");
    Body* Neptune=new Body(5.150264018E-5,TwoVector(-rN*cos(thetaN),rN*sin(thetaN)),TwoVector(-vN*sin(thetaN),-vN*cos(thetaN)),"/Users/hargwit/Documents/C++ Projects/SpaceProgram/neptune.png");
    Body* Pluto=new Body(5.150264018E-5,TwoVector(-rP*cos(thetaP),rP*sin(thetaP)),TwoVector(-vP*sin(thetaP),-vP*cos(thetaP)),"/Users/hargwit/Documents/C++ Projects/SpaceProgram/pluto.png");
    Body* Satellite=new Body(0,TwoVector(1,0),TwoVector(0,vS),"/Users/hargwit/Documents/C++ Projects/SpaceProgram/alien.png");

    std::vector<Body *> bodies;
    bodies.push_back(Jupiter);
    //bodies.push_back(Saturn);
    //bodies.push_back(Uranus);
    //bodies.push_back(Neptune);
    //bodies.push_back(Pluto);
    bodies.push_back(Satellite);

    fSystem->setBodies(bodies);
}

void MainWindow::setupGui(){
    //Match the gui window to this object
    ui->setupUi(this);
    //Set title of the window
    setWindowTitle("Withers Space Program");

    //Set the color of the start button
    ui->startButton->setStyleSheet("background-color:green");

    //Set the box, width and height belonging to the bounce widget
    ui->spaceWidget->setSystem(fSystem);
    ui->spaceWidget->setFixedSize(fWidth,fHeight);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete fSystem;
}

void MainWindow::simulate(){
    //If running
    if(fStatus==kRun){
        fSystem->simulate();

    }
}

void MainWindow::on_startButton_clicked()
{
    //if the status was idle then start
    if(fStatus==kIdle){
        //Change start button color and text
        ui->startButton->setStyleSheet("background-color:red");
        ui->startButton->setText("Stop");
        //Set status to run
        fStatus=kRun;
    }
    //else if the status was run then stop
    else if(fStatus==kRun){
        //Set color and text of start button
        ui->startButton->setStyleSheet("background-color:green");
        ui->startButton->setText("Start");
        //Set status to idle
        fStatus=kIdle;
    }
}
