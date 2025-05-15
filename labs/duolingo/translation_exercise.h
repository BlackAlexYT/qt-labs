#ifndef TRANSLATION_EXERCISE_H
#define TRANSLATION_EXERCISE_H

#include "exercise_widget.h"

class TranslationExercise : public ExerciseWidget {
    Q_OBJECT

public:
    TranslationExercise(QWidget *parent = nullptr);
    bool ValidateAnswer(const QString& answer) override;
    ~TranslationExercise() override;
private:
    void OnActivated() override;
};
#endif
