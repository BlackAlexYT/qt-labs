//
// Created by blalex on 3/14/25.
//

#ifndef CALCULATOR_CONTROLLER_H
#define CALCULATOR_CONTROLLER_H
#include <QComboBox>
#include <QLineEdit>
#include <qdialog.h>

class CalculatorController : public QObject {
    Q_OBJECT
   public:
    explicit CalculatorController(QObject* parent = nullptr);

   private:
    void UpdateValues(QLineEdit* edited);
    void UpdateUnit(QLineEdit* edited, QString unit);

    float ToBase(const QString& unit, double number);

    float FromBase(const QString& unit, double number);

    struct Field {
        QLineEdit* value_;
        QComboBox* unit_;
        QString prev_value_;
    };

    std::vector<Field> fields_{};
    bool is_work_ = false;
    friend class MainWindow;
};

#endif  // CALCULATOR_CONTROLLER_H
