-- Расы
INSERT INTO races (name, description) VALUES
('Human', 'Alliance of Lordaeron'),
('Orc', 'Horde'),
('Night Elf', 'Sentinels of Kalimdor'),
('Undead', 'Scourge');

-- Типы юнитов
INSERT INTO unit_types (name, description) VALUES
('Hero', 'Powerful unique unit with special abilities'),
('Unit', 'Regular combat unit'),
('Building', 'Structure that produces units or provides technology');

-- ГЕРОИ И ЮНИТЫ ЛЮДЕЙ (HUMAN)
INSERT INTO units (name, race_id, unit_type_id, hit_points, mana_points,
                   attack_min, attack_max, armor, gold_cost, lumber_cost)
VALUES
-- Герои людей
('Arthas (Paladin)', 1, 1, 925, 255, 28, 36, 4, 425, 100),
('Jaina Proudmoore (Archmage)', 1, 1, 700, 345, 23, 29, 2, 425, 100),
-- Юниты людей
('Footman', 1, 2, 420, NULL, 12, 13, 2, 135, 0),
('Knight', 1, 2, 800, NULL, 28, 34, 4, 245, 60),
('Priest', 1, 2, 435, 300, 11, 14, 0, 135, 10);

-- ГЕРОИ И ЮНИТЫ ОРКОВ (ORC)
INSERT INTO units (name, race_id, unit_type_id, hit_points, mana_points,
                   attack_min, attack_max, armor, gold_cost, lumber_cost)
VALUES
-- Герои орков
('Grom Hellscream (Blademaster)', 2, 1, 950, 270, 26, 40, 4, 425, 100),
('Thrall (Far Seer)', 2, 1, 775, 330, 23, 31, 2, 425, 100),
-- Юниты орков
('Grunt', 2, 2, 700, NULL, 19, 24, 1, 200, 0),
('Tauren', 2, 2, 1000, NULL, 35, 44, 1, 280, 80),
('Shaman', 2, 2, 550, 300, 16, 22, 1, 130, 20);

-- ГЕРОИ И ЮНИТЫ НЕЖИТИ (UNDEAD)
INSERT INTO units (name, race_id, unit_type_id, hit_points, mana_points,
                   attack_min, attack_max, armor, gold_cost, lumber_cost)
VALUES
-- Герои нежити
('Arthas (Death Knight)', 3, 1, 1050, 285, 34, 46, 5, 425, 100),
('Kel''Thuzad (Lich)', 3, 1, 700, 390, 22, 28, 2, 425, 100),
-- Юниты нежити
('Ghoul', 3, 2, 340, NULL, 14, 16, 0, 120, 0),
('Abomination', 3, 2, 975, NULL, 31, 37, 2, 240, 70),
('Necromancer', 3, 2, 435, 300, 15, 18, 0, 145, 20);

-- ГЕРОИ И ЮНИТЫ НОЧНЫХ ЭЛЬФОВ (NIGHT ELF)
INSERT INTO units (name, race_id, unit_type_id, hit_points, mana_points,
                   attack_min, attack_max, armor, gold_cost, lumber_cost)
VALUES
-- Герои ночных эльфов
('Illidan Stormrage (Demon Hunter)', 4, 1, 1025, 285, 32, 44, 4, 425, 100),
('Tyrande Whisperwind (Priestess of the Moon)', 4, 1, 800, 330, 27, 38, 3, 425, 100),
-- Юниты ночных эльфов
('Archer', 4, 2, 435, NULL, 18, 18, 0, 130, 10),
('Huntress', 4, 2, 700, NULL, 28, 34, 3, 195, 20),
('Druid of the Claw', 4, 2, 575, 300, 17, 23, 2, 255, 80);

-- СПОСОБНОСТИ ГЕРОЕВ
INSERT INTO abilities (name, description, mana_cost, cooldown_sec) VALUES
-- Paladin
('Holy Light', 'Heals a target or damages undead', 65, 5),
('Divine Shield', 'Makes the Paladin invulnerable', 25, 45),
('Devotion Aura', 'Increases armor of nearby allies', 0, 0),
('Resurrection', 'Brings dead units back to life', 200, 240),

-- Archmage
('Blizzard', 'Calls down waves of freezing ice', 75, 6),
('Summon Water Elemental', 'Summons a Water Elemental', 125, 30),
('Brilliance Aura', 'Increases mana regeneration', 0, 0),
('Mass Teleport', 'Teleports units to target location', 50, 20),

-- Blademaster
('Wind Walk', 'Turns invisible and moves faster', 75, 4),
('Mirror Image', 'Creates illusions of the Blademaster', 125, 16),
('Critical Strike', 'Chance to deal critical damage', 0, 0),
('Bladestorm', 'Spin and damage all nearby enemies', 0, 0),

-- Far Seer
('Chain Lightning', 'Hurls lightning that bounces', 110, 9),
('Far Sight', 'Reveals distant areas', 75, 6),
('Feral Spirit', 'Summons two Spirit Wolves', 75, 30),
('Earthquake', 'Shakes the earth damaging buildings', 150, 90),

-- Death Knight
('Death Coil', 'Damages enemies or heals undead', 75, 6),
('Death Pact', 'Kills friendly unit to heal', 0, 5),
('Unholy Aura', 'Increases movement speed', 0, 0),
('Animate Dead', 'Raises corpses as warriors', 250, 180),

-- Lich
('Frost Nova', 'Blasts enemies with ice', 125, 11),
('Frost Armor', 'Encases ally in frost armor', 50, 1),
('Dark Ritual', 'Sacrifices unit for mana', 0, 3),
('Death and Decay', 'Damages buildings and units', 250, 150),

-- Demon Hunter
('Mana Burn', 'Burns enemy mana', 50, 7),
('Immolation', 'Engulfs hero in flames', 60, 2),
('Evasion', 'Chance to dodge attacks', 0, 0),
('Metamorphosis', 'Transforms into demon form', 150, 180),

-- Priestess of the Moon
('Scout', 'Summons an Owl Scout', 50, 1),
('Searing Arrows', 'Adds fire damage to attacks', 8, 0),
('Trueshot Aura', 'Increases ranged damage', 0, 0),
('Starfall', 'Rains stars on enemies', 200, 180);

-- СВЯЗЬ ГЕРОЕВ И СПОСОБНОСТЕЙ
INSERT INTO unit_abilities (unit_id, ability_id) VALUES
-- Arthas (Paladin) - unit_id = 1
(1, 1), (1, 2), (1, 3), (1, 4),
-- Jaina (Archmage) - unit_id = 2
(2, 5), (2, 6), (2, 7), (2, 8),
-- Grom (Blademaster) - unit_id = 6
(6, 9), (6, 10), (6, 11), (6, 12),
-- Thrall (Far Seer) - unit_id = 7
(7, 13), (7, 14), (7, 15), (7, 16),
-- Arthas (Death Knight) - unit_id = 11
(11, 17), (11, 18), (11, 19), (11, 20),
-- Kel'Thuzad (Lich) - unit_id = 12
(12, 21), (12, 22), (12, 23), (12, 24),
-- Illidan (Demon Hunter) - unit_id = 16
(16, 25), (16, 26), (16, 27), (16, 28),
-- Tyrande (Priestess) - unit_id = 17
(17, 29), (17, 30), (17, 31), (17, 32);
