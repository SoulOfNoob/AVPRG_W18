#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QMainWindow>
#include <QLabel>
#include <QTextBrowser>
#include <QImage>
#include "videoengine.h"
#include "copyprocessor.h"
#include "jsontransmitter.h"

namespace Ui {
class VideoPlayer;
}

class VideoPlayer : public QMainWindow
{
    Q_OBJECT

public:
    explicit VideoPlayer(QWidget *parent = 0);
    ~VideoPlayer();

    JSONTransmitter transmitter;

private slots:
    void on_actionVideodatei_ffnen_triggered();
    void on_actionKamera_ffnen_triggered();
    void on_actionPlay_triggered();
    void on_hueSlider_valueChanged(int value);

    void on_colorFilter_toggled(bool checked);

    void on_areaFilter_toggled(bool checked);

    void on_boxFilter_toggled(bool checked);

    void on_curverFilter_toggled(bool checked);

    void on_satSlider_valueChanged(int value);

    void on_valSlider_valueChanged(int value);

    void on_trshSlider_valueChanged(int value);

    void on_calibrateButton_clicked();

    void on_sendButton_clicked();

private:
    Ui::VideoPlayer *ui;
    VideoEngine videoEngine;
    CopyProcessor copyProcessor;
    void updateLabel(QLabel* lable, QString text);
    void updateTextField(QTextBrowser* textField, QString text);
};

#endif // VIDEOPLAYER_H
