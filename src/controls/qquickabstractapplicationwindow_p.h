/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Quick Controls module of the Qt Toolkit.
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

#ifndef QQUICKABSTRACTAPPLICATIONWINDOW_P_H
#define QQUICKABSTRACTAPPLICATIONWINDOW_P_H

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

#include <QtQuick/private/qquickwindowmodule_p.h>
#include <QtQuickControls/private/qtquickcontrolsglobal_p.h>

QT_BEGIN_NAMESPACE

class QQuickStyle;
class QQuickAbstractApplicationWindowPrivate;

class Q_QUICKCONTROLS_EXPORT QQuickAbstractApplicationWindow : public QQuickWindowQmlImpl
{
    Q_OBJECT
    Q_PROPERTY(QQuickItem *header READ header WRITE setHeader NOTIFY headerChanged FINAL)
    Q_PROPERTY(QQuickItem *footer READ footer WRITE setFooter NOTIFY footerChanged FINAL)
    Q_PROPERTY(QQuickStyle *style READ style WRITE setStyle NOTIFY styleChanged FINAL)
    Q_PROPERTY(qreal contentWidth READ contentWidth WRITE setContentWidth NOTIFY contentWidthChanged FINAL)
    Q_PROPERTY(qreal contentHeight READ contentHeight WRITE setContentHeight NOTIFY contentHeightChanged FINAL)

public:
    explicit QQuickAbstractApplicationWindow(QWindow *parent = Q_NULLPTR);
    ~QQuickAbstractApplicationWindow();

    QQuickItem *header() const;
    void setHeader(QQuickItem *header);

    QQuickItem *footer() const;
    void setFooter(QQuickItem *footer);

    QQuickStyle *style() const;
    void setStyle(QQuickStyle *style);

    qreal contentWidth() const;
    void setContentWidth(qreal width);

    qreal contentHeight() const;
    void setContentHeight(qreal height);

Q_SIGNALS:
    void headerChanged();
    void footerChanged();
    void styleChanged();
    void contentWidthChanged();
    void contentHeightChanged();

protected:
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(QQuickAbstractApplicationWindow)
    Q_DECLARE_PRIVATE(QQuickAbstractApplicationWindow)
    QScopedPointer<QQuickAbstractApplicationWindowPrivate> d_ptr;
};

QT_END_NAMESPACE

#endif // QQUICKABSTRACTAPPLICATIONWINDOW_P_H
