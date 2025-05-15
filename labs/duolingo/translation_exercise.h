#ifndef TRANSLATION_EXERCISE_H
#define TRANSLATION_EXERCISE_H

#include "exercise_widget.h"

class TranslationExercise : public ExerciseWidget {
    Q_OBJECT

public:
    TranslationExercise(int difficult_level, int index, QWidget *parent = nullptr);

    bool ValidateAnswer(const QString &answer) override;

    ~TranslationExercise() override;

private:
    void LoadQuestion() override;

    void OnParentResized(double w_ratio, double h_ratio);

    int difficult_level_{};
    int index_{};
    QString answer_;
    friend class MainWindow;
};
#endif
