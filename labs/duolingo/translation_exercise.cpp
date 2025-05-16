#include "../../labs/duolingo/translation_exercise.h"

#include <qdialogbuttonbox.h>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <QVBoxLayout>
#include <string>
#include <QtSql/QSqlQuery>
#include <QSoundEffect>

TranslationExercise::TranslationExercise(int difficult_level, int index, QSqlDatabase db,
                                         QWidget *parent) : difficult_level_(difficult_level), index_(index), db_(db) {
    question_label_ = new QLabel(this);
    question_label_->setAlignment(Qt::AlignCenter);
    answer_edit_ = new QLineEdit(this); // TODO: add by pressing enter check the answer
    submit_button_ = new QPushButton("Check", this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(question_label_);
    layout->addWidget(answer_edit_);
    layout->addWidget(submit_button_);
    setLayout(layout);

    question_label_->setStyleSheet("color: white;");
    answer_edit_->setStyleSheet("background-color: white; color: purple; border: 1px solid purple; padding: 5px;");
    submit_button_->setStyleSheet(
        "background-color: #FFC0CB; color: white; border: none; padding: 10px 20px; font-size: 16px;");

    connect(submit_button_, &QPushButton::clicked, this, &ExerciseWidget::OnSubmit);
    TranslationExercise::LoadQuestion();
}

bool TranslationExercise::ValidateAnswer(const QString &answer) {
    if (answer_.toLower() == answer_edit_->text().toLower()) {
        QSoundEffect effect;
        effect.setSource(QUrl::fromLocalFile("labs/duolingo/data/correct.wav"));
        effect.play();
        QMessageBox::information(this, "Correct!", "Your answer is correct!");
    } else {
        QSoundEffect effect;
        effect.setSource(QUrl::fromLocalFile("labs/duolingo/data/wrong.wav"));
        effect.play();
        QMessageBox::critical(this, "Wrong!", "Your answer is wrong! The right answer is " + answer_);
    }
    return answer_.toLower() == answer_edit_->text().toLower();
    // TODO: half points for wrong article.
}

TranslationExercise::~TranslationExercise() {
}

void TranslationExercise::LoadQuestion() {
    QSqlQuery query;
    if (query.exec(
        "SELECT english_word, german_word from " + difficulties_[difficult_level_] + " where id == " +
        QString::number(index_) + ";")) {
        while (query.next()) {
            const QString english_word = query.value(0).toString();
            const QString german_word = query.value(1).toString();
            question_label_->setText(english_word);
            answer_ = german_word;
        }
    }
}

void TranslationExercise::OnParentResized(double w_ratio, double h_ratio) { {
        const int font_size = static_cast<int>(36 * h_ratio);
        QFont label_font = question_label_->font();
        label_font.setPointSize(font_size);
        question_label_->setFont(label_font);
    } {
        const int font_size = static_cast<int>(16 * h_ratio);
        QFont label_font = answer_edit_->font();
        label_font.setPointSize(font_size);
        answer_edit_->setFont(label_font);
    } {
        const int font_size = static_cast<int>(20 * h_ratio);
        submit_button_->setStyleSheet(
            "background-color: #FFC0CB; color: white; border: none; padding: 10px 20px; font-size: " +
            QString::number(font_size) + "px;");
    }
}
