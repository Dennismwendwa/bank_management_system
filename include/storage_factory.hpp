#ifndef STORAGE_FACTORY_HPP
#define STORAGE_FACTORY_HPP

#include <memory>
#include "csv_storage.hpp"
#include "db_storage.hpp"


inline std::shared_ptr<IStorage> createStorage() {
    auto db = std::make_shared<DatabaseStorage>(
        "dbname=bank user=postgres password=postgres host=localhost port=5432");
    if (db->connect()) {
        std::cout << "Connected to database.\n";
        return db;
    } else {
        return std::make_shared<CSVStorage>("users.csv");
    }
}

#endif