/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the test suite of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/


#include <QtTest/QtTest>
#include <QtCore/qlocale.h>
#include <qaudiodeviceinfo.h>

#include <QStringList>
#include <QList>

//TESTED_COMPONENT=src/multimedia

class tst_QAudioDeviceInfo : public QObject
{
    Q_OBJECT
public:
    tst_QAudioDeviceInfo(QObject* parent=0) : QObject(parent) {}

private slots:
    void initTestCase();
    void checkAvailableDefaultInput();
    void checkAvailableDefaultOutput();
    void outputList();
    void codecs();
    void channels();
    void sampleSizes();
    void byteOrders();
    void sampleTypes();
    void frequencies();
    void isFormatSupported();
    void preferred();
    void nearest();
    void supportedChannelCounts();
    void supportedSampleRates();
    void assignOperator();
    void deviceName();
    void defaultConstructor();

private:
    bool              available;
    QAudioDeviceInfo* device;
};

void tst_QAudioDeviceInfo::initTestCase()
{
    // Only perform tests if audio output device exists!
    QList<QAudioDeviceInfo> devices = QAudioDeviceInfo::availableDevices(QAudio::AudioOutput);
    if (devices.size() > 0)
        available = true;
    else {
        qWarning()<<"NOTE: no audio output device found, no test will be performed";
        available = false;
    }
}

void tst_QAudioDeviceInfo::checkAvailableDefaultInput()
{
    // Only perform tests if audio input device exists!
    bool storeAvailable = available;
    QList<QAudioDeviceInfo> devices = QAudioDeviceInfo::availableDevices(QAudio::AudioInput);
    if (devices.size() > 0)
        available = true;
    else {
        qWarning()<<"NOTE: no audio input device found, no test will be performed";
        available = false;
    }
    if (available)
        QVERIFY(!QAudioDeviceInfo::defaultInputDevice().isNull());
    available = storeAvailable;
}

void tst_QAudioDeviceInfo::checkAvailableDefaultOutput()
{
    if (available)
        QVERIFY(!QAudioDeviceInfo::defaultOutputDevice().isNull());
}

void tst_QAudioDeviceInfo::outputList()
{
    if (available) {
        QList<QAudioDeviceInfo> devices = QAudioDeviceInfo::availableDevices(QAudio::AudioOutput);
        QVERIFY(devices.size() > 0);
        device = new QAudioDeviceInfo(devices.at(0));
    }
}

void tst_QAudioDeviceInfo::codecs()
{
    if (available) {
        QStringList avail = device->supportedCodecs();
        QVERIFY(avail.size() > 0);
    }
}

void tst_QAudioDeviceInfo::channels()
{
    if (available) {
        QList<int> avail = device->supportedChannels();
        QVERIFY(avail.size() > 0);
    }
}

void tst_QAudioDeviceInfo::sampleSizes()
{
    if (available) {
        QList<int> avail = device->supportedSampleSizes();
        QVERIFY(avail.size() > 0);
    }
}

void tst_QAudioDeviceInfo::byteOrders()
{
    if (available) {
        QList<QAudioFormat::Endian> avail = device->supportedByteOrders();
        QVERIFY(avail.size() > 0);
    }
}

void tst_QAudioDeviceInfo::sampleTypes()
{
    if (available) {
        QList<QAudioFormat::SampleType> avail = device->supportedSampleTypes();
        QVERIFY(avail.size() > 0);
    }
}

void tst_QAudioDeviceInfo::frequencies()
{
    if (available) {
        QList<int> avail = device->supportedFrequencies();
        QVERIFY(avail.size() > 0);
    }
}

void tst_QAudioDeviceInfo::isFormatSupported()
{
    if (available) {
        QAudioFormat format;
        format.setFrequency(44100);
        format.setChannels(2);
        format.setSampleType(QAudioFormat::SignedInt);
        format.setByteOrder(QAudioFormat::LittleEndian);
        format.setSampleSize(16);
        format.setCodec("audio/pcm");

        // Should always be true for these format
        QVERIFY(device->isFormatSupported(format));
    }
}

void tst_QAudioDeviceInfo::preferred()
{
    if (available) {
        QAudioFormat format = device->preferredFormat();
        QVERIFY(format.isValid());
    }
}

// Returns closest QAudioFormat to settings that system audio supports.
void tst_QAudioDeviceInfo::nearest()
{
    if (available) {
        /*
        QAudioFormat format1, format2;
        format1.setFrequency(8000);
        format2 = device->nearestFormat(format1);
        QVERIFY(format2.frequency() == 44100);
        */
        QAudioFormat format;
        format.setFrequency(44100);
        format.setChannels(2);
        format.setSampleType(QAudioFormat::SignedInt);
        format.setByteOrder(QAudioFormat::LittleEndian);
        format.setSampleSize(16);
        format.setCodec("audio/pcm");

        QAudioFormat format2 = device->nearestFormat(format);

        // This is definitely dependent on platform support (but isFormatSupported tests that above)
        QVERIFY(format2.frequency() == 44100);
    }
}

// Returns a list of supported channel counts.
void tst_QAudioDeviceInfo::supportedChannelCounts()
{
    if (available) {
        QList<int> avail = device->supportedChannelCounts();
        QVERIFY(avail.size() > 0);
    }
}

// Returns a list of supported sample rates.
void tst_QAudioDeviceInfo::supportedSampleRates()
{
    if (available) {
        QList<int> avail = device->supportedSampleRates();
        QVERIFY(avail.size() > 0);
    }
}

// QAudioDeviceInfo's assignOperator method
void tst_QAudioDeviceInfo::assignOperator()
{
    QAudioDeviceInfo dev;
    QVERIFY(dev.deviceName() == NULL);
    QVERIFY(dev.isNull() == true);

    if (available) {
        QList<QAudioDeviceInfo> devices = QAudioDeviceInfo::availableDevices(QAudio::AudioOutput);
        QVERIFY(devices.size() > 0);
        QAudioDeviceInfo dev1(devices.at(0));
        dev = dev1;
        QVERIFY(dev.isNull() == false);
        QVERIFY(dev.deviceName() == dev1.deviceName());
    }
}

// Returns human readable name of audio device
void tst_QAudioDeviceInfo::deviceName()
{
    if (available) {
        QVERIFY(device->deviceName() != NULL);
        QVERIFY(device->deviceName() == QAudioDeviceInfo::availableDevices(QAudio::AudioOutput).at(0).deviceName());
    }
}

// QAudioDeviceInfo's defaultConstructor method
void tst_QAudioDeviceInfo::defaultConstructor()
{
    QAudioDeviceInfo dev;
    QVERIFY(dev.isNull() == true);
    QVERIFY(dev.deviceName() == NULL);
}

QTEST_MAIN(tst_QAudioDeviceInfo)

#include "tst_qaudiodeviceinfo.moc"