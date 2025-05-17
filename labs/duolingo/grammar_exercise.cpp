#include "grammar_exercise.h"

#include <QButtonGroup>
#include <QVBoxLayout>

GrammarExercise::GrammarExercise(const int difficult_level, const QSqlDatabase &db, QWidget *parent) : difficult_level_(
        difficult_level), db_(db) {
    question_label_ = new QLabel(this);
    question_label_->setAlignment(Qt::AlignCenter);
    option_1_ = new QRadioButton(this);
    option_2_ = new QRadioButton(this);
    option_3_ = new QRadioButton(this);
    option_4_ = new QRadioButton(this);
    QButtonGroup *options_group = new QButtonGroup(this);
    options_group->addButton(option_1_);
    options_group->addButton(option_2_);
    options_group->addButton(option_3_);
    options_group->addButton(option_4_);
    options_group->setExclusive(true);
    submit_button_ = new QPushButton("Check", this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(question_label_);

    QHBoxLayout *options_layout = new QHBoxLayout; {
        QVBoxLayout *left_col = new QVBoxLayout;
        left_col->addWidget(option_1_);
        left_col->addWidget(option_2_);

        QVBoxLayout *right_col = new QVBoxLayout;
        right_col->addWidget(option_3_);
        right_col->addWidget(option_4_);

        options_layout->addLayout(left_col);
        options_layout->addLayout(right_col);
    }
    layout->addLayout(options_layout);

    layout->addWidget(submit_button_);
    setLayout(layout);

    question_label_->setStyleSheet("color: white;");

    const QString rb_style = R"(
    QRadioButton {
        spacing: 5px;
        padding: 4px;
        color: white;
    }
    QRadioButton::indicator {
        width: 16px;
        height: 16px;
        border-radius: 8px;
        border: 1px solid white;
        background: transparent;
    }
    QRadioButton::indicator:hover {
        border-color: #ddddff;
    }
    QRadioButton::indicator:checked {
        background-color: pink;
        border: 1px solid pink;
    }
)";
    option_1_->setStyleSheet(rb_style);
    option_2_->setStyleSheet(rb_style);
    option_3_->setStyleSheet(rb_style);
    option_4_->setStyleSheet(rb_style);

    submit_button_->setStyleSheet(R"(
        QPushButton {
            background-color: #FFC0CB;
            color: white;
            border: none;
            border-radius: 12px;
            padding: 10px 20px;
            font-size: 16px;
        }
        QPushButton:hover {
            background-color: #FFB6C1;
        }
        QPushButton:pressed {
            background-color: #FF69B4;
        }
    )");

    question_label_->setText("Test");
    option_1_->setText("Test1");
    option_2_->setText("Test2");
    option_3_->setText("Test3");
    option_4_->setText("Test4");
}

void GrammarExercise::OnParentResized(double /*w_ratio*/, const double h_ratio) const { {
        const int font_size = static_cast<int>(48 * h_ratio);
        QFont label_font = question_label_->font();
        label_font.setPointSize(font_size);
        question_label_->setFont(label_font);
    } {
        const int dia = qBound(8, static_cast<int>(16 * h_ratio), 32);
        const int radius = dia / 2;
        const int text_fs = static_cast<int>(16 * h_ratio);
        const QString rb_style = QString(R"(
            QRadioButton {
                spacing: 5px;
                padding: 4px;
                font-size: %3px;
                color: white;
            }
            QRadioButton::indicator {
                width: %1px;
                height: %1px;
                border-radius: %2px;       /* половина размера — идеально круг */
                border: 2px solid white;
                background: transparent;
            }
            QRadioButton::indicator:hover {
                border-color: pink;
            }
            QRadioButton::indicator:checked {
                background-color: pink;
                border: 2px solid pink;
            }
        )").arg(dia).arg(radius).arg(text_fs);
        option_1_->setStyleSheet(rb_style);
        option_2_->setStyleSheet(rb_style);
        option_3_->setStyleSheet(rb_style);
        option_4_->setStyleSheet(rb_style);
    } {
        const int font_size = static_cast<int>(20 * h_ratio);
        const QString sheet = QString(R"(
            QPushButton {
                background-color: #FFC0CB;
                color: white;
                border: none;
                border-radius: 12px;
                padding: 10px 20px;
                font-size: %1px;
            }
            QPushButton:hover {
                background-color: #FFB6C1;
            }
            QPushButton:pressed {
                background-color: #FF69B4;
            }
        )").arg(font_size);
        submit_button_->setStyleSheet(sheet);
    }
}


GrammarExercise::~GrammarExercise() {
}

bool GrammarExercise::ValidateAnswer() {
    return true;
}

void GrammarExercise::LoadQuestion() {
}
