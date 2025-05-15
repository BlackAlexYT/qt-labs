#ifndef EXERCISE_WIDGET_H
#define EXERCISE_WIDGET_H
#include <QLabel>
#include <QLineEdit>
#include <QWidget>
#include <QPushButton>

class ExerciseWidget : public QWidget {
    Q_OBJECT

public:
    explicit ExerciseWidget(QWidget *parent = nullptr);

    virtual bool ValidateAnswer(const QString &answer) = 0;

    virtual ~ExerciseWidget() = default;

protected slots:
    void OnSubmit();

signals:
    void ExerciseAnswered(bool correct);

private:
    friend class TranslationExercise;

    virtual void LoadQuestion() = 0;

    QLabel *question_label_;
    QLineEdit *answer_edit_;
    QPushButton *submit_button_;
};

#endif
