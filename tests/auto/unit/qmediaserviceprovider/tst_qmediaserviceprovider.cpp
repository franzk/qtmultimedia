/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the Qt Toolkit.
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

//TESTED_COMPONENT=src/multimedia

#include <QtTest/QtTest>
#include <QDebug>
#include <QStringList>

#include <qmediaserviceprovider.h>
#include <qmediaserviceproviderplugin.h>
#include <private/qmediapluginloader_p.h>
#include <qmediaobject.h>
#include <qmediaservice.h>
#include <qmediaplayer.h>
#include <qaudiocapturesource.h>

QT_USE_NAMESPACE
class MockMediaService : public QMediaService
{
    Q_OBJECT
public:
    MockMediaService(const QString& name, QObject *parent = 0) : QMediaService(parent)
    { setObjectName(name); }
    ~MockMediaService() {}

    QMediaControl* requestControl(const char *) {return 0;}
    void releaseControl(QMediaControl *) {}
};

class MockServicePlugin1 : public QMediaServiceProviderPlugin,
                           public QMediaServiceSupportedFormatsInterface,
                           public QMediaServiceSupportedDevicesInterface
{
    Q_OBJECT
    Q_INTERFACES(QMediaServiceSupportedFormatsInterface)
    Q_INTERFACES(QMediaServiceSupportedDevicesInterface)
public:
    QStringList keys() const
    {
        return QStringList() <<
                QLatin1String(Q_MEDIASERVICE_MEDIAPLAYER);
    }

    QMediaService* create(QString const& key)
    {
        if (keys().contains(key))
            return new MockMediaService("MockServicePlugin1");
        else
            return 0;
    }

    void release(QMediaService *service)
    {
        delete service;
    }

    QtMultimedia::SupportEstimate hasSupport(const QString &mimeType, const QStringList& codecs) const
    {
        if (codecs.contains(QLatin1String("mpeg4")))
            return QtMultimedia::NotSupported;

        if (mimeType == "audio/ogg") {
            return QtMultimedia::ProbablySupported;
        }

        return QtMultimedia::MaybeSupported;
    }

    QStringList supportedMimeTypes() const
    {
        return QStringList("audio/ogg");
    }

    QList<QByteArray> devices(const QByteArray &service) const
    {
        QList<QByteArray> res;
        return res;
    }

    QString deviceDescription(const QByteArray &service, const QByteArray &device)
    {
        if (devices(service).contains(device))
            return QString(device)+" description";
        else
            return QString();
    }
};

class MockServicePlugin2 : public QMediaServiceProviderPlugin,
                            public QMediaServiceSupportedFormatsInterface,
                            public QMediaServiceFeaturesInterface
{
    Q_OBJECT
    Q_INTERFACES(QMediaServiceSupportedFormatsInterface)
    Q_INTERFACES(QMediaServiceFeaturesInterface)
public:
    QStringList keys() const
    {
        return QStringList() << QLatin1String(Q_MEDIASERVICE_MEDIAPLAYER)
                             << QLatin1String(Q_MEDIASERVICE_RADIO);
    }

    QMediaService* create(QString const& key)
    {
        if (keys().contains(key))
            return new MockMediaService("MockServicePlugin2");
        else
            return 0;
    }

    void release(QMediaService *service)
    {
        delete service;
    }

    QtMultimedia::SupportEstimate hasSupport(const QString &mimeType, const QStringList& codecs) const
    {
        Q_UNUSED(codecs);

        if (mimeType == "audio/wav")
            return QtMultimedia::PreferredService;

        return QtMultimedia::NotSupported;
    }

    QStringList supportedMimeTypes() const
    {
        return QStringList("audio/wav");
    }

    QMediaServiceProviderHint::Features supportedFeatures(const QByteArray &service) const
    {
        if (service == QByteArray(Q_MEDIASERVICE_MEDIAPLAYER))
            return QMediaServiceProviderHint::LowLatencyPlayback;
        else
            return 0;
    }
};


