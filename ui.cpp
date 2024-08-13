#include "ui.h"

void MainWindow::initMainWindow() {
    QHBoxLayout* layout = new QHBoxLayout;
    this->setLayout(layout);
    // Set the minimum size of the window
    this->setMinimumSize(400, 400);

    QLabel* label = new QLabel("Sudoku");
    // Make the label bigger
    QFont f = label->font();
    f.setPointSize(20);
    label->setFont(f);
    label->setAlignment(Qt::AlignCenter);

    QVBoxLayout* btnLayout = new QVBoxLayout;
    layout->addLayout(btnLayout);
    btnLayout->addWidget(label);
    btnLayout->addWidget(btn_easy);
    btnLayout->addWidget(btn_medium);
    btnLayout->addWidget(btn_hard);
    btnLayout->addWidget(btn_expert);
}

int MainWindow::generateRandomNumber() {
    std::random_device rd;
    std::mt19937 gen(rd());
    int upper_bound = 2;
    std::uniform_int_distribution<> distribution(0, upper_bound);
    int randomMultipleOf18 = distribution(gen) * 18;
    qDebug() << "Random number: " << randomMultipleOf18;
    return randomMultipleOf18;
}

void MainWindow::connectSignalsMain() {
    QObject::connect(btn_easy, &QPushButton::clicked, [this]() {
        Repo::resetInstance();
        Repo* repo = Repo::getInstance("sudoku.txt", "easy.txt", this->generateRandomNumber());
        CentralWindow* central = new CentralWindow(*repo);
        this->close();
        central->show();
        });
    QObject::connect(btn_medium, &QPushButton::clicked, [this]() {
        Repo::resetInstance();
        Repo* repo = Repo::getInstance("sudoku.txt", "medium.txt", this->generateRandomNumber());
        CentralWindow* central = new CentralWindow(*repo);
        this->close();
        central->show();
        });
    QObject::connect(btn_hard, &QPushButton::clicked, [this]() {
        Repo::resetInstance();
        Repo* repo = Repo::getInstance("sudoku.txt", "hard.txt", this->generateRandomNumber());
        CentralWindow* central = new CentralWindow(*repo);
        this->close();
        central->show();
        });
    QObject::connect(btn_expert, &QPushButton::clicked, [this]() {
        Repo::resetInstance();
        Repo* repo = Repo::getInstance("sudoku.txt", "expert.txt", this->generateRandomNumber());
        CentralWindow* central = new CentralWindow(*repo);
        this->close();
        central->show();
        });
}

