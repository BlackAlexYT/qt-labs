CREATE TABLE IF NOT EXISTS translation_questions_easy
(
    id           INTEGER PRIMARY KEY AUTOINCREMENT,
    english_word TEXT NOT NULL,
    german_word  TEXT NOT NULL
);

CREATE TABLE IF NOT EXISTS translation_questions_medium
(
    id           INTEGER PRIMARY KEY AUTOINCREMENT,
    english_word TEXT NOT NULL,
    german_word  TEXT NOT NULL
);

CREATE TABLE IF NOT EXISTS translation_questions_hard
(
    id           INTEGER PRIMARY KEY AUTOINCREMENT,
    english_word TEXT NOT NULL,
    german_word  TEXT NOT NULL
);