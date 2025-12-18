CREATE DATABASE warcraft3_db;

-- Подключение к БД
\c warcraft3_db;

-- Таблица рас
CREATE TABLE races (
    race_id      SERIAL PRIMARY KEY,
    name         TEXT NOT NULL UNIQUE,
    description  TEXT
);

-- Типы юнитов
CREATE TABLE unit_types (
    unit_type_id SERIAL PRIMARY KEY,
    name         TEXT NOT NULL UNIQUE,
    description  TEXT
);

-- Юниты
CREATE TABLE units (
    unit_id      SERIAL PRIMARY KEY,
    name         TEXT NOT NULL,
    race_id      INT NOT NULL REFERENCES races(race_id) ON DELETE RESTRICT,
    unit_type_id INT NOT NULL REFERENCES unit_types(unit_type_id) ON DELETE RESTRICT,
    hit_points   INT NOT NULL,
    mana_points  INT,
    attack_min   INT,
    attack_max   INT,
    armor        INT,
    gold_cost    INT,
    lumber_cost  INT
);

-- Способности
CREATE TABLE abilities (
    ability_id   SERIAL PRIMARY KEY,
    name         TEXT NOT NULL UNIQUE,
    description  TEXT,
    mana_cost    INT,
    cooldown_sec INT
);

-- Связь юнит-способность (многие-ко-многим)
CREATE TABLE unit_abilities (
    unit_id    INT NOT NULL REFERENCES units(unit_id) ON DELETE CASCADE,
    ability_id INT NOT NULL REFERENCES abilities(ability_id) ON DELETE CASCADE,
    PRIMARY KEY (unit_id, ability_id)
);
