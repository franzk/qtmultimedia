/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/
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
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qmediaaudioprobecontrol.h"
#include "qmediacontrol_p.h"

QT_BEGIN_NAMESPACE

/*!
    \class QMediaAudioProbeControl
    \inmodule QtMultimedia

    \ingroup multimedia
    \ingroup multimedia_control

    \brief The QMediaAudioProbeControl class allows control over probing audio data in media objects.

    \l QAudioProbe is the client facing class for probing audio - this class is implemented by
    media backends to provide this functionality.

    The interface name of QMediaAudioProbeControl is \c com.nokia.Qt.QMediaAudioProbeControl/1.0 as
    defined in QMediaAudioProbeControl_iid.

    \sa QAudioProbe, QMediaService::requestControl(), QMediaPlayer, QCamera
*/

/*!
    \macro QMediaAudioProbeControl_iid

    \c com.nokia.Qt.QMediaAudioProbeControl/1.0

    Defines the interface name of the QMediaAudioProbeControl class.

    \relates QMediaAudioProbeControl
*/

/*!
  Create a new media audio probe control object with the given \a parent.
*/
QMediaAudioProbeControl::QMediaAudioProbeControl(QObject *parent)
    : QMediaControl(*new QMediaControlPrivate, parent)
{
}

/*! Destroys this audio probe control */
QMediaAudioProbeControl::~QMediaAudioProbeControl()
{
}

/*!
    \fn QMediaAudioProbeControl::audioBufferProbed(const QAudioBuffer &buffer)

    This signal should be emitted when an audio buffer is processed in the
    media service.
*/

#include "moc_qmediaaudioprobecontrol.cpp"

QT_END_NAMESPACE