#ifndef MAIN_WINDOW_H_
#define MAIN_WINDOW_H_

#include <QLabel>
#include <QMainWindow>
#include <QProgressBar>
#include <QPushButton>
#include <QStackedWidget>


class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow();

    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    void SetupMenu();

    void SetupUI();

    void ApplyStyles() const;

    void OnSelectDifficulty();


    QWidget *central_widget_;
    QLabel *level_circle_;
    QLabel *learn_german_label_;
    QProgressBar *exp_bar_;
    QLabel *exp_text_;
    QPushButton *translation_btn_;
    QPushButton *grammar_btn_;
    QStackedWidget *stacked_widget_;
    // TranslationExercise *translation_widget_;
    // GrammarExercise *grammar_widget_;
    QTimer *exercise_timer_;
    int difficult_level_ = 0;
};


#endif
