#ifndef MYTABLEDELEGATE_H
#define MYTABLEDELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>
#include <QTableView>

class MyTableDelegate : public QStyledItemDelegate {
    Q_OBJECT

public:
    explicit MyTableDelegate(QTableView* tableView = nullptr, QObject* parent = nullptr)
        : QStyledItemDelegate(parent), tableView(tableView) {}

    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override {
        // Determine if the cell should have a special background
        bool highlightRow = tableView && tableView->selectionModel()->currentIndex().row() == index.row();
        bool highlightCol = tableView && tableView->selectionModel()->currentIndex().column() == index.column();

        // Set the background color based on selection
        if (highlightRow || highlightCol) {
            painter->fillRect(option.rect, QColor(173, 255, 47)); // Light green background for the selected row/column
        }
        else {
            painter->fillRect(option.rect, QColor(255, 255, 255)); // White background for unselected cells
        }

        // Draw the text
        painter->setPen(Qt::black);
        painter->drawText(option.rect, Qt::AlignCenter, index.data().toString());

        // Draw borders
        QRect rect = option.rect;
        QPen thickPen(Qt::black, 3);
        QPen normalPen(Qt::black, 1);

        bool topThick = (index.row() == 3 || index.row() == 6);
        bool leftThick = (index.column() == 3 || index.column() == 6);
        bool bottomThick = (index.row() == 2 || index.row() == 5);
        bool rightThick = (index.column() == 2 || index.column() == 5);

        // Draw top border
        painter->setPen(topThick ? thickPen : normalPen);
        painter->drawLine(rect.topLeft(), rect.topRight());

        // Draw left border
        painter->setPen(leftThick ? thickPen : normalPen);
        painter->drawLine(rect.topLeft(), rect.bottomLeft());

        // Draw bottom border
        painter->setPen(bottomThick ? thickPen : normalPen);
        painter->drawLine(rect.bottomLeft(), rect.bottomRight());

        // Draw right border
        painter->setPen(rightThick ? thickPen : normalPen);
        painter->drawLine(rect.topRight(), rect.bottomRight());
    }

private:
    QTableView* tableView;
};

#endif // MYTABLEDELEGATE_H