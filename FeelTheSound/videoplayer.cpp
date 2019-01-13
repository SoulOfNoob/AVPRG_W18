#include <QFileDialog>
#include "videoplayer.h"
#include "ui_videoplayer.h"
#include <iostream>
#include <QJsonDocument>
#include <QWebChannel>
#include <QWebSocket>
#include <QWebSocketServer>
#include "shared/websocketclientwrapper.h"
#include "shared/websockettransport.h"


using namespace cv;
using namespace std;

VideoPlayer::VideoPlayer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::VideoPlayer)
{
    ui->setupUi(this);
    videoEngine.setInputWidget(ui->inputFrame);
    videoEngine.setProcessedWidget(ui->processedFrame);
    videoEngine.setProcessor(&copyProcessor);


}

VideoPlayer::~VideoPlayer()
{
    delete ui;
}

void VideoPlayer::on_actionVideodatei_ffnen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Movie"),QDir::homePath());

    if (!fileName.isEmpty()) {
        videoEngine.openFile(fileName);
     }
}

void VideoPlayer::on_actionKamera_ffnen_triggered()
{
    const int deviceNumber = 0;
    videoEngine.openCamera(deviceNumber + cv::CAP_DSHOW);
}

void VideoPlayer::on_actionPlay_triggered()
{
    videoEngine.start();
}

void VideoPlayer::updateLabel(QLabel *label, QString text)
{
    label->setText(text);
}

void VideoPlayer::updateTextField(QTextBrowser *textField, QString text)
{
    textField->setText(text);
}

void VideoPlayer::on_hueSlider_valueChanged(int value)
{
    copyProcessor.hue = value;
    updateLabel(ui->hueLabel, QString::number(value));
}

void VideoPlayer::on_colorFilter_toggled(bool checked)
{
    if(checked) copyProcessor.filter = 0;
}

void VideoPlayer::on_areaFilter_toggled(bool checked)
{
    if(checked) copyProcessor.filter = 1;
}

void VideoPlayer::on_boxFilter_toggled(bool checked)
{
    if(checked) copyProcessor.filter = 2;
}

void VideoPlayer::on_curverFilter_toggled(bool checked)
{
    if(checked) copyProcessor.filter = 3;
}

void VideoPlayer::on_satSlider_valueChanged(int value)
{
    copyProcessor.sat = value;
    updateLabel(ui->satLabel, QString::number(value));
}

void VideoPlayer::on_valSlider_valueChanged(int value)
{
    copyProcessor.val = value;
    updateLabel(ui->valLabel, QString::number(value));
}

void VideoPlayer::on_trshSlider_valueChanged(int value)
{
    copyProcessor.trsh = value;
    updateLabel(ui->trshLabel, QString::number(value));
}

void VideoPlayer::on_calibrateButton_clicked()
{
    copyProcessor.calibration = true;
    updateLabel(ui->calLabel, QString::number(copyProcessor.calibrationValue));
}

void VideoPlayer::on_sendButton_clicked()
{
    copyProcessor.getData = true;
    transmitter.JSONData = copyProcessor.JSONData;
    QJsonDocument doc;
    doc.setArray(copyProcessor.JSONData);
    QString dataToString(doc.toJson());
    updateTextField(ui->textOutput, dataToString);
}
