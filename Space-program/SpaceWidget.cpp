#include "SpaceWidget.h"
#include "Body.h"

#include <QPainter>
#include <iostream>
#include <QString>
#include <string>

SpaceWidget::SpaceWidget(QWidget *parent):
    QWidget(parent){
}

SpaceWidget::~SpaceWidget(){}

void SpaceWidget::paintEvent(QPaintEvent *event){
    //Set the painter to this Widget
    QPainter painter(this);
    //Set the background color
    QColor background(0,0,0);
    //Draw over the last image with a rectangle to clear
    painter.fillRect(QRect(0, 0, width(), height()),background);
    //Set ball color
    QColor planetColor(255,255,255);
    int radius=1;

    TwoVector position;
    Body* body;
    QImage image;
    //Loop through every ball in the box
    for(int i=0;i<fSystem->getBodies().size();i++){
        //Set brush color
        painter.setBrush(planetColor);
        //Set pen color
        painter.setPen(planetColor);

        body=fSystem->getBodies()[i];

        image=*(body->getImage());
        //get position
        position=body->getPosition();

        double scaleX=width()/30;
        double scaleY=height()/20;
        int x=position.getX()*scaleX+width()/2;
        int y=-position.getY()*scaleY+height()/2;

        int size=10;
        double sc = (size)/((double)(image.width()));
        painter.drawImage(QRect(x-size,y-sc*image.height(),2*size,2*sc*image.height()),image);
        //Convert to gui co-ordinates and draw circle
        //painter.drawEllipse(x-radius,y-radius,2*radius,2*radius);
    }

    image=QImage("/Users/hargwit/Documents/C++ Projects/SpaceProgram/sun.png");
    int size=10;
    double sc = (size)/((double)(image.width()));
    painter.drawImage(QRect(width()/2-size,height()/2-sc*image.height(),2*size,2*sc*image.height()),image);

}
