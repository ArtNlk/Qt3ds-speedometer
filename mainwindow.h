#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWindow>
#include <QtStudio3D/Q3DSPresentation>
#include <QKeyEvent>

class MainWindow : public QWindow
{
public:
    MainWindow(QWindow* parent = nullptr);

    void setPresentation(Q3DSPresentation* _presentation);

public slots:
    void onPresentationReady();

private:
    void keyPressEvent(QKeyEvent *event);

    Q3DSPresentation* presentation;
};

#endif // MAINWINDOW_H
