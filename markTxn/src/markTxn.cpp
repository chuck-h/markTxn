#include <markTxn.hpp>


[[eosio::action]]
void markTxn::mark( checksum256 txn, string category, uint8_t confidence, float fraction, string memo ) {
    // validate category against list
    // validate range for confidence, fraction
    // is there any way to check that the txn id is valid within a contract?
}

[[eosio::action]]
void markTxn::register_category( string category, string memo ); {
    // check for duplicate category name
    // check for name too big
    // check for list too big
    // update list
}

[[eosio::action]]
void markTxn::unregister_category( string category, string memo ); {
    // check that category name is on list
    // update list
}

