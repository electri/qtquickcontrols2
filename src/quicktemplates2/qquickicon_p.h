/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Quick Templates 2 module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL3$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPLv3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or later as published by the Free
** Software Foundation and appearing in the file LICENSE.GPL included in
** the packaging of this file. Please review the following information to
** ensure the GNU General Public License version 2.0 requirements will be
** met: http://www.gnu.org/licenses/gpl-2.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QQUICKICON_P_H
#define QQUICKICON_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QtCore/qurl.h>
#include <QtCore/qobject.h>
#include <QtQuickTemplates2/private/qtquicktemplates2global_p.h>
#include <QtGui/qcolor.h>

QT_BEGIN_NAMESPACE

class QQuickIconPrivate;

class Q_QUICKTEMPLATES2_PRIVATE_EXPORT QQuickIcon : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged FINAL)
    Q_PROPERTY(QUrl source READ source WRITE setSource NOTIFY sourceChanged FINAL)
    Q_PROPERTY(int width READ width WRITE setWidth NOTIFY widthChanged FINAL)
    Q_PROPERTY(int height READ height WRITE setHeight NOTIFY heightChanged FINAL)
    Q_PROPERTY(QColor color READ color WRITE setColor RESET resetColor NOTIFY colorChanged FINAL)

public:
    explicit QQuickIcon(QObject *parent = nullptr);

    QString name() const;
    void setName(const QString &name);

    QUrl source() const;
    void setSource(const QUrl &source);

    int width() const;
    void setWidth(int width);

    int height() const;
    void setHeight(int height);

    QColor color() const;
    void setColor(const QColor &color);
    void resetColor();

Q_SIGNALS:
    void nameChanged(const QString &name);
    void sourceChanged(const QUrl &source);
    void widthChanged(int width);
    void heightChanged(int height);
    void colorChanged(const QColor &color);

private:
    Q_DISABLE_COPY(QQuickIcon)
    Q_DECLARE_PRIVATE(QQuickIcon)
};

QT_END_NAMESPACE

#endif // QQUICKICON_P_H
