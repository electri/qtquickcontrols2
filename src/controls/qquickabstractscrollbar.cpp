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

#include "qquickabstractscrollbar_p.h"
#include "qquickcontrol_p_p.h"

#include <QtQuick/private/qquickflickable_p.h>
#include <QtQuick/private/qquickitemchangelistener_p.h>

QT_BEGIN_NAMESPACE

/*!
    \qmltype ScrollBar
    \inherits Control
    \instantiates QQuickAbstractScrollBar
    \inqmlmodule QtQuick.Controls
    \ingroup indicators
    \ingroup sliders
    \brief A scroll bar.

    TODO
*/

class QQuickAbstractScrollBarPrivate : public QQuickControlPrivate
{
public:
    QQuickAbstractScrollBarPrivate() : size(0), position(0), offset(0),
        active(false), pressed(false), moving(false),
        orientation(Qt::Vertical), handle(Q_NULLPTR) { }

    static QQuickAbstractScrollBarPrivate *get(QQuickAbstractScrollBar *bar)
    {
        return bar->d_func();
    }

    qreal size;
    qreal position;
    qreal offset;
    bool active;
    bool pressed;
    bool moving;
    Qt::Orientation orientation;
    QQuickItem *handle;
};

QQuickAbstractScrollBar::QQuickAbstractScrollBar(QQuickItem *parent) :
    QQuickControl(*(new QQuickAbstractScrollBarPrivate), parent)
{
    setKeepMouseGrab(true);
    setAcceptedMouseButtons(Qt::LeftButton);
}

QQuickScrollBarAttached *QQuickAbstractScrollBar::qmlAttachedProperties(QObject *object)
{
    QQuickFlickable *flickable = qobject_cast<QQuickFlickable *>(object);
    if (flickable)
        return new QQuickScrollBarAttached(flickable);

    qWarning() << "ScrollBar must be attached to a Flickable" << object;
    return Q_NULLPTR;
}

/*!
    \qmlproperty real QtQuickControls2::ScrollBar::size

    TODO
*/
qreal QQuickAbstractScrollBar::size() const
{
    Q_D(const QQuickAbstractScrollBar);
    return d->size;
}

void QQuickAbstractScrollBar::setSize(qreal size)
{
    Q_D(QQuickAbstractScrollBar);
    if (!qFuzzyCompare(d->size, size)) {
        d->size = size;
        emit sizeChanged();
    }
}

/*!
    \qmlproperty real QtQuickControls2::ScrollBar::position

    TODO
*/
qreal QQuickAbstractScrollBar::position() const
{
    Q_D(const QQuickAbstractScrollBar);
    return d->position;
}

void QQuickAbstractScrollBar::setPosition(qreal position)
{
    Q_D(QQuickAbstractScrollBar);
    if (!qFuzzyCompare(d->position, position)) {
        d->position = position;
        emit positionChanged();
    }
}

/*!
    \qmlproperty bool QtQuickControls2::ScrollBar::active

    TODO
*/
bool QQuickAbstractScrollBar::isActive() const
{
    Q_D(const QQuickAbstractScrollBar);
    return d->active;
}

void QQuickAbstractScrollBar::setActive(bool active)
{
    Q_D(QQuickAbstractScrollBar);
    if (d->active != active) {
        d->active = active;
        emit activeChanged();
    }
}

/*!
    \qmlproperty bool QtQuickControls2::ScrollBar::pressed

    TODO
*/
bool QQuickAbstractScrollBar::isPressed() const
{
    Q_D(const QQuickAbstractScrollBar);
    return d->pressed;
}

void QQuickAbstractScrollBar::setPressed(bool pressed)
{
    Q_D(QQuickAbstractScrollBar);
    if (d->pressed != pressed) {
        d->pressed = pressed;
        setActive(d->pressed || d->moving);
        emit pressedChanged();
    }
}

/*!
    \qmlproperty enumeration QtQuickControls2::ScrollBar::orientation

    TODO
*/
Qt::Orientation QQuickAbstractScrollBar::orientation() const
{
    Q_D(const QQuickAbstractScrollBar);
    return d->orientation;
}

void QQuickAbstractScrollBar::setOrientation(Qt::Orientation orientation)
{
    Q_D(QQuickAbstractScrollBar);
    if (d->orientation != orientation) {
        d->orientation = orientation;
        emit orientationChanged();
    }
}

/*!
    \qmlproperty Item QtQuickControls2::ScrollBar::handle

    TODO
*/
QQuickItem *QQuickAbstractScrollBar::handle() const
{
    Q_D(const QQuickAbstractScrollBar);
    return d->handle;
}

void QQuickAbstractScrollBar::setHandle(QQuickItem *handle)
{
    Q_D(QQuickAbstractScrollBar);
    if (d->handle != handle) {
        delete d->handle;
        d->handle = handle;
        if (handle && !handle->parentItem())
            handle->setParentItem(this);
        emit handleChanged();
    }
}

