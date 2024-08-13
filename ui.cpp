#include "ui.h"

void MainWindow::initMainWindow() {
    QHBoxLayout* layout = new QHBoxLayout;
    this->setLayout(layout);
    //set the minimum size of the window
    this->setMinimumSize(400, 400);

    QLabel* label = new QLabel("Sudoku");
    //make the label bigger
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
    int upper_bound = 0;
    std::uniform_int_distribution<> distribution(0, upper_bound);
    int randomMultipleOf18 = distribution(gen) * 18;
    return randomMultipleOf18;
}

void MainWindow::connectSignalsMain() {
    QObject::connect(btn_easy, &QPushButton::clicked, [this]() {
        Repo* repo = Repo::getInstance("sudoku.txt", "easy.txt", this->generateRandomNumber());
        CentralWindow* central = new CentralWindow(*repo);
        this->hide();
        central->show();
        });
    QObject::connect(btn_medium, &QPushButton::clicked, [this]() {
        Repo* repo = Repo::getInstance("sudoku.txt", "medium.txt", this->generateRandomNumber());
        CentralWindow* central = new CentralWindow(*repo);
        this->hide();
        central->show();
        });
    QObject::connect(btn_hard, &QPushButton::clicked, [this]() {
        Repo* repo = Repo::getInstance("sudoku.txt", "hard.txt", this->generateRandomNumber());
        CentralWindow* central = new CentralWindow(*repo);
        this->hide();
        central->show();
        });
    QObject::connect(btn_expert, &QPushButton::clicked, [this]() {
        Repo* repo = Repo::getInstance("sudoku.txt", "expert.txt", this->generateRandomNumber());
        CentralWindow* central = new CentralWindow(*repo);
        this->hide();
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

    QFont font = QFont("Helvetica", 16, 10, false);
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

    btn_1->setStyleSheet("background-color: white;"
        "border-radius: 4px;"
        "font-size: 18px;");
    btn_2->setStyleSheet("background-color: white;"
        "border-radius: 4px;"
        "font-size: 18px;");
    btn_3->setStyleSheet("background-color: white;"
        "border-radius: 4px;"
        "font-size: 18px;");
    btn_4->setStyleSheet("background-color: white;"
        "border-radius: 4px;"
        "font-size: 18px;");
    btn_5->setStyleSheet("background-color: white;"
        "border-radius: 4px;"
        "font-size: 18px;");
    btn_6->setStyleSheet("background-color: white;"
        "border-radius: 4px;"
        "font-size: 18px;");
    btn_7->setStyleSheet("background-color: white;"
        "border-radius: 4px;"
        "font-size: 18px;");
    btn_8->setStyleSheet("background-color: white;"
        "border-radius: 4px;"
        "font-size: 18px;");
    btn_9->setStyleSheet("background-color: white;"
        "border-radius: 4px;"
        "font-size: 18px;");

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

    btnLayout->addSpacing(200);

    btnLayout->addLayout(btn1Layout);
    btnLayout->addLayout(btn2Layout);
    btnLayout->addLayout(btn3Layout);
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
        "QTableView::item:selected {"
        "    selection-background-color: #eeeeee;"
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

void CentralWindow::updateSelectedCell(int value) {
    QMessageBox msg;
    QModelIndex currentIndex = table->selectionModel()->currentIndex();

    if (currentIndex.isValid()) {
        int row = currentIndex.row();
        int column = currentIndex.column();

        qDebug() << "Selected cell: " << row << " " << column;

        // Check if the cell is editable
        Qt::ItemFlags flags = model->flags(currentIndex);
        if (!(flags & Qt::ItemIsEditable)) {
            QMessageBox::warning(this, "Error", "Selected cell cannot be edited.");
            return;
        }

        try {
            repo.modificaRepo(row, column, value);
            model->setData(currentIndex, value, Qt::EditRole);
        }
        catch (RepoException& mesaj) {
            msg.warning(this, "Warning", QString::fromStdString(mesaj.get_mesaj()));
        }
    }
}