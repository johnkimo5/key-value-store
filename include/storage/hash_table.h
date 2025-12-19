#include <string>
#include <optional>
#include <cstddef>

class HashTable {
public:
    // Constructor
    explicit HashTable(size_t capacity = 1024);
    // Methods
    bool put(const std::string& key, const std::string& value);
    std::optional<std::string> get(const std::string& key) const;
    bool del(const std::string& key);
    // Member variables
    std::vector<Entry> buckets_;
    size_t capacity_;
    size_t size_;

private:
    struct Entry;
    size_t index_for(const std::string& key) const;
};