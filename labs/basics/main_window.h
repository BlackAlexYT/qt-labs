//
// Created by blalex on 3/12/25.
//

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
class QSpinBox;
class QListWidget;
class QGroupBox;
class QLabel;
class QLineEdit;
class QComboBox;
class QPushButton;
class QProgressBar;
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    MainWindow(QWidget* parent = nullptr);

   private:
    void CreateWidgets() const;
    void SetupLayout();

    QSpinBox* count_;
    QListWidget* view_;
    QProgressBar* total_progress_;
    QProgressBar* green_progress_;
    QGroupBox* question_view_;
    QLabel* number_label_;
    QLabel* name_label_;
    QLineEdit* name_edit_;
    QComboBox* status_;
    QPushButton* next_button_;
    QPushButton* previous_button_;
};

#endif  // MAIN_WINDOW_H
