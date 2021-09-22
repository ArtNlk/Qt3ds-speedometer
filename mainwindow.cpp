#include "mainwindow.h"

#include <QDebug>
#include <QVector4D>

MainWindow::MainWindow(QWindow* parent) :
    QWindow(parent),
    presentation(nullptr),
    currentRotation(0,0,0),
    speedometerVisible(true)
{

}

void MainWindow::setPresentation(Q3DSPresentation *_presentation)
{
    qDebug() << "Presentation loaded";
    if (_presentation == nullptr)
    {
        qDebug() << "presentation is null";
        return;
    }
    presentation = _presentation;
    connect(presentation,&Q3DSPresentation::customSignalEmitted,this,&MainWindow::onCustomSignal);
}

void MainWindow::onPresentationReady()
{

}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(!presentation) return;

    qDebug() << event->key() - 48 << "pressed";

    switch (event->key())
    {
        case Qt::Key_1:
        presentation->setAttribute("Scene.Layer.Speedometer.units.units_mat.diffusemap", "sourcepath","qrc:/speedometer/maps/kmh.png");
        presentation->setDataInputValue("SpeedometerColor", QVector4D(0,0,255,255), true);
        presentation->setDataInputValue("TextColor", QVector4D(255,255,255,255), true);
            break;

        case Qt::Key_2:
        presentation->setAttribute("Scene.Layer.Speedometer.units.units_mat.diffusemap", "sourcepath","qrc:/speedometer/maps/mph.png");
        presentation->setDataInputValue("SpeedometerColor", QVector4D(255,0,0,255), true);
        presentation->setDataInputValue("TextColor", QVector4D(0,0,0,255), true);
            break;

        case Qt::Key_3:
            presentation->setDataInputValue("CurrentArrowSlide", "Anim", true);
            break;

        case Qt::Key_4:
            presentation->setDataInputValue("CurrentSlide","Left",true);
            break;

        case Qt::Key_5:
            presentation->setDataInputValue("CurrentSlide","Mid",true);
            break;

        case Qt::Key_6:
            presentation->setDataInputValue("CurrentSlide","Right",true);
            break;

        case Qt::Key_7:
            speedometerVisible = !speedometerVisible;
            presentation->setDataInputValue("SpeedometerVisible",speedometerVisible,true);
            break;

        case Qt::Key_Plus:
                currentRotation.setZ(currentRotation.z() - 1);
                presentation->setDataInputValue("ArrowRotation", currentRotation, true);
                presentation->setDataInputValue("SpeedometerText", QString::number(-currentRotation.z()), true);
            break;

        case Qt::Key_Minus:
                currentRotation.setZ(currentRotation.z() + 1);
                presentation->setDataInputValue("ArrowRotation", currentRotation, true);
                presentation->setDataInputValue("SpeedometerText", QString::number(-currentRotation.z()), true);
            break;

        default:
            break;
    }
}

void MainWindow::onCustomSignal(const QString& path, const QString& name)
{
    qDebug() << "Got cutom signal " << name << " from " << path;
    if(name == "idleStart")
    {
        presentation->setDataInputValue("ArrowRotation", QVariant(currentRotation), true);
    }
}
