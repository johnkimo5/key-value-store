#include <string>
#include <optional>
#include <cstddef>

class HashTable {
public:
    explicit HashTable(size_t capacity = 1024);
    bool put(const std::string& key, const std::string& value);
    std::optional<std::string> get(const std::string& key) const;
    bool del(const std::string& key);

private:
    struct Entry;
    size_t index_for(const std::string& key) const;
};