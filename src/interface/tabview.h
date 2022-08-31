/*
 * Copyright (C) 2021 ~ 2021 Deepin Technology Co., Ltd.
 *
 * Author:     caixiangrong <caixiangrong@uniontech.com>
 *
 * Maintainer: caixiangrong <caixiangrong@uniontech.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef TABVIEW_H
#define TABVIEW_H
#include "interface/namespace.h"
#include <qglobal.h>
#include <QAbstractItemView>

namespace DCC_NAMESPACE {

class TabViewPrivate;
class TabView : public QAbstractItemView
{
    Q_OBJECT
    Q_PROPERTY(int spacing READ spacing WRITE setSpacing)
    Q_PROPERTY(QSize gridSize READ gridSize WRITE setGridSize)
    Q_PROPERTY(Qt::Alignment alignment READ alignment WRITE setAlignment)

public:
    explicit TabView(QWidget *parent = nullptr);
    virtual ~TabView() override;

    void setSpacing(int space);
    int spacing() const;

    void setGridSize(const QSize &size);
    QSize gridSize() const;

    void setAlignment(Qt::Alignment alignment);
    Qt::Alignment alignment() const;

    QRect visualRect(const QModelIndex &index) const override;
    void scrollTo(const QModelIndex &index, ScrollHint hint = EnsureVisible) override;
    QModelIndex indexAt(const QPoint &p) const override;

protected:
    QModelIndex moveCursor(CursorAction cursorAction, Qt::KeyboardModifiers modifiers) override;
    int horizontalOffset() const override;
    int verticalOffset() const override;

    bool isIndexHidden(const QModelIndex &index) const override;
    QRegion visualRegionForSelection(const QItemSelection &selection) const override;
    void setSelection(const QRect &rect, QItemSelectionModel::SelectionFlags command) override;

    void updateGeometries() override;

    void dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles = QVector<int>()) override;
    void rowsInserted(const QModelIndex &parent, int start, int end) override;
    void rowsAboutToBeRemoved(const QModelIndex &parent, int start, int end) override;

protected:
    void paintEvent(QPaintEvent *e) override;
    bool viewportEvent(QEvent *event) override;
    void wheelEvent(QWheelEvent *e) override;

private:
    TabViewPrivate *const d_ptr;
    Q_DECLARE_PRIVATE(TabView)
    Q_DISABLE_COPY(TabView)
};

}

#endif // TABVIEW_H