void QQuickAbstractScrollBar::mousePressEvent(QMouseEvent *event)
{
    Q_D(QQuickAbstractScrollBar);
    QQuickControl::mousePressEvent(event);
    d->offset = positionAt(event->pos()) - d->position;
    if (d->offset < 0 || d->offset > d->size)
        d->offset = d->size / 2;
    setPressed(true);
    event->accept();
}

void QQuickAbstractScrollBar::mouseMoveEvent(QMouseEvent *event)
{
    Q_D(QQuickAbstractScrollBar);
    QQuickControl::mouseMoveEvent(event);
    setPosition(qBound(0.0, positionAt(event->pos()) - d->offset, 1.0 - d->size));
    event->accept();
}

void QQuickAbstractScrollBar::mouseReleaseEvent(QMouseEvent *event)
{
    Q_D(QQuickAbstractScrollBar);
    QQuickControl::mouseReleaseEvent(event);
    setPosition(qBound(0.0, positionAt(event->pos()) - d->offset, 1.0 - d->size));
    d->offset = 0.0;
    setPressed(false);
    event->accept();
}

qreal QQuickAbstractScrollBar::positionAt(const QPoint &point) const
{
    Q_D(const QQuickAbstractScrollBar);
    if (d->orientation == Qt::Horizontal)
        return point.x() / width();
    else
        return point.y() / height();
}

class QQuickScrollBarAttachedPrivate : public QObjectPrivate, public QQuickItemChangeListener
{
public:
    QQuickScrollBarAttachedPrivate(QQuickFlickable *flickable) : flickable(flickable), horizontal(Q_NULLPTR), vertical(Q_NULLPTR) { }

    void activateHorizontal();
    void activateVertical();
    void scrollHorizontal();
    void scrollVertical();

    void itemGeometryChanged(QQuickItem *item, const QRectF &newGeometry, const QRectF &oldGeometry) Q_DECL_OVERRIDE;

    QQuickFlickable *flickable;
    QQuickAbstractScrollBar *horizontal;
    QQuickAbstractScrollBar *vertical;
};

void QQuickScrollBarAttachedPrivate::activateHorizontal()
{
    QQuickAbstractScrollBarPrivate *p = QQuickAbstractScrollBarPrivate::get(horizontal);
    p->moving = flickable->isMovingHorizontally();
    horizontal->setActive(p->moving || p->pressed);
}

void QQuickScrollBarAttachedPrivate::activateVertical()
{
    QQuickAbstractScrollBarPrivate *p = QQuickAbstractScrollBarPrivate::get(vertical);
    p->moving = flickable->isMovingVertically();
    vertical->setActive(p->moving || p->pressed);
}

// TODO: QQuickFlickable::maxXYExtent()
class QQuickFriendlyFlickable : public QQuickFlickable
{
    friend class QQuickScrollBarAttachedPrivate;
};

void QQuickScrollBarAttachedPrivate::scrollHorizontal()
{
    QQuickFriendlyFlickable *f = reinterpret_cast<QQuickFriendlyFlickable *>(flickable);

    const qreal viewwidth = f->width();
    const qreal maxxextent = -f->maxXExtent() + f->minXExtent();
    qreal cx = horizontal->position() * (maxxextent + viewwidth) - f->minXExtent();
    if (!qIsNaN(cx) && !qFuzzyCompare(cx, flickable->contentX()))
        flickable->setContentX(cx);
}

void QQuickScrollBarAttachedPrivate::scrollVertical()
{
    QQuickFriendlyFlickable *f = reinterpret_cast<QQuickFriendlyFlickable *>(flickable);

    const qreal viewheight = f->height();
    const qreal maxyextent = -f->maxYExtent() + f->minYExtent();
    qreal cy = vertical->position() * (maxyextent + viewheight) - f->minYExtent();
    if (!qIsNaN(cy) && !qFuzzyCompare(cy, flickable->contentY()))
        flickable->setContentY(cy);
}

void QQuickScrollBarAttachedPrivate::itemGeometryChanged(QQuickItem *item, const QRectF &newGeometry, const QRectF &oldGeometry)
{
    Q_ASSERT(item == flickable);
    if (horizontal) {
        QQuickItemPrivate *p = QQuickItemPrivate::get(horizontal);
        if (!p->widthValid) {
            horizontal->setWidth(newGeometry.width());
            p->widthValid = false;
        }
        if (qFuzzyIsNull(horizontal->y()) || qFuzzyCompare(horizontal->y(), oldGeometry.height() - horizontal->height()))
            horizontal->setY(newGeometry.height() - horizontal->height());
    }
    if (vertical) {
        QQuickItemPrivate *p = QQuickItemPrivate::get(vertical);
        if (!p->heightValid) {
            vertical->setHeight(newGeometry.height());
            p->heightValid = false;
        }
        if (!p->isMirrored() && (qFuzzyIsNull(vertical->x()) || qFuzzyCompare(vertical->x(), oldGeometry.width() - vertical->width())))
            vertical->setX(newGeometry.width() - vertical->width());
    }
}

