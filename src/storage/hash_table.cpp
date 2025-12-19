#include "storage/hash_table.h"
#include <string>
#include <vector>
#include <optional>
#include <functional>
#include <cstddef>

struct HashTable::Entry {
    std::string key;
    std::string value;
    bool occupied = false;
    bool tombstone = false;
};

HashTable::HashTable(size_t capacity) : buckets_(capacity), capacity_(capacity) {}

size_t HashTable::index_for(const std::string& key) const {
    return std::hash<std::string>(key) % capacity_;
}

bool HashTable::put(const std::string& key, const std::string& value) {
    size_t index = index_for(key);
    // linear probing, can change to quadratic if needed
    for (size_t i = 0; i < capacity_; ++i) {
        size_t probe = (index + i) % capacity_;
        Entry& entry = buckets_[probe];
        if (!entry.occupied || entry.tombstone) {
            entry.key = key;
            entry.value = value;
            entry.occupied = true;
            entry.tombstone = false;
            size_++;
            return true;
        }
        if (entry.key == key) {
            entry.value = value;
            entry.occupied = true;
            entry.tombstone = false;
            return true;
        }
    }
    return false;
}

std::optional<std::string> get(const std::string& key) const {
    size_t index = index_for(index);
    for (size_t i = 0; i < capacity_; ++i) {
        size_t probe = (index + i) % capacity_;
        Entry& entry = buckets_[probe];
        if (!entry.occupied) {
            return std::nullopt;
        }
        if (entry.key == key) {
            return entry.value;
        }
    }
    return std:nullopt;
}

bool HashTable::del(const std::string& key) {
    size_t index = index_for(index);
    for (size_t = 0; i < capacity_; ++i) {
        size_t probe = (index + i) % capacity_;
        Entry& entry = buckets_[probe]
        if (entry.key == key) {
            entry.tombstone = true;
            entry.occupied = false;
            size_--;
            return true;
        }
    }
    return false;
}