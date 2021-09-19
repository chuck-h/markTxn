#include <eosio/eosio.hpp>
#include <eosio/crypto.hpp>

using namespace eosio;
using std::string;

struct category_info {
   string category;
   name creator;
   string memo;
};

class [[eosio::contract]] markTxn : public contract {
   public:
      using contract::contract;
      markTxn(name receiver, name code, datastream<const char *> ds) :
         contract(receiver, code, ds),
         max_categories_count(100),
         max_category_size(32),
         max_memo_size(255),
         category_table( receiver, receiver.value ) {
         }

      [[eosio::action]]
      void mark( const checksum256 txn, const string category, const uint8_t confidence, const float fraction, const string memo, const string jsonmemo );

      [[eosio::action]]
      void addcategory( const string category, name creator, const string memo );

      [[eosio::action]]
      void delcategory(const string category, name deleter, const string memo );

      [[eosio::action]]
      void categorylist();

      using mark_action = eosio::action_wrapper<"mark"_n, &markTxn::mark>;
      using addcategory_action = eosio::action_wrapper<"addcategory"_n, &markTxn::addcategory>;
      using delcategory_action = eosio::action_wrapper<"delcategory"_n, &markTxn::delcategory>;
      using categories_action = eosio::action_wrapper<"categorylist"_n, &markTxn::categorylist>;
   private:
      uint32_t max_categories_count;
      uint32_t max_category_size;
      uint32_t max_memo_size;
   struct [[eosio::table]] categories {
      uint64_t id; // auto-incrementing
      std::string category;
      eosio::checksum256 category_hash;
      eosio::name creator;
      std::string memo;
      uint64_t primary_key() const { return id; }
      eosio::checksum256 by_secondary( ) const { return category_hash; }
   };
   typedef multi_index<"categories"_n, categories,
     eosio::indexed_by<"secid"_n,
     eosio::const_mem_fun<categories, eosio::checksum256, &categories::by_secondary>>
    > cat_table;
   cat_table category_table;

};
