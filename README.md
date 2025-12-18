# 🔑 KVStore — Educational C++ Key–Value Store (Hash Table + WAL)

KVStore is a **minimal, durable key–value store written in C++**.

It’s designed as a **learning project for low-level systems** — not as a production database. The focus is on:

- Custom **in-memory hash table** (no `std::unordered_map` for storage)
- **Write-Ahead Log (WAL)** for durability
- **Crash recovery** by replaying the WAL
- Clean, simple **C++ API** and a small **CLI/REPL**

Think of it as a tiny, educational version of “Redis with persistence,” built from scratch.

---

## 🎯 Goals

- Learn **memory layout**, hashing, and probe strategies by implementing our own hash table.
- Understand **durability** and **crash consistency** with a real write-ahead log.
- Practice **file I/O**, binary formats, and basic OS concepts.
- Build a foundation we can extend later (snapshots, LSM-tree, sharding, etc.).

Non-goals (for v1.0):

- No distributed system features.
- No multi-node replication.
- No LSM-tree or SSTables yet.
- No advanced transactions or query mechanisms.

Those may come in v2+.

---

## 🧱 High-Level Design

### 1. In-Memory Hash Table

The main data structure is a **custom open-addressing hash table**:

- Keys: `std::string`
- Values: `std::string` (or `std::vector<uint8_t>` internally)
- Collision handling via **linear** or **quadratic probing**
- **Tombstones** to support delete operations
- **Resizing** when load factor exceeds a threshold

Supported operations:

```cpp
bool put(const std::string& key, const std::string& value);
std::optional<std::string> get(const std::string& key) const;
bool remove(const std::string& key);
