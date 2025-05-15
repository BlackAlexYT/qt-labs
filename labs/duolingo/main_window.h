#ifndef MAIN_WINDOW_H_
#define MAIN_WINDOW_H_

#include <QLabel>
#include <QMainWindow>
#include <QProgressBar>
#include <QPushButton>
#include <QStackedWidget>
#include "translation_exercise.h"


class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow();

    ~MainWindow();

private slots:
    void OnTranslation();

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    void SetupMenu();

    void SetupUI();

    void ApplyStyles() const;

    void OnSelectDifficulty();

    void UpdateEXP();


    QWidget *central_widget_;
    QLabel *level_circle_;
    QLabel *learn_german_label_;
    QProgressBar *exp_bar_;
    QLabel *exp_text_;
    QPushButton *translation_button_;
    QPushButton *grammar_button_;
    QStackedWidget *stacked_widget_;
    TranslationExercise *translation_widget_;
    // GrammarExercise *grammar_widget_;
    QTimer *exercise_timer_;
    int difficult_level_ = 0;
    int level_ = 1;
    int exp_ = 0;
    int necessary_exp_ = 10;
    std::vector<int> translation_index_{0, 0, 0};
    std::vector<int> grammar_index_{0, 0, 0};
};


#endif
