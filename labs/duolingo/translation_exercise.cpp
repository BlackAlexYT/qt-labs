#include "../../labs/duolingo/translation_exercise.h"
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>

TranslationExercise::TranslationExercise(QWidget *parent) {
    question_label_ = new QLabel(this);
    answer_edit_ = new QLineEdit(this);
    submit_button_ = new QPushButton("Check", this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(question_label_);
    layout->addWidget(answer_edit_);
    layout->addWidget(submit_button_);
    setLayout(layout);

    connect(submit_button_, &QPushButton::clicked, this, &ExerciseWidget::OnSubmit);
    // TODO: Заполнить questions_
    LoadQuestion();
}

bool TranslationExercise::ValidateAnswer(const QString &answer) {
    return true; // TODO: norm realization pls
}

void TranslationExercise::OnActivated() {

}


TranslationExercise::~TranslationExercise() {
}

