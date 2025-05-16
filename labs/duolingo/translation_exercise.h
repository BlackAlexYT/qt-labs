#ifndef TRANSLATION_EXERCISE_H
#define TRANSLATION_EXERCISE_H

#include <QtSql/QSqlDatabase>

#include "exercise_widget.h"

class TranslationExercise : public ExerciseWidget {
    Q_OBJECT

public:
    TranslationExercise(int difficult_level, int index, QSqlDatabase db, QWidget *parent = nullptr);

    bool ValidateAnswer(const QString &answer) override;

    ~TranslationExercise() override;

private:
    void LoadQuestion() override;

    void OnParentResized(double w_ratio, double h_ratio) const;

    int difficult_level_{};
    int index_{};
    QString answer_;
    friend class MainWindow;
    QSqlDatabase db_;
    std::vector<QString> difficulties_{
        "translation_questions_easy", "translation_questions_medium", "translation_questions_hard"
    };
};
#endif
