//
// Created by blalex on 3/14/25.
//

#include "main_window.h"

#include "calculator_controller.h"

#include <QComboBox>
#include <QLineEdit>
#include <QMainWindow>
#include <QVBoxLayout>
#include <qlayoutitem.h>
#include <qobject.h>
#include <qpushbutton.h>
#include <qwidget.h>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , main_layout_(new QVBoxLayout())
    , controller_(new CalculatorController(this))
    , button_(new QPushButton("Add new unit", this))
    , main_layout1_(new QVBoxLayout()) {
    main_layout_->addWidget(button_);

    auto* central_widget = new QWidget(this);
    central_widget->setLayout(main_layout1_);
    setCentralWidget(central_widget);
    setWindowTitle("Distance unit converter");

    AddField();
    QSpacerItem* spacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    main_layout1_->addLayout(main_layout_);
    main_layout1_->addSpacerItem(spacer);
    connect(button_, &QPushButton::clicked, this, &MainWindow::AddField);
}

void MainWindow::AddField() {
    QString base_value;
    if (std::size(controller_->fields_) == 0) {
        base_value = "0";
    } else {
        std::unordered_map<QString, double> to_base{
          {"m", 1}, {"cm", 0.01}, {"km", 1000}, {"dm", 0.1}, {"mm", 0.001}};
        base_value = QString::number(
            controller_->fields_.front().value_->text().toDouble() *
            to_base[controller_->fields_.front().unit_->currentText()]);
    }
    QHBoxLayout* fieldLayout = new QHBoxLayout;
    QLineEdit* value = new QLineEdit(base_value);
    QComboBox* unit = new QComboBox;
    unit->addItems(
        {// Metrical
         "m", "cm", "km", "dm", "mm",

         // British/American
         "mi", "yd", "ft", "in",

         // Chinese
         "li", "zhang", "chi", "cun",

         // Astronomical
         "au", "ly", "pc",

         // Sea
         "nmi"});
    fieldLayout->addWidget(value);
    fieldLayout->addWidget(unit);
    main_layout_->addLayout(fieldLayout);

    controller_->fields_.push_back({value, unit, "m"});
    connect(
        value, &QLineEdit::textEdited, this, [this, value] { controller_->UpdateValues(value); });
    connect(unit, &QComboBox::currentIndexChanged, this, [this, value, unit] {
        controller_->UpdateUnit(value, unit->currentText());
    });
}
