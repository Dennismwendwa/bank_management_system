#ifndef STORAGE_FACTORY_HPP
#define STORAGE_FACTORY_HPP

#include <memory>


inline std::shared_ptr<IStorage> createStorage() {
    auto db = "";//std::make_shared<DatabaseStorage>("db-url");
    if (db->connect()) {
        std::cout << "Connected to database.\n";
        return db;
    } else {
        return std::make_shared<CSVStorage>("users.csv");
    }
}

#endif