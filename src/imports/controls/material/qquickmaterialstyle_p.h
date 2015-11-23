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

#ifndef QQUICKMATERIALSTYLE_P_H
#define QQUICKMATERIALSTYLE_P_H

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

#include <QtQml/qqml.h>
#include <QtGui/qcolor.h>
#include <QtCore/qobject.h>
#include <QtQuick/private/qquickitemchangelistener_p.h>

QT_BEGIN_NAMESPACE

class QQuickMaterialStylePrivate;

class QQuickMaterialStyle : public QObject, public QQuickItemChangeListener
{
    Q_OBJECT
    Q_PROPERTY(Theme theme READ theme WRITE setTheme RESET resetTheme NOTIFY themeChanged FINAL)
    Q_PROPERTY(Color primary READ primary WRITE setPrimary RESET resetPrimary NOTIFY primaryChanged FINAL)
    Q_PROPERTY(Color accent READ accent WRITE setAccent RESET resetAccent NOTIFY accentChanged FINAL)
    Q_PROPERTY(QColor accentColor READ accentColor NOTIFY accentChanged FINAL)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor primaryTextColor READ primaryTextColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor primaryHighlightedTextColor READ primaryHighlightedTextColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor secondaryTextColor READ secondaryTextColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor hintTextColor READ hintTextColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor textSelectionColor READ textSelectionColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor dropShadowColor READ dropShadowColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor dividerColor READ dividerColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor raisedButtonColor READ raisedButtonColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor raisedButtonHoverColor READ raisedButtonHoverColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor raisedButtonPressColor READ raisedButtonPressColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor raisedButtonDisabledColor READ raisedButtonDisabledColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor raisedHighlightedButtonColor READ raisedHighlightedButtonColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor raisedHighlightedButtonHoverColor READ raisedHighlightedButtonHoverColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor raisedHighlightedButtonPressColor READ raisedHighlightedButtonPressColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor raisedHighlightedButtonDisabledColor READ raisedHighlightedButtonDisabledColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor flatButtonPressColor READ flatButtonPressColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor flatButtonFocusColor READ flatButtonFocusColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor frameColor READ frameColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor checkBoxUncheckedRippleColor READ checkBoxUncheckedRippleColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor checkBoxCheckedRippleColor READ checkBoxCheckedRippleColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor switchUncheckedTrackColor READ switchUncheckedTrackColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor switchCheckedTrackColor READ switchCheckedTrackColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor switchUncheckedHandleColor READ switchUncheckedHandleColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor switchCheckedHandleColor READ switchCheckedHandleColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor switchDisabledTrackColor READ switchDisabledTrackColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor switchDisabledHandleColor READ switchDisabledHandleColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor scrollBarColor READ scrollBarColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor scrollBarPressedColor READ scrollBarPressedColor NOTIFY paletteChanged FINAL)
    Q_PROPERTY(QColor drawerBackgroundColor READ drawerBackgroundColor NOTIFY paletteChanged FINAL)

public:
    enum Theme {
        Light,
        Dark
    };

    enum Color {
        Red,
        Pink,
        Purple,
        DeepPurple,
        Indigo,
        Blue,
        LightBlue,
        Cyan,
        Teal,
        Green,
        LightGreen,
        Lime,
        Yellow,
        Amber,
        Orange,
        DeepOrange,
        Brown,
        Grey,
        BlueGrey
    };

    enum Shade {
        Shade50,
        Shade100,
        Shade200,
        Shade300,
        Shade400,
        Shade500,
        Shade600,
        Shade700,
        Shade800,
        Shade900,
        ShadeA100,
        ShadeA200,
        ShadeA400,
        ShadeA700,
    };

    Q_ENUM(Theme)
    Q_ENUM(Color)
    Q_ENUM(Shade)

    explicit QQuickMaterialStyle(QObject *parent = Q_NULLPTR);
    ~QQuickMaterialStyle();

    static QQuickMaterialStyle *qmlAttachedProperties(QObject *object);

    Theme theme() const;
    void setTheme(Theme theme);
    void inheritTheme(Theme theme);
    void resetTheme();

    QColor primaryColorLight() const;

    Color primary() const;
    void setPrimary(Color color);
    void inheritPrimary(Color color);
    void resetPrimary();

    QColor primaryColorDark() const;

    Color accent() const;
    void setAccent(Color color);
    void inheritAccent(Color color);
    void resetAccent();

    QColor accentColor() const;
    QColor backgroundColor() const;
    QColor primaryTextColor() const;
    QColor primaryHighlightedTextColor() const;
    QColor secondaryTextColor() const;
    QColor hintTextColor() const;
    QColor textSelectionColor() const;
    QColor dropShadowColor() const;
    QColor dividerColor() const;
    QColor raisedButtonColor() const;
    QColor raisedButtonHoverColor() const;
    QColor raisedButtonPressColor() const;
    QColor raisedButtonDisabledColor() const;
    QColor raisedHighlightedButtonColor() const;
    QColor raisedHighlightedButtonHoverColor() const;
    QColor raisedHighlightedButtonPressColor() const;
    QColor raisedHighlightedButtonDisabledColor() const;
    QColor flatButtonPressColor() const;
    QColor flatButtonFocusColor() const;
    QColor frameColor() const;
    QColor checkBoxUncheckedRippleColor() const;
    QColor checkBoxCheckedRippleColor() const;
    QColor switchUncheckedTrackColor() const;
    QColor switchCheckedTrackColor() const;
    QColor switchUncheckedHandleColor() const;
    QColor switchCheckedHandleColor() const;
    QColor switchDisabledTrackColor() const;
    QColor switchDisabledHandleColor() const;
    QColor scrollBarColor() const;
    QColor scrollBarPressedColor() const;
    QColor drawerBackgroundColor() const;

    Q_INVOKABLE QColor color(Color color, Shade shade) const;

Q_SIGNALS:
    void themeChanged();
    void primaryChanged();
    void accentChanged();
    void paletteChanged();

protected:
    void reparent(QQuickMaterialStyle *theme);
    void itemParentChanged(QQuickItem *item, QQuickItem *parent) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(QQuickMaterialStyle)
    Q_DECLARE_PRIVATE(QQuickMaterialStyle)
};

QT_END_NAMESPACE

QML_DECLARE_TYPEINFO(QQuickMaterialStyle, QML_HAS_ATTACHED_PROPERTIES)

#endif // QQUICKMATERIALSTYLE_P_H