void CentralWindow::initCentralWindow() {
    QHBoxLayout* layout = new QHBoxLayout;
    this->setLayout(layout);

    QPalette palette = QPalette();
    palette.setColor(QPalette::Window, "#f3f6f4");

    // Create a gradient for the fading effect
    QLinearGradient gradient(this->width() / 2, 0, this->width(), 0);
    gradient.setColorAt(0, QColor("#f3f6f4")); // Same color as background
    gradient.setColorAt(1, QColor("#b6d7a8")); // color

    // Set the gradient as the brush for the background
    palette.setBrush(QPalette::Window, QBrush(gradient));

    QFont font = QFont("Helvetica", 12, 10, false);
    QFont boldFont = font;
    boldFont.setBold(true);

    this->setAutoFillBackground(true); //
    this->setPalette(palette);

    this->setFont(font);

    this->setStyleSheet("color: black;");

    this->setMinimumSize(782, 502);

    delegate = new MyTableDelegate(table);

    QVBoxLayout* tableLayout = new QVBoxLayout;
    layout->addLayout(tableLayout);

    table->resizeColumnsToContents();
    tableLayout->addWidget(table);

    QVBoxLayout* btnLayout = new QVBoxLayout;
    layout->addLayout(btnLayout);


    QHBoxLayout* btn1Layout = new QHBoxLayout;
    QHBoxLayout* btn2Layout = new QHBoxLayout;
    QHBoxLayout* btn3Layout = new QHBoxLayout;

    auto createShadowEffect = [](QPushButton* button) {
        QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect;
        shadowEffect->setColor(QColor(0, 0, 0, 160)); // Slightly transparent black
        shadowEffect->setOffset(4, 4); // Slightly to the right and down
        shadowEffect->setBlurRadius(15); // Blur radius
        button->setGraphicsEffect(shadowEffect);
        };

    btn_1->setStyleSheet(
        "QPushButton { background-color: white; border-radius: 4px; font-size: 20px; }"
        "QPushButton:hover { background-color: grey; }"
    );
    btn_2->setStyleSheet(
        "QPushButton { background-color: white; border-radius: 4px; font-size: 20px; }"
        "QPushButton:hover { background-color: grey; }"
    );
    btn_3->setStyleSheet(
        "QPushButton { background-color: white; border-radius: 4px; font-size: 20px; }"
        "QPushButton:hover { background-color: grey; }"
    );
    btn_4->setStyleSheet(
        "QPushButton { background-color: white; border-radius: 4px; font-size: 20px; }"
        "QPushButton:hover { background-color: grey; }"
    );
    btn_5->setStyleSheet(
        "QPushButton { background-color: white; border-radius: 4px; font-size: 20px; }"
        "QPushButton:hover { background-color: grey; }"
    );
    btn_6->setStyleSheet(
        "QPushButton { background-color: white; border-radius: 4px; font-size: 20px; }"
        "QPushButton:hover { background-color: grey; }"
    );
    btn_7->setStyleSheet(
        "QPushButton { background-color: white; border-radius: 4px; font-size: 20px; }"
        "QPushButton:hover { background-color: grey; }"
    );
    btn_8->setStyleSheet(
        "QPushButton { background-color: white; border-radius: 4px; font-size: 20px; }"
        "QPushButton:hover { background-color: grey; }"
    );
    btn_9->setStyleSheet(
        "QPushButton { background-color: white; border-radius: 4px; font-size: 20px; }"
        "QPushButton:hover { background-color: grey; }"
    );

    createShadowEffect(btn_1);
    createShadowEffect(btn_2);
    createShadowEffect(btn_3);
    createShadowEffect(btn_4);
    createShadowEffect(btn_5);
    createShadowEffect(btn_6);
    createShadowEffect(btn_7);
    createShadowEffect(btn_8);
    createShadowEffect(btn_9);

    btn_1->setFixedSize(50, 50);
    btn_2->setFixedSize(50, 50);
    btn_3->setFixedSize(50, 50);
    btn_4->setFixedSize(50, 50);
    btn_5->setFixedSize(50, 50);
    btn_6->setFixedSize(50, 50);
    btn_7->setFixedSize(50, 50);
    btn_8->setFixedSize(50, 50);
    btn_9->setFixedSize(50, 50);

    btn1Layout->addSpacing(20);
    btn1Layout->addWidget(btn_1);
    btn1Layout->addWidget(btn_2);
    btn1Layout->addWidget(btn_3);
    btn1Layout->addSpacing(20);

    btn2Layout->addSpacing(20);
    btn2Layout->addWidget(btn_4);
    btn2Layout->addWidget(btn_5);
    btn2Layout->addWidget(btn_6);
    btn2Layout->addSpacing(20);

    btn3Layout->addSpacing(20);
    btn3Layout->addWidget(btn_7);
    btn3Layout->addWidget(btn_8);
    btn3Layout->addWidget(btn_9);
    btn3Layout->addSpacing(20);

    // make the text of the timer label bold
    timeLabel->setFont(boldFont);
    // make the bottom border of the label white
    timeLabel->setStyleSheet("border-bottom: 1px solid white;");
    // Add the timer label to the button layout
    btnLayout->addWidget(timeLabel, 0, Qt::AlignHCenter);
    // make the text of the mistakes label bold
    mistakesLabel->setFont(boldFont);
    // Add the mistakes label to the button layout
    btnLayout->addWidget(mistakesLabel, 0, Qt::AlignHCenter);
    btnLayout->addSpacing(200);
    btnLayout->addLayout(btn1Layout);
    btnLayout->addLayout(btn2Layout);
    btnLayout->addLayout(btn3Layout);
    btnLayout->addSpacing(20);
}

void CentralWindow::loadTable(Sudoku sudoku) {
    model = new MyTableModel(sudoku);
    table->setModel(model);

    table->horizontalHeader()->setVisible(false);
    table->verticalHeader()->setVisible(false);

    table->setStyleSheet(
        "QTableView {"
        "   border: 5px solid black;"
        "   gridline-color: black;"
        "   font-size: 20px;"
        "}"
    );

    table->setItemDelegate(delegate);

    table->resizeColumnsToContents();
    table->resizeRowsToContents();

    // Set selection mode and behavior
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setSelectionBehavior(QAbstractItemView::SelectItems);

    // Ensure sizes are adjusted initially
    adjustSizes();
}

void CentralWindow::showMessageBox(const QString& title, const QString& message, QMessageBox::Icon icon) {
    QMessageBox messageBox(this);
    messageBox.setIcon(icon);
    messageBox.setWindowTitle(title);
    messageBox.setText(message);
    messageBox.setStyleSheet("QMessageBox { background-color: white; color: black; }"
        "QPushButton { background-color: rgb(206, 206, 206); color: black; border-radius: 3px; padding: 10px 25px 10px 25px; }");
    messageBox.exec();
}

