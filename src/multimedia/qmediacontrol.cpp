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

#include <QtCore/qmetaobject.h>
#include <QtCore/qtimer.h>

#include "qmediacontrol.h"
#include "qmediacontrol_p.h"



QT_BEGIN_NAMESPACE

/*!
    \class QMediaControl
    \inmodule QtMultimedia

    \ingroup multimedia
    \ingroup multimedia_control
    \ingroup multimedia_core

    \brief The QMediaControl class provides a base interface for media service controls.

    Media controls provide an interface to individual features provided by a
    media service.  Most services implement a principal control which exposes
    the core functionality of the service and a number of optional controls which
    expose any additional functionality.

    A pointer to a control implemented by a media service can be obtained using
    the \l {QMediaService::requestControl()} member of QMediaService.  If the
    service doesn't implement a control it will instead return a null pointer.

    \snippet doc/src/snippets/multimedia-snippets/media.cpp Request control

    Alternatively if the IId of the control has been declared using
    Q_MEDIA_DECLARE_CONTROL the template version of
    QMediaService::requestControl() can be used to request the service without
    explicitly passing the IId or using qobject_cast().

    \snippet doc/src/snippets/multimedia-snippets/media.cpp Request control templated

    Most application code will not interface directly with a media service's
    controls, instead the QMediaObject which owns the service acts as an
    intermediary between one or more controls and the application.

    \sa QMediaService, QMediaObject
*/

/*!
    \macro Q_MEDIA_DECLARE_CONTROL(Class, IId)
    \relates QMediaControl

    The Q_MEDIA_DECLARE_CONTROL macro declares an \a IId for a \a Class that
    inherits from QMediaControl.

    Declaring an IId for a QMediaControl allows an instance of that control to
    be requested from QMediaService::requestControl() without explicitly
    passing the IId.

    \snippet doc/src/snippets/multimedia-snippets/media.cpp Request control templated

    \sa QMediaService::requestControl()
*/

/*!
    Destroys a media control.
*/

QMediaControl::~QMediaControl()
{
    delete d_ptr;
}

/*!
    Constructs a media control with the given \a parent.
*/

QMediaControl::QMediaControl(QObject *parent)
    : QObject(parent)
    , d_ptr(new QMediaControlPrivate)
{
    d_ptr->q_ptr = this;
}

/*!
    \internal
*/

QMediaControl::QMediaControl(QMediaControlPrivate &dd, QObject *parent)
    : QObject(parent)
    , d_ptr(&dd)

{
    d_ptr->q_ptr = this;
}

#include "moc_qmediacontrol.cpp"
QT_END_NAMESPACE

