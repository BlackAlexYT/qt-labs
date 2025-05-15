#include "../../labs/duolingo/translation_exercise.h"
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <string>

TranslationExercise::TranslationExercise(int difficult_level, int index, QWidget *parent) : difficult_level_(difficult_level), index_(index) {
    question_label_ = new QLabel(this);
    question_label_->setAlignment(Qt::AlignCenter);
    answer_edit_ = new QLineEdit(this);
    submit_button_ = new QPushButton("Check", this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(question_label_);
    layout->addWidget(answer_edit_);
    layout->addWidget(submit_button_);
    setLayout(layout);

    question_label_->setStyleSheet("color: white;");
    answer_edit_->setStyleSheet("background-color: white; color: purple; border: 1px solid purple; padding: 5px;");
    submit_button_->setStyleSheet("background-color: #FFC0CB; color: white; border: none; padding: 10px 20px; font-size: 16px;");

    connect(submit_button_, &QPushButton::clicked, this, &ExerciseWidget::OnSubmit);
    TranslationExercise::LoadQuestion();
}

bool TranslationExercise::ValidateAnswer(const QString &answer) {
    if (answer_ == answer_edit_->text()) {
        return true;
    }
    return false;
}

TranslationExercise::~TranslationExercise() {
}

void TranslationExercise::LoadQuestion() {
    question_label_->setText("TestQuestion");

    answer_ = "TestAnswer"; //TODO: DB
}



void TranslationExercise::OnParentResized(double w_ratio, double h_ratio)
{
    {
        const int font_size = static_cast<int>(36 * h_ratio);
        QFont label_font = question_label_->font();
        label_font.setPointSize(font_size);
        question_label_->setFont(label_font);
    }

    {
        const int font_size = static_cast<int>(16 * h_ratio);
        QFont label_font = answer_edit_->font();
        label_font.setPointSize(font_size);
        answer_edit_->setFont(label_font);
    }

    {
        const int font_size = static_cast<int>(20 * h_ratio);
        submit_button_->setStyleSheet("background-color: #FFC0CB; color: white; border: none; padding: 10px 20px; font-size: "+QString::number(font_size)+"px;");
        qDebug() << font_size;  //TODO: ubrat'
    }
}