void CentralWindow::updateSelectedCell(int value) {
    QModelIndex currentIndex = table->selectionModel()->currentIndex();

    if (currentIndex.isValid()) {
        int row = currentIndex.row();
        int column = currentIndex.column();

        qDebug() << "Selected cell: " << row << " " << column;

        // Check if the cell is editable
        Qt::ItemFlags flags = model->flags(currentIndex);
        if (!(flags & Qt::ItemIsEditable)) {
            showMessageBox("Error", "Selected cell cannot be edited.", QMessageBox::Warning);
            return;
        }

        try {
            repo.modificaRepo(row, column, value);
            model->setData(currentIndex, value, Qt::EditRole);
            table->viewport()->update();
        }
        catch (RepoException& mesaj) {
            showMessageBox("Warning", QString::fromStdString(mesaj.get_mesaj()), QMessageBox::Warning);
            // Update the mistakes label
            mistakesLabel->setText("Mistakes: " + QString::number(repo.getMistakes()) + "/3");
        }
    }

    // Check if the game is over
    if (repo.isGameOver()) {
        timer->stop();
        showMessageBox("Game Over", "Try again!", QMessageBox::Information);
        this->close();
        // Return to the main window
        MainWindow* main = new MainWindow;
        main->show();
    }

    // Check if the game is won
    else if (repo.isGameWon()) {
        timer->stop();
        showMessageBox("Game Won", "Congratulations!", QMessageBox::Information);
        this->close();
        // Return to the main window
        MainWindow* main = new MainWindow;
        main->show();
    }
}

void CentralWindow::paintEvent(QPaintEvent* event) {
    QWidget::paintEvent(event);

    QPainter painter(this);
    drawBambooShapes(&painter);
}

void CentralWindow::drawBambooShapes(QPainter* painter) {
    // draw a thick white line to separate the 2 labels, time and mistake
    QPen thickWhitePen(QColor(255, 255, 255), 3);  // Thick white line
    painter->setPen(thickWhitePen);

    // Adjust the y-coordinate to move the line lower
    int yCoordinate = 60;  // Adjust this value as needed
    painter->drawLine(0, yCoordinate, this->width(), yCoordinate);

    QPen pen(QColor(0, 100, 0));  // Dark green color for bamboo
    painter->setPen(pen);
    painter->setBrush(QBrush(QColor(0, 155, 0)));  // Light green color for bamboo

    QPoint bottomRight = rect().bottomRight();

    // Draw the first bamboo stalk
    int x1 = bottomRight.x() - 100;  // Position for the first bamboo
    int y1 = bottomRight.y() - 150;  // Height for the first bamboo
    for (int i = 0; i < 6; ++i) {  // Number of segments for the first bamboo
        painter->drawRect(x1, y1 - i * 30, 20, 30);
    }

    // Draw the second bamboo stalk (shorter)
    int x2 = x1 - 40;  // Position for the second bamboo
    int y2 = bottomRight.y() - 120;  // Height for the second bamboo
    for (int i = 0; i < 4; ++i) {  // Number of segments for the second bamboo
        painter->drawRect(x2, y2 - i * 30, 20, 30);
    }

    // Draw the third bamboo stalk (taller)
    int x3 = x1 + 40;  // Position for the third bamboo
    int y3 = bottomRight.y() - 200;  // Height for the third bamboo
    for (int i = 0; i < 7; ++i) {  // Number of segments for the third bamboo
        painter->drawRect(x3, y3 - i * 30, 20, 30);
    }

    // Draw leaves on the first bamboo
    QBrush leafBrush(QColor(34, 139, 34));
    painter->setBrush(leafBrush);
    painter->drawEllipse(x1 - 15, y1 - 90, 30, 10);  // Left leaf
    painter->drawEllipse(x1 + 5, y1 - 90, 30, 10);   // Right leaf
    painter->drawEllipse(x1 - 5, y1 - 120, 30, 10);  // Top leaf

    // Draw leaves on the second bamboo
    painter->drawEllipse(x2 - 15, y2 - 60, 30, 10);  // Left leaf
    painter->drawEllipse(x2 + 5, y2 - 60, 30, 10);   // Right leaf
    painter->drawEllipse(x2 - 5, y2 - 90, 30, 10);   // Top leaf

    // Draw leaves on the third bamboo
    painter->drawEllipse(x3 - 15, y3 - 150, 30, 10);  // Left leaf
    painter->drawEllipse(x3 + 5, y3 - 150, 30, 10);   // Right leaf
    painter->drawEllipse(x3 - 5, y3 - 180, 30, 10);   // Top leaf

    // Additional leaves on the third (tallest) bamboo, a bit lower
    painter->drawEllipse(x3 - 15, y3 - 90, 30, 10);  // Left leaf
    painter->drawEllipse(x3 + 5, y3 - 90, 30, 10);   // Right leaf
    painter->drawEllipse(x3 - 5, y3 - 120, 30, 10);   // Top leaf

    painter->drawEllipse(x3 - 15, y3, 30, 10);  // Left leaf
    painter->drawEllipse(x3 + 5, y3, 30, 10);   // Right leaf
}