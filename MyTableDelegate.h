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
        // Determine if the cell is highlighted (in the same row/column as the selected cell)
        QModelIndex currentIndex = tableView->selectionModel()->currentIndex();
        bool highlightRow = tableView && currentIndex.row() == index.row();
        bool highlightCol = tableView && currentIndex.column() == index.column();
        bool isSelected = tableView && currentIndex == index;

        // Get the text of the selected cell
        QString selectedText = currentIndex.data().toString();
        QString cellText = index.data().toString();

        // Set the background color based on selection
        if (isSelected || highlightRow || highlightCol) {
            painter->fillRect(option.rect, QColor(235, 245, 231)); // Light green background for the selected row/column or selected cell
        }
        else {
            painter->fillRect(option.rect, QColor(238, 238, 238)); // Default background for unselected cells
        }

        // Set font properties
        QFont font = painter->font();
        if (cellText == selectedText) {
            font.setBold(true);
        }
        else {
            font.setBold(false);
        }
        painter->setFont(font);

        // Draw the text
        painter->setPen(Qt::black);
        painter->drawText(option.rect, Qt::AlignCenter, cellText);

        // Draw borders
        QRect rect = option.rect;
        QPen thickPen(Qt::black, 3);
        QPen normalPen(Qt::black, 1);
        QPen greenPen(QColor(106, 168, 79), 3);

        bool topThick = (index.row() == 3 || index.row() == 6);
        bool leftThick = (index.column() == 3 || index.column() == 6);
        bool bottomThick = (index.row() == 2 || index.row() == 5);
        bool rightThick = (index.column() == 2 || index.column() == 5);

        // Draw top border
        painter->setPen(topThick ? thickPen : (isSelected ? greenPen : normalPen));
        painter->drawLine(rect.topLeft(), rect.topRight());

        // Draw left border
        painter->setPen(leftThick ? thickPen : (isSelected ? greenPen : normalPen));
        painter->drawLine(rect.topLeft(), rect.bottomLeft());

        // Draw bottom border
        painter->setPen(bottomThick ? thickPen : (isSelected ? greenPen : normalPen));
        painter->drawLine(rect.bottomLeft(), rect.bottomRight());

        // Draw right border
        painter->setPen(rightThick ? thickPen : (isSelected ? greenPen : normalPen));
        painter->drawLine(rect.topRight(), rect.bottomRight());
    }

private:
    QTableView* tableView;
};

#endif // MYTABLEDELEGATE_H