QQuickScrollBarAttached::QQuickScrollBarAttached(QQuickFlickable *flickable) :
    QObject(*(new QQuickScrollBarAttachedPrivate(flickable)), flickable)
{
    Q_D(QQuickScrollBarAttached);
    QQuickItemPrivate *p = QQuickItemPrivate::get(flickable);
    p->addItemChangeListener(d, QQuickItemPrivate::Geometry);
}

QQuickAbstractScrollBar *QQuickScrollBarAttached::horizontal() const
{
    Q_D(const QQuickScrollBarAttached);
    return d->horizontal;
}

void QQuickScrollBarAttached::setHorizontal(QQuickAbstractScrollBar *horizontal)
{
    Q_D(QQuickScrollBarAttached);
    if (d->horizontal != horizontal) {
        if (d->horizontal) {
            QObjectPrivate::disconnect(d->horizontal, &QQuickAbstractScrollBar::positionChanged, d, &QQuickScrollBarAttachedPrivate::scrollHorizontal);
            QObjectPrivate::disconnect(d->flickable, &QQuickFlickable::movingHorizontallyChanged, d, &QQuickScrollBarAttachedPrivate::activateHorizontal);

            // TODO: export QQuickFlickableVisibleArea
            QObject *area = d->flickable->property("visibleArea").value<QObject *>();
            disconnect(area, SIGNAL(widthRatioChanged(qreal)), d->horizontal, SLOT(setSize(qreal)));
            disconnect(area, SIGNAL(xPositionChanged(qreal)), d->horizontal, SLOT(setPosition(qreal)));
        }

        d->horizontal = horizontal;

        if (horizontal) {
            if (!horizontal->parentItem())
                horizontal->setParentItem(d->flickable);
            horizontal->setOrientation(Qt::Horizontal);

            QObjectPrivate::connect(horizontal, &QQuickAbstractScrollBar::positionChanged, d, &QQuickScrollBarAttachedPrivate::scrollHorizontal);
            QObjectPrivate::connect(d->flickable, &QQuickFlickable::movingHorizontallyChanged, d, &QQuickScrollBarAttachedPrivate::activateHorizontal);

            // TODO: export QQuickFlickableVisibleArea
            QObject *area = d->flickable->property("visibleArea").value<QObject *>();
            connect(area, SIGNAL(widthRatioChanged(qreal)), horizontal, SLOT(setSize(qreal)));
            connect(area, SIGNAL(xPositionChanged(qreal)), horizontal, SLOT(setPosition(qreal)));

            horizontal->setSize(area->property("widthRatio").toReal());
            horizontal->setPosition(area->property("xPosition").toReal());
        }
        emit horizontalChanged();
    }
}

QQuickAbstractScrollBar *QQuickScrollBarAttached::vertical() const
{
    Q_D(const QQuickScrollBarAttached);
    return d->vertical;
}

void QQuickScrollBarAttached::setVertical(QQuickAbstractScrollBar *vertical)
{
    Q_D(QQuickScrollBarAttached);
    if (d->vertical != vertical) {
        if (d->vertical) {
            QObjectPrivate::disconnect(d->vertical, &QQuickAbstractScrollBar::positionChanged, d, &QQuickScrollBarAttachedPrivate::scrollVertical);
            QObjectPrivate::disconnect(d->flickable, &QQuickFlickable::movingVerticallyChanged, d, &QQuickScrollBarAttachedPrivate::activateVertical);

            // TODO: export QQuickFlickableVisibleArea
            QObject *area = d->flickable->property("visibleArea").value<QObject *>();
            disconnect(area, SIGNAL(heightRatioChanged(qreal)), d->vertical, SLOT(setSize(qreal)));
            disconnect(area, SIGNAL(yPositionChanged(qreal)), d->vertical, SLOT(setPosition(qreal)));
        }

        d->vertical = vertical;

        if (vertical) {
            if (!vertical->parentItem())
                vertical->setParentItem(d->flickable);
            vertical->setOrientation(Qt::Vertical);

            QObjectPrivate::connect(vertical, &QQuickAbstractScrollBar::positionChanged, d, &QQuickScrollBarAttachedPrivate::scrollVertical);
            QObjectPrivate::connect(d->flickable, &QQuickFlickable::movingVerticallyChanged, d, &QQuickScrollBarAttachedPrivate::activateVertical);

            // TODO: export QQuickFlickableVisibleArea
            QObject *area = d->flickable->property("visibleArea").value<QObject *>();
            connect(area, SIGNAL(heightRatioChanged(qreal)), vertical, SLOT(setSize(qreal)));
            connect(area, SIGNAL(yPositionChanged(qreal)), vertical, SLOT(setPosition(qreal)));

            vertical->setSize(area->property("heightRatio").toReal());
            vertical->setPosition(area->property("yPosition").toReal());
        }
        emit verticalChanged();
    }
}

QT_END_NAMESPACE
