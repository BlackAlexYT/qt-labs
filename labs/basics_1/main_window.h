//
// Created by blalex on 3/14/25.
//

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H
#include "calculator_controller.h"

#include <QMainWindow>
#include <QPushButton>

QT_BEGIN_NAMESPACE
class QVBoxLayout;
class QMainWindow;
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
   public:
    MainWindow(QWidget* parent = nullptr);

    void AddField();

   private:
    QVBoxLayout* main_layout_;
    CalculatorController* controller_;
    QPushButton* button_;
    QVBoxLayout* main_layout1_;
};

#endif  // MAIN_WINDOW_H
