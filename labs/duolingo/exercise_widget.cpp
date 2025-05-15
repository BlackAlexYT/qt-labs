#include "../../labs/duolingo/exercise_widget.h"
#include <qtmetamacros.h>

ExerciseWidget::ExerciseWidget(QWidget *parent) : QWidget(parent) {
}

void ExerciseWidget::OnSubmit() {
    const bool ok = ValidateAnswer(answer_edit_->text());
    emit ExerciseAnswered(ok);
    // LoadQuestion();
}
