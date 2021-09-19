#include <markTxn.hpp>


[[eosio::action]]
void markTxn::mark( const checksum256 txn, const string category, const uint8_t confidence, const float fraction, const string memo, const string jsonmemo ) {
    auto idx = category_table.get_index<"secid"_n>();
    auto hash = eosio::sha256( category.c_str(), category.length());
    auto itr = idx.find(hash);
    check (itr != idx.end(), "unknown category");
    check (confidence<=100, "confidence must be between 0 and 100");
    check (fraction>0.0 && fraction<=100.0, "fraction must be between 0 and 100");
}

[[eosio::action]]
void markTxn::addcategory( const string category, name creator, const string memo ) {
    require_auth(creator);
    check(category.size()<max_category_size, "category name too long");
    check(memo.size()<max_memo_size, "memo too long");
    auto idx = category_table.get_index<"secid"_n>();
    auto categories_count = std::distance(category_table.cbegin(),category_table.cend());
    check(categories_count<max_categories_count,
           "reached max number of categories (" + std::to_string(max_categories_count) + ")");
    auto hash = eosio::sha256( category.c_str(), category.length());
    auto itr = idx.find(hash);
    if (itr != idx.end()) {
        check( false, "category name already exists" );
    } else {
        // add category to table
        category_table.emplace( creator, [&]( auto& u ) {
            u.id = category_table.available_primary_key();
            u.category = category;
            u.category_hash = hash;
            u.creator = creator;
            u.memo = memo;
        } );
    }
}

[[eosio::action]]
void markTxn::delcategory( const string category, name deleter, const string memo ) {
    require_auth(deleter);
    auto idx = category_table.get_index<"secid"_n>();
    auto hash = eosio::sha256( category.c_str(), category.length());
    auto itr = idx.find(hash);
    check (itr != idx.end(), "unknown category");
    auto ptr = category_table.find(itr->id);
    category_table.erase(ptr);
}

[[eosio::action]]
void markTxn::categorylist() {
    for ( auto itr = category_table.begin(); itr != category_table.end(); itr++ ) {
        print (itr->category, " ", itr->creator, " ", itr->memo);
    }
}


