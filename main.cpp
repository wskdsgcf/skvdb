#include <iostream>
#include "rocksdb/db.h"
#include "rocksdb/write_batch.h"

using namespace std;

int main() {
    rocksdb::DB *db;
    rocksdb::Options options;
    options.create_if_missing = true;
    rocksdb::Status status = rocksdb::DB::Open(options, "testdb", &db);
    assert(status.ok());
    cout << "Open rocksdb success!" << endl;

    string key1 = "1";
    string value1 = "aaaa";
    status = db->Put(rocksdb::WriteOptions(), key1, value1);
    assert(status.ok());
    printf("Put[%s,%s] success.\n", key1.c_str(), value1.c_str());

    string key2 = "2";
    string value;
    status = db->Get(rocksdb::ReadOptions(), key1, &value);
    if (status.ok()) {
        rocksdb::WriteBatch batch;
        batch.Delete(key1);
        batch.Put(key2, value);
        status = db->Write(rocksdb::WriteOptions(), &batch);
        assert(status.ok());
        printf("Move key[%s] value to key[%s] value success.\n", key1.c_str(), key2.c_str());
    }
    status = db->Get(rocksdb::ReadOptions(), key2, &value);
    assert(status.ok());
    printf("Get key[%s] = %s.", key2.c_str(), value.c_str());

    status = db->Delete(rocksdb::WriteOptions(), key2);
    assert(status.ok());
    printf("Delete key[%s] success", key2.c_str());

    delete db;
    return 0;
}
