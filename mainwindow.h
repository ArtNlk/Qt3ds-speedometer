#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWindow>
#include <QtStudio3D/Q3DSPresentation>
#include <QKeyEvent>
#include <QVector3D>

class MainWindow : public QWindow
{
public:
    MainWindow(QWindow* parent = nullptr);

    void setPresentation(Q3DSPresentation* _presentation);

public slots:
    void onPresentationReady();

private:
    void keyPressEvent(QKeyEvent *event);

    void onCustomSignal(const QString& path, const QString& name);

    Q3DSPresentation* presentation;
    QVector3D currentRotation;
    bool speedometerVisible;
};

#endif // MAINWINDOW_H
