//
// Created by blalex on 3/12/25.
//

#include "main_window.h"

#include <QFormLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
#include <qcombobox.h>
#include <qgroupbox.h>
#include <qlabel.h>
#include <qlistwidget.h>
#include <qprogressbar.h>
#include <qspinbox.h>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , count_(new QSpinBox(this))
    , view_(new QListWidget(this))
    , total_progress_(new QProgressBar(this))
    , green_progress_(new QProgressBar(this))
    , question_view_(new QGroupBox("Information about ticket", this))
    , number_label_(new QLabel("Ticket number", this))
    , name_label_(new QLabel("Name", this))
    , name_edit_(new QLineEdit("Enter new name", this))
    , status_(new QComboBox(this))
    , next_button_(new QPushButton("Next question", this))
    , previous_button_(new QPushButton("Previous question", this)) {
    CreateWidgets();
    SetupLayout();
    setWindowTitle("Procrastination");
    resize(500, 700);
}

void MainWindow::CreateWidgets() const {
    status_->addItems({"Default", "Yellow", "Green"});
}

void MainWindow::SetupLayout() {
    auto* main_layout = new QVBoxLayout;

    main_layout->addWidget(total_progress_);
    main_layout->addWidget(green_progress_);

    main_layout->addWidget(count_);
    main_layout->addWidget(view_);

    auto* question_layout = new QGridLayout(question_view_);
    question_layout->addWidget(number_label_, 0, 0);
    question_layout->addWidget(name_label_, 0, 1);
    question_layout->addWidget(name_edit_, 1, 0);
    question_layout->addWidget(status_, 1, 1);

    auto* button_layout = new QHBoxLayout;
    button_layout->addWidget(next_button_);
    button_layout->addWidget(previous_button_);

    main_layout->addWidget(question_view_);
    main_layout->addLayout(button_layout);

    auto* central_widget = new QWidget(this);
    central_widget->setLayout(main_layout);
    setCentralWidget(central_widget);
}