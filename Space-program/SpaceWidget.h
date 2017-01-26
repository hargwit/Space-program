#ifndef SPACEWIDGET_H
#define SPACEWIDGET_H

#include "QWidget"
#include "QImage"
#include "CelestialSystem.h"

class SpaceWidget : public QWidget
{
    Q_OBJECT
public:
    SpaceWidget(QWidget *parent=0);
    virtual ~SpaceWidget();


    inline CelestialSystem* getSystem();
    inline void setSystem(CelestialSystem * system);

    //Paints on update
    void paintEvent(QPaintEvent *event);

private:
    CelestialSystem * fSystem;

};

inline CelestialSystem* SpaceWidget::getSystem(){return fSystem;}
inline void SpaceWidget::setSystem(CelestialSystem * system){fSystem=system;}

#endif // SPACEWIDGET_H
