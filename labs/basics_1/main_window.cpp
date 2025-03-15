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
#include <unordered_set>

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
    AddField();
    AddField();

    QSpacerItem* spacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    main_layout1_->addLayout(main_layout_);
    main_layout1_->addSpacerItem(spacer);
    connect(button_, &QPushButton::clicked, this, &MainWindow::AddField);
}

void MainWindow::AddField() {
    double base_value;
    if (std::size(controller_->fields_) == 0) {
        base_value = 0;
    } else {
        base_value = controller_->fields_.front().value_->text().toDouble() *
                     to_base_[controller_->fields_.front().unit_->currentText()];
    }

    std::unordered_set<QString> fields;
    for (auto& field : controller_->fields_) {
        fields.insert(field.unit_->currentText());
    }

    QString necessary_unit = "m";
    for (const auto& unit_ : units_) {
        if (fields.find(unit_) == fields.end()) {
            necessary_unit = unit_;
            break;
        }
    }

    base_value = base_value * from_base_[necessary_unit];

    QHBoxLayout* fieldLayout = new QHBoxLayout;
    // QString base_value_string = std::to_string(base_value);
    QLineEdit* value = new QLineEdit(QString::number(base_value));  // 'f', 15
    // value->setMaxLength(100);
    QComboBox* unit = new QComboBox;
    for (const auto& unit_ : units_) {
        unit->addItem(unit_);
    }

    unit->setCurrentText(necessary_unit);

    fieldLayout->addWidget(value);
    fieldLayout->addWidget(unit);
    main_layout_->addLayout(fieldLayout);

    controller_->fields_.push_back({value, unit, necessary_unit});
    connect(
        value, &QLineEdit::textEdited, this, [this, value] { controller_->UpdateValues(value); });
    connect(unit, &QComboBox::currentIndexChanged, this, [this, value, unit] {
        controller_->UpdateUnit(value, unit->currentText());
    });
}
