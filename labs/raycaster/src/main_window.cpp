//
// Created by blalex on 4/6/25.
//

#include "main_window.h"

#include <QBoxLayout>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), drawing_widget_(new DrawingWidget(&controller_, this)) {
    SetupWindow();
}

void MainWindow::SetupWindow() {
    setWindowTitle("Raycaster");
    resize(800, 600);
    auto* central_widget = new QWidget(this);
    auto* main_layout = new QVBoxLayout(central_widget);
    auto* top_layout = new QHBoxLayout(central_widget);

    mode_selector_ = new QComboBox(this);
    mode_selector_->addItems({"Light", "Polygon"});
    mode_selector_->setCurrentIndex(0);

    main_layout->addLayout(top_layout);
    main_layout->addWidget(drawing_widget_);
    setCentralWidget(central_widget);
    connect(mode_selector_, &QComboBox::currentIndexChanged, this, &MainWindow::ChangeMode);
}

void MainWindow::ChangeMode(const int mode) {
    controller_.SetMode(mode);
}