class MockServicePlugin3 : public QMediaServiceProviderPlugin,
                            public QMediaServiceSupportedDevicesInterface
{
    Q_OBJECT
    Q_INTERFACES(QMediaServiceSupportedDevicesInterface)
public:
    QStringList keys() const
    {
        return QStringList() <<
               QLatin1String(Q_MEDIASERVICE_MEDIAPLAYER) <<
               QLatin1String(Q_MEDIASERVICE_AUDIOSOURCE);
    }

    QMediaService* create(QString const& key)
    {
        if (keys().contains(key))
            return new MockMediaService("MockServicePlugin3");
        else
            return 0;
    }

    void release(QMediaService *service)
    {
        delete service;
    }

    QList<QByteArray> devices(const QByteArray &service) const
    {
        QList<QByteArray> res;
        if (service == QByteArray(Q_MEDIASERVICE_AUDIOSOURCE))
            res << "audiosource1" << "audiosource2";

        return res;
    }

    QString deviceDescription(const QByteArray &service, const QByteArray &device)
    {
        if (devices(service).contains(device))
            return QString(device)+" description";
        else
            return QString();
    }
};

class MockServicePlugin4 : public QMediaServiceProviderPlugin,
                            public QMediaServiceSupportedFormatsInterface,
                            public QMediaServiceFeaturesInterface
{
    Q_OBJECT
    Q_INTERFACES(QMediaServiceSupportedFormatsInterface)
    Q_INTERFACES(QMediaServiceFeaturesInterface)
public:
    QStringList keys() const
    {
        return QStringList() << QLatin1String(Q_MEDIASERVICE_MEDIAPLAYER);
    }

    QMediaService* create(QString const& key)
    {
        if (keys().contains(key))
            return new MockMediaService("MockServicePlugin4");
        else
            return 0;
    }

    void release(QMediaService *service)
    {
        delete service;
    }

    QtMultimedia::SupportEstimate hasSupport(const QString &mimeType, const QStringList& codecs) const
    {
        if (codecs.contains(QLatin1String("jpeg2000")))
            return QtMultimedia::NotSupported;

        if (supportedMimeTypes().contains(mimeType))
            return QtMultimedia::ProbablySupported;

        return QtMultimedia::MaybeSupported;
    }

    QStringList supportedMimeTypes() const
    {
        return QStringList() << "video/mp4" << "video/quicktime";
    }

    QMediaServiceProviderHint::Features supportedFeatures(const QByteArray &service) const
    {
        if (service == QByteArray(Q_MEDIASERVICE_MEDIAPLAYER))
            return QMediaServiceProviderHint::StreamPlayback;
        else
            return 0;
    }
};



class MockMediaServiceProvider : public QMediaServiceProvider
{
    QMediaService* requestService(const QByteArray &type, const QMediaServiceProviderHint &)
    {
        Q_UNUSED(type);
        return 0;
    }

    void releaseService(QMediaService *service)
    {
        Q_UNUSED(service);
    }
};


class tst_QMediaServiceProvider : public QObject
{
    Q_OBJECT

public slots:
    void initTestCase();

private slots:
    void testDefaultProviderAvailable();
    void testObtainService();
    void testHasSupport();
    void testSupportedMimeTypes();
    void testProviderHints();

private:
    QObjectList plugins;
};

void tst_QMediaServiceProvider::initTestCase()
{
    plugins << new MockServicePlugin1;
    plugins << new MockServicePlugin2;
    plugins << new MockServicePlugin3;
    plugins << new MockServicePlugin4;

    QMediaPluginLoader::setStaticPlugins(QLatin1String("mediaservice"), plugins);
}

void tst_QMediaServiceProvider::testDefaultProviderAvailable()
{
    // Must always be a default provider available    
    QVERIFY(QMediaServiceProvider::defaultServiceProvider() != 0);
}

void tst_QMediaServiceProvider::testObtainService()
{
    QMediaServiceProvider *provider = QMediaServiceProvider::defaultServiceProvider();

    if (provider == 0)
        QSKIP("No default provider");

    QMediaService *service = 0;

    // Player
    service = provider->requestService(Q_MEDIASERVICE_MEDIAPLAYER);
    QVERIFY(service != 0);
    provider->releaseService(service);
}

