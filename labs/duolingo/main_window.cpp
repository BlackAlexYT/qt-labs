#include "main_window.h"
#include <QMainWindow>
#include <QStackedWidget>
#include <QProgressBar>
#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include <QVBoxLayout>
#include <QMenuBar>
#include <QInputDialog>
#include <QMessageBox>


MainWindow::MainWindow() {
    SetupMenu();
    SetupUI();
    ApplyStyles();
    UpdateEXP();
}

void MainWindow::SetupMenu() {
    QMenu *settings_menu = menuBar()->addMenu("Settings");
    QAction *difficulty_action = settings_menu->addAction("Select Difficulty");
    connect(difficulty_action, &QAction::triggered, this, &MainWindow::OnSelectDifficulty);
}

MainWindow::~MainWindow() {
}

void MainWindow::SetupUI() {
    central_widget_ = new QWidget(this);
    setCentralWidget(central_widget_);

    level_circle_ = new QLabel("Level: 1", this);
    level_circle_->setAlignment(Qt::AlignCenter);
    level_circle_->setObjectName("levelCircle");
    level_circle_->setFixedSize(160, 160);

    learn_german_label_ = new QLabel("LEARN GERMAN", this);
    learn_german_label_->setAlignment(Qt::AlignCenter);
    learn_german_label_->setObjectName("learnGermanLabel");

    exp_bar_ = new QProgressBar(this);
    exp_bar_->setRange(0, 100);
    exp_bar_->setValue(30);
    exp_bar_->setTextVisible(true);
    exp_bar_->setFixedHeight(14);
    exp_bar_->setObjectName("expBar");

    translation_button_ = new QPushButton("Translation", this);
    grammar_button_ = new QPushButton("Grammar", this);

    stacked_widget_ = new QStackedWidget(this);

    QHBoxLayout *btn_layout = new QHBoxLayout;
    btn_layout->addWidget(translation_button_);
    btn_layout->addWidget(grammar_button_);
    btn_layout->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);

    QVBoxLayout *top_layout = new QVBoxLayout;
    top_layout->addWidget(level_circle_, 0, Qt::AlignHCenter);
    top_layout->addWidget(exp_bar_, 0, Qt::AlignHCenter);
    top_layout->setSpacing(10);

    QVBoxLayout *main_layout = new QVBoxLayout;
    main_layout->setContentsMargins(20, 20, 20, 20);
    main_layout->setSpacing(20);

    main_layout->addLayout(top_layout);
    main_layout->addStretch(1);
    main_layout->addWidget(learn_german_label_, 0, Qt::AlignCenter);
    main_layout->addStretch(1);
    main_layout->addLayout(btn_layout);
    main_layout->addWidget(stacked_widget_, 0);

    central_widget_->setLayout(main_layout);

    translation_widget_ = new TranslationExercise();
    connect(translation_button_, &QPushButton::clicked, this, &MainWindow::OnTranslation);
    setMinimumSize(800, 600);
}

void MainWindow::ApplyStyles() const {
    const QString bg_style = R"(
        QWidget#centralWidget {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
                stop:0 #7f00ff, stop:1 #e100ff);
        }
    )";
    //
    const QString circle_style = R"(
        QLabel#levelCircle {
            background-color: #d18cff;
            color: white;
            border-radius: 80px;
            font: bold 18px;
        }
    )";

    const QString bar_style = R"(
        QProgressBar#expBar {
            background: #eeeeee;
            border-radius: 7px;
            color: black;
        }
       QProgressBar#expBar::chunk {
            background-color: #ff66cc;
            border-radius: 7px;
        }
    )";

    const QString label_style = R"(
        QLabel#learnGermanLabel {
            color: white;
            text-transform: uppercase;
        }
    )";
    //
    translation_button_->setStyleSheet(
        "QPushButton { background-color: #cc66ff; color: white; padding: 8px 1px; border-radius: 8px; } QPushButton:hover { background-color: #dd88ff; }");
    grammar_button_->setStyleSheet(
        "QPushButton { background-color: #ff99cc; color: white; padding: 8px 1px; border-radius: 8px; } QPushButton:hover { background-color: #ffaadf; }");

    central_widget_->setObjectName("centralWidget");
    central_widget_->setStyleSheet(bg_style + circle_style + bar_style + label_style);
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    QMainWindow::resizeEvent(event);

    constexpr int base_width = 800;
    constexpr int base_height = 600;

    const qreal w_ratio = static_cast<qreal>(width()) / base_width;
    const qreal h_ratio = static_cast<qreal>(height()) / base_height;

    const int font_size = qMax(24, static_cast<int>(48 * h_ratio));
    QFont label_font = learn_german_label_->font();
    label_font.setPointSize(font_size);
    learn_german_label_->setFont(label_font);

    const int circle_size = qMin(static_cast<int>(160 * w_ratio), static_cast<int>(h_ratio * 160));
    level_circle_->setFixedSize(circle_size, circle_size);

    const int radius = circle_size / 2;
    const QString circle_style = QString(R"(
        QLabel#levelCircle {
            background-color: #d18cff;
            color: white;
            border-radius: %1px;
            font: bold %2px;
        }
    )").arg(radius).arg(qMax(12, static_cast<int>(18 * h_ratio)));

    level_circle_->setStyleSheet(circle_style);
    exp_bar_->setFixedSize(150 * w_ratio, 14 * h_ratio);
    exp_bar_->setAlignment(Qt::AlignCenter);
    QFont font = exp_bar_->font();
    font.setPointSize(12 * h_ratio);
    exp_bar_->setFont(font);

    const int btn_height = qMax(30, static_cast<int>(40 * h_ratio));
    const int btn_width = qMax(100, static_cast<int>(160 * w_ratio));
    translation_button_->setFixedSize(btn_width, btn_height);
    grammar_button_->setFixedSize(btn_width, btn_height);

    const int btn_font_size = qMax(10, static_cast<int>(14 * h_ratio));
    QFont btn_font;
    btn_font.setPointSize(btn_font_size);
    translation_button_->setFont(btn_font);
    grammar_button_->setFont(btn_font);
}

void MainWindow::OnSelectDifficulty() {
    bool ok = false;
    QStringList levels = {"Easy", "Medium", "Hard"};
    QString level = QInputDialog::getItem(this, "Select Difficulty", "Difficulty:", levels, difficult_level_, false,
                                          &ok);
    if (ok && !level.isEmpty()) {
        QMessageBox::information(this, "Difficulty Selected", "You chose: " + level);
        difficult_level_ = levels.indexOf(level);
    }
}

void MainWindow::UpdateEXP() {
    if (exp_ >= necessary_exp_) {
        level_ ++;
        exp_ -= necessary_exp_;
        necessary_exp_ += 10;
        exp_bar_->setRange(0, necessary_exp_);
    }
    level_circle_->setText("Level: " + QString::number(level_));
    exp_bar_->setFormat(QString("%1/%2 XP").arg(exp_).arg(necessary_exp_));
    exp_bar_->setValue(exp_);
}

void MainWindow::OnTranslation() {
    stacked_widget_->addWidget(translation_widget_);

}