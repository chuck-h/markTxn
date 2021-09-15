#include <markTxn.hpp>


[[eosio::action]]
void markTxn::mark( const checksum256 txn, const string category, const uint8_t confidence, const float fraction, const string memo ) {
    auto itr = category_entries.find(category);
    check (itr != category_entries.end(), "unknown category");
    check (confidence<=100, "confidence must be between 0 and 100");
    check (fraction>0.0 && fraction<=100.0, "fraction must be between 0 and 100");
}

[[eosio::action]]
void markTxn::addcategory( const string category, name creator, const string memo ) {
    require_auth(creator);
    check(categories_count<max_categories_count,
           "reached max number of categories (" + std::to_string(max_categories_count) + ")");
    check(category.size()<max_category_size, "category name too long");
    check(memo.size()<max_memo_size, "memo too long");
    auto itr = category_entries.find(category);
    if (itr != category_entries.end()) {
        check( false, "category name already exists" );
    } else {
        // add category to table
        category_entries[category] = category_entry{category, creator, memo};
        categories_count++;
    }
}

[[eosio::action]]
void markTxn::delcategory( const string category, name deleter, const string memo ) {
    require_auth(deleter);
    auto itr = category_entries.find(category);
    check (itr != category_entries.end(), "unknown category");
    category_entries.erase(category);
    categories_count--;
}

[[eosio::action]]
std::vector<category_entry> markTxn::categories() {
    std::vector<category_entry> rv;
    for ( const auto& entry : category_entries ) {
        rv.push_back(entry.second());
    }
    return rv;
}


