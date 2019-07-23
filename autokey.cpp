#include <eosio/eosio.hpp>

using namespace eosio;

CONTRACT autokey: public contract {
public:
using contract::contract;

ACTION insertkey() {
// require_auth(get_self()); //주석처리하면 모든 계정이 접근이 가능해진다

Autokey myTable(get_self(), get_self().value);
myTable.emplace(get_self(), [&](auto& row) {
row.mykey = myTable.available_primary_key();//자동으로 1씩 증가한 값 저장
});
}

private:
TABLE example_struct {
uint64_t mykey;

uint64_t primary_key() const { return mykey; }
};

typedef multi_index<"autokeys"_n, example_struct> Autokey;
};