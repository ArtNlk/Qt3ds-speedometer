#include "speedometercontroller.h"

#include <QDebug>
#include <QVector4D>
#include <QVector3D>
#include <QtGlobal>

SpeedometerController::SpeedometerController(QObject *_parent) :
    QObject(_parent),
    units(KMH),
    isVisible(true),
    speed(0.0),
    maxSpeed(100.0),
    presentation(nullptr)
{

}

void SpeedometerController::setPresentation(Q3DSPresentation *_presentation)
{
    qDebug() << "Presentation loaded";
    if (_presentation == nullptr)
    {
        qDebug() << "presentation is null";
        return;
    }
    presentation = _presentation;
    connect(presentation,&Q3DSPresentation::customSignalEmitted,this,&SpeedometerController::onCustomSignal);
}

void SpeedometerController::leftLayout()
{
    if(!presentation) return;
    presentation->setDataInputValue("CurrentSlide","Left",true);
}

void SpeedometerController::centralLayout()
{
    if(!presentation) return;
    presentation->setDataInputValue("CurrentSlide","Mid",true);
}

void SpeedometerController::rightLayout()
{
    if(!presentation) return;
    presentation->setDataInputValue("CurrentSlide","Right",true);
}

void SpeedometerController::setKmhUnits()
{
    if(this->units == MPH)
    {
        speed = mphToKmh(speed);
        maxSpeed = mphToKmh(maxSpeed);
    }
    units = KMH;

    if(!presentation) return;
    presentation->setAttribute("Scene.Layer.Speedometer.units.units_mat.diffusemap", "sourcepath","qrc:/speedometer/maps/kmh.png");
    presentation->setDataInputValue("SpeedometerColor", QVector4D(0,0,255,255), true);
    presentation->setDataInputValue("TextColor", QVector4D(255,255,255,255), true);
    updateText();
}

void SpeedometerController::setMphUnits()
{
    if(this->units == KMH)
    {
        speed = kmhToMph(speed);
        maxSpeed = kmhToMph(maxSpeed);
    }
    units = MPH;

    if(!presentation) return;
    presentation->setAttribute("Scene.Layer.Speedometer.units.units_mat.diffusemap", "sourcepath","qrc:/speedometer/maps/mph.png");
    presentation->setDataInputValue("SpeedometerColor", QVector4D(255,0,0,255), true);
    presentation->setDataInputValue("TextColor", QVector4D(0,0,0,255), true);
    updateText();
}

void SpeedometerController::setKmhMaxSpeed(double _speed)
{
    if(units == MPH)
    {
        maxSpeed = kmhToMph(_speed);
    }
    else
    {
        maxSpeed = _speed;
    }

    if(!presentation) return;
    updateArrow();
    updateText();
}

void SpeedometerController::setMphMaxSpeed(double _speed)
{
    if(units == KMH)
    {
        maxSpeed = mphToKmh(_speed);
    }
    else
    {
        maxSpeed = _speed;
    }

    if(!presentation) return;
    updateArrow();
    updateText();
}

void SpeedometerController::setKmhSpeed(double _speed)
{
    if(units == MPH)
    {
        speed = kmhToMph(_speed);
    }
    else
    {
        speed = _speed;
    }
    speed = qMax(0.0,speed);

    if(!presentation) return;
    updateText();
    updateArrow();
}

void SpeedometerController::setMphSpeed(double _speed)
{
    if(units == KMH)
    {
        speed = mphToKmh(_speed);
    }
    else
    {
        speed = _speed;
    }
    speed = qMax(0.0,speed);

    if(!presentation) return;
    updateText();
    updateArrow();
}

void SpeedometerController::toggleVisibility()
{
    isVisible = !isVisible;

    if(!presentation) return;
    presentation->setDataInputValue("SpeedometerVisible",isVisible,true);
}

void SpeedometerController::enableVisibility()
{
    isVisible = true;

    if(!presentation) return;
    presentation->setDataInputValue("SpeedometerVisible",isVisible,true);
}

void SpeedometerController::disableVisibility()
{
    isVisible = true;

    if(!presentation) return;
    presentation->setDataInputValue("SpeedometerVisible",isVisible,true);
}

void SpeedometerController::demoAnim()
{
    if(!presentation) return;
    presentation->setDataInputValue("CurrentArrowSlide","Anim",true);
}

void SpeedometerController::speedUp()
{
    speed += 1;

    if(!presentation) return;
    updateText();
    updateArrow();
}

void SpeedometerController::slowDown()
{
    speed -= 1;
    speed = qMax(0.0,speed);

    if(!presentation) return;
    updateText();
    updateArrow();
}

void SpeedometerController::onCustomSignal(const QString &path, const QString &name)
{
    qDebug() << "Got cutom signal " << name << " from " << path;
    if(name == "idleStart")
    {
        if(!presentation) return;
        updateArrow();
    }
}

void SpeedometerController::updateText()
{
    if(!presentation) return;
    presentation->setDataInputValue("SpeedometerText", QString("%1").arg(speed, 3, 'f',0, '0'), true);
}

void SpeedometerController::updateArrow()
{
    qDebug() << 190-(qBound(0.0,speed,maxSpeed)/maxSpeed)*250;
    if(!presentation) return;
    presentation->setDataInputValue("ArrowRotation", QVector3D(0,0,-(qBound(0.0,speed,maxSpeed)/maxSpeed)*250),true);
}

double SpeedometerController::mphToKmh(double value)
{
    return value * 1.60934;
}

double SpeedometerController::kmhToMph(double value)
{
    return value / 1.60934;
}