void tst_QMediaServiceProvider::testHasSupport()
{
    MockMediaServiceProvider mockProvider;
    QCOMPARE(mockProvider.hasSupport(QByteArray(Q_MEDIASERVICE_MEDIAPLAYER), "video/ogv", QStringList()),
             QtMultimedia::MaybeSupported);

    QMediaServiceProvider *provider = QMediaServiceProvider::defaultServiceProvider();

    if (provider == 0)
        QSKIP("No default provider");

    QCOMPARE(provider->hasSupport(QByteArray(Q_MEDIASERVICE_MEDIAPLAYER), "video/ogv", QStringList()),
             QtMultimedia::MaybeSupported);

    QCOMPARE(provider->hasSupport(QByteArray(Q_MEDIASERVICE_MEDIAPLAYER), "audio/ogg", QStringList()),
             QtMultimedia::ProbablySupported);

    //while the service returns PreferredService, provider should return ProbablySupported
    QCOMPARE(provider->hasSupport(QByteArray(Q_MEDIASERVICE_MEDIAPLAYER), "audio/wav", QStringList()),
             QtMultimedia::ProbablySupported);

    //even while all the plugins with "hasSupport" returned NotSupported,
    //MockServicePlugin3 has no "hasSupport" interface, so MaybeSupported
    QCOMPARE(provider->hasSupport(QByteArray(Q_MEDIASERVICE_MEDIAPLAYER), "video/avi",
                                  QStringList() << "mpeg4"),
             QtMultimedia::MaybeSupported);

    QCOMPARE(provider->hasSupport(QByteArray("non existing service"), "video/ogv", QStringList()),
             QtMultimedia::NotSupported);

    QCOMPARE(QMediaPlayer::hasSupport("video/ogv"), QtMultimedia::MaybeSupported);
    QCOMPARE(QMediaPlayer::hasSupport("audio/ogg"), QtMultimedia::ProbablySupported);
    QCOMPARE(QMediaPlayer::hasSupport("audio/wav"), QtMultimedia::ProbablySupported);

    //test low latency flag support
    QCOMPARE(QMediaPlayer::hasSupport("audio/wav", QStringList(), QMediaPlayer::LowLatency),
             QtMultimedia::ProbablySupported);
    //plugin1 probably supports audio/ogg, it checked because it doesn't provide features iface
    QCOMPARE(QMediaPlayer::hasSupport("audio/ogg", QStringList(), QMediaPlayer::LowLatency),
             QtMultimedia::ProbablySupported);
    //Plugin4 is not checked here, sine it's known not support low latency
    QCOMPARE(QMediaPlayer::hasSupport("video/quicktime", QStringList(), QMediaPlayer::LowLatency),
             QtMultimedia::MaybeSupported);

    //test streaming flag support
    QCOMPARE(QMediaPlayer::hasSupport("video/quicktime", QStringList(), QMediaPlayer::StreamPlayback),
             QtMultimedia::ProbablySupported);
    //Plugin2 is not checked here, sine it's known not support streaming
    QCOMPARE(QMediaPlayer::hasSupport("audio/wav", QStringList(), QMediaPlayer::StreamPlayback),
             QtMultimedia::MaybeSupported);

    //ensure the correct media player plugin is chosen for mime type
    QMediaPlayer simplePlayer(0, QMediaPlayer::LowLatency);
    QCOMPARE(simplePlayer.service()->objectName(), QLatin1String("MockServicePlugin2"));

    QMediaPlayer mediaPlayer;
    QVERIFY(mediaPlayer.service()->objectName() != QLatin1String("MockServicePlugin2"));

    QMediaPlayer streamPlayer(0, QMediaPlayer::StreamPlayback);
    QCOMPARE(streamPlayer.service()->objectName(), QLatin1String("MockServicePlugin4"));
}

