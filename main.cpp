#include <iostream>
#include <pqxx/pqxx>
#include <iomanip>

void printSeparator() {
    std::cout << std::string(70, '=') << "\n";
}

void queryHumanUnits(pqxx::connection &c) {
    printSeparator();
    std::cout << "Запрос 1: Все юниты расы Human\n";
    printSeparator();
    
    try {
        pqxx::work tx{c};
        pqxx::result r = tx.exec(
            "SELECT u.name, u.hit_points, u.mana_points "
            "FROM units u "
            "JOIN races r ON u.race_id = r.race_id "
            "WHERE r.name = 'Human';"
        );
        
        std::cout << std::setw(30) << std::left << "Name" 
                  << std::setw(15) << "Hit Points" 
                  << std::setw(15) << "Mana Points" << "\n";
        std::cout << std::string(60, '-') << "\n";
        
        for (auto const &row : r) {
            std::cout << std::setw(30) << std::left << row["name"].c_str()
                      << std::setw(15) << row["hit_points"].c_str()
                      << std::setw(15) << (row["mana_points"].is_null() ? "NULL" : row["mana_points"].c_str())
                      << "\n";
        }
        
        tx.commit();
        std::cout << "\n";
    } catch (const std::exception &e) {
        std::cerr << "Ошибка: " << e.what() << "\n";
    }
}

void queryAllHeroes(pqxx::connection &c) {
    printSeparator();
    std::cout << "Запрос 2: Все герои всех рас\n";
    printSeparator();
    
    try {
        pqxx::work tx{c};
        pqxx::result r = tx.exec(
            "SELECT u.name, r.name AS race "
            "FROM units u "
            "JOIN races r ON u.race_id = r.race_id "
            "JOIN unit_types t ON u.unit_type_id = t.unit_type_id "
            "WHERE t.name = 'Hero';"
        );
        
        std::cout << std::setw(40) << std::left << "Hero Name" 
                  << std::setw(20) << "Race" << "\n";
        std::cout << std::string(60, '-') << "\n";
        
        for (auto const &row : r) {
            std::cout << std::setw(40) << std::left << row["name"].c_str()
                      << std::setw(20) << row["race"].c_str() << "\n";
        }
        
        tx.commit();
        std::cout << "\n";
    } catch (const std::exception &e) {
        std::cerr << "Ошибка: " << e.what() << "\n";
    }
}

void queryUnitAbilities(pqxx::connection &c) {
    printSeparator();
    std::cout << "Запрос 3: Юниты и их способности\n";
    printSeparator();
    
    try {
        pqxx::work tx{c};
        pqxx::result r = tx.exec(
            "SELECT u.name AS unit, a.name AS ability "
            "FROM units u "
            "JOIN unit_abilities ua ON u.unit_id = ua.unit_id "
            "JOIN abilities a ON ua.ability_id = a.ability_id "
            "ORDER BY u.name, a.name;"
        );
        
        std::cout << std::setw(40) << std::left << "Unit" 
                  << std::setw(30) << "Ability" << "\n";
        std::cout << std::string(70, '-') << "\n";
        
        for (auto const &row : r) {
            std::cout << std::setw(40) << std::left << row["unit"].c_str()
                      << std::setw(30) << row["ability"].c_str() << "\n";
        }
        
        tx.commit();
        std::cout << "\n";
    } catch (const std::exception &e) {
        std::cerr << "Ошибка: " << e.what() << "\n";
    }
}

void queryAverageArmorByRace(pqxx::connection &c) {
    printSeparator();
    std::cout << "Запрос 4: Средняя броня по расам (агрегатная функция)\n";
    printSeparator();
    
    try {
        pqxx::work tx{c};
        pqxx::result r = tx.exec(
            "SELECT r.name AS race, AVG(u.armor) AS avg_armor "
            "FROM units u "
            "JOIN races r ON u.race_id = r.race_id "
            "GROUP BY r.name;"
        );
        
        std::cout << std::setw(25) << std::left << "Race" 
                  << std::setw(20) << "Average Armor" << "\n";
        std::cout << std::string(45, '-') << "\n";
        
        for (auto const &row : r) {
            std::cout << std::setw(25) << std::left << row["race"].c_str()
                      << std::setw(20) << row["avg_armor"].c_str() << "\n";
        }
        
        tx.commit();
        std::cout << "\n";
    } catch (const std::exception &e) {
        std::cerr << "Ошибка: " << e.what() << "\n";
    }
}

void queryExpensiveUnits(pqxx::connection &c) {
    printSeparator();
    std::cout << "Запрос 5: Юниты дороже 200 золота (WHERE)\n";
    printSeparator();
    
    try {
        pqxx::work tx{c};
        pqxx::result r = tx.exec(
            "SELECT name, gold_cost "
            "FROM units "
            "WHERE gold_cost > 200;"
        );
        
        std::cout << std::setw(40) << std::left << "Unit Name" 
                  << std::setw(15) << "Gold Cost" << "\n";
        std::cout << std::string(55, '-') << "\n";
        
        for (auto const &row : r) {
            std::cout << std::setw(40) << std::left << row["name"].c_str()
                      << std::setw(15) << row["gold_cost"].c_str() << "\n";
        }
        
        tx.commit();
        std::cout << "\n";
    } catch (const std::exception &e) {
        std::cerr << "Ошибка: " << e.what() << "\n";
    }
}

