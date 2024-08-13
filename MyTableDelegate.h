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

        //determine the cells of the same square as the selected cell
        bool highlightSquare = false;
        if (currentIndex.isValid()) {
			int selectedRow = currentIndex.row();
			int selectedCol = currentIndex.column();
			int selectedSquare = (selectedRow / 3) * 3 + selectedCol / 3;

			int row = index.row();
			int col = index.column();
			int square = (row / 3) * 3 + col / 3;

			highlightSquare = square == selectedSquare;
		}

        // Set the background color based on selection
        if (isSelected || highlightRow || highlightCol || highlightSquare) {
			painter->fillRect(option.rect, QColor(235, 245, 231)); // Light green background for the selected row/column or selected cell
		}
		else {
			painter->fillRect(option.rect, QColor(238, 238, 238)); // Default background for unselected cells
		}

        // Get the text of the selected cell
        QString selectedText = currentIndex.data().toString();
        QString cellText = index.data().toString();

        //set the background to light green to cells with the same value other than 0 as the selected cell
        if (cellText == selectedText && cellText != "") {
			painter->fillRect(option.rect, QColor(235, 245, 231));
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

        // Set the pen color based on the initial value
        QVariant foreground = index.data(Qt::ForegroundRole);
        if (foreground.canConvert<QColor>()) {
            painter->setPen(foreground.value<QColor>());
        }
        else {
            painter->setPen(Qt::black);
        }

        // Draw the text
        painter->drawText(option.rect, Qt::AlignCenter, cellText);

        // Draw borders
        QRect rect = option.rect;
        QPen thickPen(Qt::black, 3);
        QPen normalPen(Qt::black, 1);
        QPen purplePen(QColor(109, 81, 177), 4);

        bool topThick = (index.row() == 3 || index.row() == 6);
        bool leftThick = (index.column() == 3 || index.column() == 6);
        bool bottomThick = (index.row() == 2 || index.row() == 5);
        bool rightThick = (index.column() == 2 || index.column() == 5);

        // Draw top border
        painter->setPen(isSelected ? purplePen : (topThick ? thickPen : normalPen));
        painter->drawLine(rect.topLeft(), rect.topRight());

        // Draw left border
        painter->setPen(isSelected ? purplePen : (leftThick ? thickPen : normalPen));
        painter->drawLine(rect.topLeft(), rect.bottomLeft());

        // Draw bottom border
        painter->setPen(isSelected ? purplePen : (bottomThick ? thickPen : normalPen));
        painter->drawLine(rect.bottomLeft(), rect.bottomRight());

        // Draw right border
        painter->setPen(isSelected ? purplePen : (rightThick ? thickPen : normalPen));
        painter->drawLine(rect.topRight(), rect.bottomRight());
    }

private:
    QTableView* tableView;
};

#endif // MYTABLEDELEGATE_H