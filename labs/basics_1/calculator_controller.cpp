//
// Created by blalex on 3/14/25.
//

#include "calculator_controller.h"

CalculatorController::CalculatorController(QObject* parent) : QObject(parent) {
}

void CalculatorController::UpdateValues(QLineEdit* edited) {
    if (std::size(edited->text()) == 0 ||
        edited->text()[std::size(edited->text()) - 1] == QString(".") || is_work_) {
        return;
    }
    is_work_ = true;
    Field changed_field{};
    for (const auto& field : fields_) {
        if (field.value_ == edited) {
            changed_field = field;
        }
    }

    const double base =
        ToBase(changed_field.unit_->currentText(), changed_field.value_->text().toDouble());
    for (const auto& field : fields_) {
        field.value_->setText(QString::number(FromBase(field.unit_->currentText(), base)));
    }
    is_work_ = false;
}

void CalculatorController::UpdateUnit(QLineEdit* edited, QString unit) {
    Field* changed_field = nullptr;

    for (auto& field : fields_) {
        if (field.value_ == edited) {
            changed_field = &field;
        }
    }
    const double base = ToBase(changed_field->prev_value_, edited->text().toDouble());
    changed_field->prev_value_ = unit;

    edited->setText(QString::number(FromBase(unit, base)));
}

float CalculatorController::ToBase(const QString& unit, const double number) {
    std::unordered_map<QString, double> to_base{
      {"m", 1},
      {"cm", 0.01},
      {"km", 1000},
      {"dm", 0.1},
      {"mm", 0.001},

      {"mi", 1609.34},
      {"yd", 0.9144},
      {"ft", 0.3048},
      {"in", 0.0254},

      {"li", 500},
      {"zhang", 3.33333},
      {"chi", 0.333333},
      {"cun", 0.0333333},

      {"au", 149'597'870'700},
      {"ly", 9.4607304725808e15},
      {"pc", 3.0856775814913672789e16},

      {"nmi", 1852}};
    return to_base[unit] * number;
}

float CalculatorController::FromBase(const QString& unit, const double number) {
    std::unordered_map<QString, double> from_base{
      {"m", 1},
      {"cm", 100},
      {"km", 0.001},
      {"dm", 10},
      {"mm", 1000},

      {"mi", 0.000621371},
      {"yd", 1.09361},
      {"ft", 3.28084},
      {"in", 39.3701},

      {"li", 0.002},
      {"zhang", 0.3},
      {"chi", 3},
      {"cun", 30},

      {"au", 6.684587122e-12},
      {"ly", 1.057000834e-16},
      {"pc", 3.240779289e-17},

      {"nmi", 0.000539957}};
    return from_base[unit] * number;
}