void tst_QMediaServiceProvider::testSupportedMimeTypes()
{
    QMediaServiceProvider *provider = QMediaServiceProvider::defaultServiceProvider();

    if (provider == 0)
        QSKIP("No default provider");

    QVERIFY(provider->supportedMimeTypes(QByteArray(Q_MEDIASERVICE_MEDIAPLAYER)).contains("audio/ogg"));
    QVERIFY(!provider->supportedMimeTypes(QByteArray(Q_MEDIASERVICE_MEDIAPLAYER)).contains("audio/mp3"));
}

void tst_QMediaServiceProvider::testProviderHints()
{
    {
        QMediaServiceProviderHint hint;
        QVERIFY(hint.isNull());
        QCOMPARE(hint.type(), QMediaServiceProviderHint::Null);
        QVERIFY(hint.device().isEmpty());
        QVERIFY(hint.mimeType().isEmpty());
        QVERIFY(hint.codecs().isEmpty());
        QCOMPARE(hint.features(), 0);
    }

    {
        QByteArray deviceName(QByteArray("testDevice"));
        QMediaServiceProviderHint hint(deviceName);
        QVERIFY(!hint.isNull());
        QCOMPARE(hint.type(), QMediaServiceProviderHint::Device);
        QCOMPARE(hint.device(), deviceName);
        QVERIFY(hint.mimeType().isEmpty());
        QVERIFY(hint.codecs().isEmpty());
        QCOMPARE(hint.features(), 0);
    }

    {
        QMediaServiceProviderHint hint(QMediaServiceProviderHint::LowLatencyPlayback);
        QVERIFY(!hint.isNull());
        QCOMPARE(hint.type(), QMediaServiceProviderHint::SupportedFeatures);
        QVERIFY(hint.device().isEmpty());
        QVERIFY(hint.mimeType().isEmpty());
        QVERIFY(hint.codecs().isEmpty());
        QCOMPARE(hint.features(), QMediaServiceProviderHint::LowLatencyPlayback);
    }

    {
        QMediaServiceProviderHint hint(QMediaServiceProviderHint::RecordingSupport);
        QVERIFY(!hint.isNull());
        QCOMPARE(hint.type(), QMediaServiceProviderHint::SupportedFeatures);
        QVERIFY(hint.device().isEmpty());
        QVERIFY(hint.mimeType().isEmpty());
        QVERIFY(hint.codecs().isEmpty());
        QCOMPARE(hint.features(), QMediaServiceProviderHint::RecordingSupport);
    }

    {
        QString mimeType(QLatin1String("video/ogg"));
        QStringList codecs;
        codecs << "theora" << "vorbis";

        QMediaServiceProviderHint hint(mimeType,codecs);
        QVERIFY(!hint.isNull());
        QCOMPARE(hint.type(), QMediaServiceProviderHint::ContentType);
        QVERIFY(hint.device().isEmpty());
        QCOMPARE(hint.mimeType(), mimeType);
        QCOMPARE(hint.codecs(), codecs);

        QMediaServiceProviderHint hint2(hint);

        QVERIFY(!hint2.isNull());
        QCOMPARE(hint2.type(), QMediaServiceProviderHint::ContentType);
        QVERIFY(hint2.device().isEmpty());
        QCOMPARE(hint2.mimeType(), mimeType);
        QCOMPARE(hint2.codecs(), codecs);

        QMediaServiceProviderHint hint3;
        QVERIFY(hint3.isNull());
        hint3 = hint;
        QVERIFY(!hint3.isNull());
        QCOMPARE(hint3.type(), QMediaServiceProviderHint::ContentType);
        QVERIFY(hint3.device().isEmpty());
        QCOMPARE(hint3.mimeType(), mimeType);
        QCOMPARE(hint3.codecs(), codecs);

        QCOMPARE(hint, hint2);
        QCOMPARE(hint3, hint2);

        QMediaServiceProviderHint hint4(mimeType,codecs);
        QCOMPARE(hint, hint4);

        QMediaServiceProviderHint hint5(mimeType,QStringList());
        QVERIFY(hint != hint5);
    }
}

QTEST_MAIN(tst_QMediaServiceProvider)

#include "tst_qmediaserviceprovider.moc"