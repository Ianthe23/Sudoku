#ifndef CUSTOMWIDGET_H
#define CUSTOMWIDGET_H

#include <QWidget>
#include <QTableView>
#include <QVBoxLayout>
#include "MyTableModel.h"
#include "MyTableDelegate.h"

class CustomWidget : public QWidget {
    Q_OBJECT

public:
    CustomWidget(QWidget* parent = nullptr) : QWidget(parent) {
        tableView = new QTableView(this);
        model = new MyTableModel(this);
        delegate = new MyTableDelegate(this);

        tableView->setModel(model);
        tableView->setItemDelegate(delegate);
        tableView->horizontalHeader()->setVisible(false);
        tableView->verticalHeader()->setVisible(false);
        tableView->setStyleSheet(
            "QTableView {"
            "   border: 5px solid black;"          // Create a thick outer border
            "   gridline-color: black;"            // Set grid line color
            "}"
        );

        QVBoxLayout* layout = new QVBoxLayout(this);
        layout->addWidget(tableView);
        setLayout(layout);

        connect(this, &CustomWidget::resized, this, &CustomWidget::adjustSizes);
    }



private:
    QTableView* tableView;
    MyTableModel* model;

};

#endif // CUSTOMWIDGET_H