void queryUnitCountByRace(pqxx::connection &c) {
    printSeparator();
    std::cout << "Запрос 6: Количество юнитов в каждой расе (LEFT JOIN)\n";
    printSeparator();
    
    try {
        pqxx::work tx{c};
        pqxx::result r = tx.exec(
            "SELECT r.name AS race, COUNT(u.unit_id) AS unit_count "
            "FROM races r "
            "LEFT JOIN units u ON r.race_id = u.race_id "
            "GROUP BY r.name;"
        );
        
        std::cout << std::setw(25) << std::left << "Race" 
                  << std::setw(15) << "Unit Count" << "\n";
        std::cout << std::string(40, '-') << "\n";
        
        for (auto const &row : r) {
            std::cout << std::setw(25) << std::left << row["race"].c_str()
                      << std::setw(15) << row["unit_count"].c_str() << "\n";
        }
        
        tx.commit();
        std::cout << "\n";
    } catch (const std::exception &e) {
        std::cerr << "Ошибка: " << e.what() << "\n";
    }
}

void queryUnitsWithoutMana(pqxx::connection &c) {
    printSeparator();
    std::cout << "Запрос 7: Юниты без маны (IS NULL)\n";
    printSeparator();
    
    try {
        pqxx::work tx{c};
        pqxx::result r = tx.exec(
            "SELECT name FROM units WHERE mana_points IS NULL;"
        );
        
        std::cout << std::setw(40) << std::left << "Unit Name" << "\n";
        std::cout << std::string(40, '-') << "\n";
        
        for (auto const &row : r) {
            std::cout << std::setw(40) << std::left << row["name"].c_str() << "\n";
        }
        
        tx.commit();
        std::cout << "\n";
    } catch (const std::exception &e) {
        std::cerr << "Ошибка: " << e.what() << "\n";
    }
}

void updateFootmanCost(pqxx::connection &c) {
    printSeparator();
    std::cout << "Запрос 8: UPDATE - увеличение стоимости Footman на 10 золота\n";
    printSeparator();
    
    try {
        pqxx::work tx{c};
        
        pqxx::result before = tx.exec("SELECT gold_cost FROM units WHERE name = 'Footman';");
        std::cout << "Цена до обновления: " << before[0]["gold_cost"].c_str() << " золота\n";
        
        tx.exec("UPDATE units SET gold_cost = gold_cost + 10 WHERE name = 'Footman';");
        
        pqxx::result after = tx.exec("SELECT gold_cost FROM units WHERE name = 'Footman';");
        std::cout << "Цена после обновления: " << after[0]["gold_cost"].c_str() << " золота\n";
        
        tx.commit();
        std::cout << "Обновление выполнено успешно\n\n";
    } catch (const std::exception &e) {
        std::cerr << "Ошибка: " << e.what() << "\n";
    }
}

void deleteAbilityFromHero(pqxx::connection &c) {
    printSeparator();
    std::cout << "Запрос 9: DELETE - удаление способности Divine Shield у Paladin\n";
    printSeparator();
    
    try {
        pqxx::work tx{c};

        pqxx::result before = tx.exec(
            "SELECT a.name FROM abilities a "
            "JOIN unit_abilities ua ON a.ability_id = ua.ability_id "
            "WHERE ua.unit_id = 1;"
        );
        std::cout << "Способности до удаления (" << before.size() << "):\n";
        for (auto const &row : before) {
            std::cout << "  - " << row["name"].c_str() << "\n";
        }
        
        tx.exec("DELETE FROM unit_abilities WHERE unit_id = 1 AND ability_id = 2;");
        
        pqxx::result after = tx.exec(
            "SELECT a.name FROM abilities a "
            "JOIN unit_abilities ua ON a.ability_id = ua.ability_id "
            "WHERE ua.unit_id = 1;"
        );
        std::cout << "Способности после удаления (" << after.size() << "):\n";
        for (auto const &row : after) {
            std::cout << "  - " << row["name"].c_str() << "\n";
        }
        
        tx.commit();
        std::cout << "Удаление выполнено успешно\n\n";
    } catch (const std::exception &e) {
        std::cerr << "Ошибка: " << e.what() << "\n";
    }
}

void queryMinArmorPerRace(pqxx::connection &c) {
    printSeparator();
    std::cout << "Запрос 10: Юниты с минимальной бронёй в каждой расе (подзапрос)\n";
    printSeparator();
    
    try {
        pqxx::work tx{c};
        pqxx::result r = tx.exec(
            "SELECT u.name, r.name AS race, u.armor "
            "FROM units u "
            "JOIN races r ON u.race_id = r.race_id "
            "WHERE u.armor = ("
            "    SELECT MIN(u2.armor) "
            "    FROM units u2 "
            "    WHERE u2.race_id = u.race_id"
            ");"
        );
        
        std::cout << std::setw(40) << std::left << "Unit Name" 
                  << std::setw(20) << "Race" 
                  << std::setw(10) << "Armor" << "\n";
        std::cout << std::string(70, '-') << "\n";
        
        for (auto const &row : r) {
            std::cout << std::setw(40) << std::left << row["name"].c_str()
                      << std::setw(20) << row["race"].c_str()
                      << std::setw(10) << row["armor"].c_str() << "\n";
        }
        
        tx.commit();
        std::cout << "\n";
    } catch (const std::exception &e) {
        std::cerr << "Ошибка: " << e.what() << "\n";
    }
}

int main() {
    try {
        pqxx::connection c{
            "dbname=warcraft3_db "
            "user=sanj "
            "port=5432"
        };

        if (!c.is_open()) {
            std::cerr << "Не удалось открыть соединение с БД\n";
            return 1;
        }

        queryHumanUnits(c);
        queryAllHeroes(c);
        queryUnitAbilities(c);
        queryAverageArmorByRace(c);
        queryExpensiveUnits(c);
        queryUnitCountByRace(c);
        queryUnitsWithoutMana(c);
        updateFootmanCost(c);
        deleteAbilityFromHero(c);
        queryMinArmorPerRace(c);

    } catch (const std::exception &e) {
        std::cerr << "Критическая ошибка: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
