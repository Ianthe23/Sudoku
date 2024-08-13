#ifndef UI_H_
#define UI_H_

#include "repo.h"
#include "MyTableModel.h"

#include <QMainWindow>
#include <QTableView>
#include <QTableWidget>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QDebug>
#include <iostream>
#include <random>
#include <QTimer>
#include <iomanip>
#include <sstream>
#include <QResizeEvent>
#include <QItemSelectionModel>
#include <QAbstractItemView>
#include <QHeaderView>
#include <QGraphicsDropShadowEffect>
#include <QMediaPlayer>
#include <QAudioOutput>

class MainWindow : public QWidget {
public:
    MainWindow() {
        this->initMainWindow();
        this->connectSignalsMain();
    }
private:
    QPushButton* btn_easy = new QPushButton("Easy");
    QPushButton* btn_medium = new QPushButton("Medium");
    QPushButton* btn_hard = new QPushButton("Hard");
    QPushButton* btn_expert = new QPushButton("Expert");

    void initMainWindow();
    void connectSignalsMain();
    int generateRandomNumber();
};

class CentralWindow : public QWidget {
    Q_OBJECT
public:
    CentralWindow(Repo& repo) : repo{ repo } {
        this->initCentralWindow();
        loadTable(repo.getSudoku());

        // Ensures that only one cell is selected at a time
        table->setSelectionMode(QAbstractItemView::SingleSelection);
        table->setSelectionBehavior(QAbstractItemView::SelectItems);

        // Connect the resize signal to the slot
        connect(this, &CentralWindow::resized, this, &CentralWindow::adjustSizes);

        // Connect the selection changed signal to the slot
        connect(table->selectionModel(), &QItemSelectionModel::selectionChanged, [this]() {
            table->viewport()->update();
            });

        // Ensure sizes are adjusted initially
        QTimer::singleShot(0, this, &CentralWindow::adjustSizesFirst);

        // Connect button signals to the slots
        connect(btn_1, &QPushButton::clicked, this, [this]() { updateSelectedCell(1); });
        connect(btn_2, &QPushButton::clicked, this, [this]() { updateSelectedCell(2); });
        connect(btn_3, &QPushButton::clicked, this, [this]() { updateSelectedCell(3); });
        connect(btn_4, &QPushButton::clicked, this, [this]() { updateSelectedCell(4); });
        connect(btn_5, &QPushButton::clicked, this, [this]() { updateSelectedCell(5); });
        connect(btn_6, &QPushButton::clicked, this, [this]() { updateSelectedCell(6); });
        connect(btn_7, &QPushButton::clicked, this, [this]() { updateSelectedCell(7); });
        connect(btn_8, &QPushButton::clicked, this, [this]() { updateSelectedCell(8); });
        connect(btn_9, &QPushButton::clicked, this, [this]() { updateSelectedCell(9); });

        // Initialize and start the timer
        timeElapsed = 0;
        connect(timer, &QTimer::timeout, this, &CentralWindow::updateTimeLabel);
        timer->start(1000);

        // Initialize QMediaPlayer for background music
        player = new QMediaPlayer(this);
        QAudioOutput* audioOutput = new QAudioOutput(this);
        player->setAudioOutput(audioOutput);
        player->setSource(QUrl::fromLocalFile("music/chinese-song.mp3"));
        audioOutput->setVolume(0.5);
        player->play();

    }

private:
    Repo& repo;
    MyTableModel* model;
    QTableView* table = new QTableView;
    MyTableDelegate* delegate;

    QMediaPlayer* player;

    // Variable for time elapsed
    int timeElapsed;
    // Timer for time elapsed
    QTimer* timer = new QTimer(this);
    // Label for time elapsed
    QLabel* timeLabel = new QLabel("Time elapsed: 00:00");

    // Label for mistakes out of three
    QLabel* mistakesLabel = new QLabel("Mistakes: 0/3");

    QPushButton* btn_1 = new QPushButton("1");
    QPushButton* btn_2 = new QPushButton("2");
    QPushButton* btn_3 = new QPushButton("3");
    QPushButton* btn_4 = new QPushButton("4");
    QPushButton* btn_5 = new QPushButton("5");
    QPushButton* btn_6 = new QPushButton("6");
    QPushButton* btn_7 = new QPushButton("7");
    QPushButton* btn_8 = new QPushButton("8");
    QPushButton* btn_9 = new QPushButton("9");

    void initCentralWindow();
    void loadTable(Sudoku sudoku);
    void updateSelectedCell(int value);
    void showMessageBox(const QString& title, const QString& message, QMessageBox::Icon icon = QMessageBox::NoIcon);
    void drawBambooShapes(QPainter* painter);


    QString formatTime(int totalSeconds) {
        int minutes = totalSeconds / 60;
        int seconds = totalSeconds % 60;
        QString formattedTime = QString("%1:%2")
            .arg(minutes, 2, 10, QChar('0'))
            .arg(seconds, 2, 10, QChar('0'));
        return formattedTime;
    }
signals:
    void resized();

protected:
    void resizeEvent(QResizeEvent* event) override {
        emit resized();
        QWidget::resizeEvent(event);

        qDebug() << "Sudoku window size:" << this->width() << "x" << this->height();
    }

    void paintEvent(QPaintEvent* event) override;

private slots:
    void adjustSizesFirst() {
        int totalWidth = 546;
        int totalHeight = 474;

        qDebug() << "Table size:" << totalWidth << "x" << totalHeight;

        for (int i = 0; i < model->columnCount(); ++i) {
            table->setColumnWidth(i, totalWidth / 9);
            qDebug() << "Column " << i << " width: " << totalWidth / 9;
        }

        for (int i = 0; i < model->rowCount(); ++i) {
            table->setRowHeight(i, totalHeight / 9);
            qDebug() << "Row " << i << " height: " << totalHeight / 9;
        }
    }

    void adjustSizes() {
        int totalWidth = table->viewport()->width();
        int totalHeight = table->viewport()->height();

        qDebug() << "Table size:" << totalWidth << "x" << totalHeight;

        for (int i = 0; i < model->columnCount(); ++i) {
            table->setColumnWidth(i, totalWidth / 9);
            qDebug() << "Column " << i << " width: " << totalWidth / 9;
        }

        for (int i = 0; i < model->rowCount(); ++i) {
            table->setRowHeight(i, totalHeight / 9);
            qDebug() << "Row " << i << " height: " << totalHeight / 9;
        }
    }

    void updateTimeLabel() {
        timeElapsed++;
        timeLabel->setText(QString("Time elapsed: %1").arg(formatTime(timeElapsed)));
    }
};

#endif /* UI_H_ */