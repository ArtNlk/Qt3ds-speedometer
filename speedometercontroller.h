#ifndef SPEEDOMETERCONTROLLER_H
#define SPEEDOMETERCONTROLLER_H

#include <Q3DSPresentation>

class SpeedometerController : public QObject
{
    Q_OBJECT
public:
    SpeedometerController(QObject *_parent);
    virtual ~SpeedometerController() = default;

    enum SpeedUnit {MPH,KMH};

    void setPresentation(Q3DSPresentation* _presentation);

    void leftLayout();
    void centralLayout();
    void rightLayout();

    void setKmhUnits();
    void setMphUnits();

    void setKmhMaxSpeed(double _speed);
    void setMphMaxSpeed(double _speed);

    void setKmhSpeed(double _speed);
    void setMphSpeed(double _speed);

    void toggleVisibility();
    void enableVisibility();
    void disableVisibility();

    void demoAnim();

    void speedUp();
    void slowDown();

private slots:
    void onCustomSignal(const QString& path, const QString& name);

private:
    SpeedUnit units;
    bool isVisible;
    double speed;
    double maxSpeed;
    Q3DSPresentation* presentation;

    void inline updateText();
    void inline updateArrow();
    double inline mphToKmh(double value);
    double inline kmhToMph(double value);
};

#endif // SPEEDOMETERCONTROLLER_H
