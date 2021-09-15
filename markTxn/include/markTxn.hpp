#include <eosio/eosio.hpp>
using namespace eosio;
using std::string;

struct category_entry {
  std::string category;
  eosio::name creator;
  std::string memo;

  std::string get_category() const { return category; }
  eosio::name get_creator() const { return creator; }
  std::string get_memo() const { return memo; }
};

class [[eosio::contract]] markTxn : public contract {
   public:
      using contract::contract;
      using category_table = eosio::kv::map<"categories"_n, std::string, category_entry>;
      markTxn(name receiver, name code, datastream<const char *> ds) :
         contract(receiver, code, ds),
         max_categories_count(100),
         max_category_size(32),
         max_memo_size(255),
         categories_count(0) {
         }

      [[eosio::action]]
      void mark( const checksum256 txn, const string category, const uint8_t confidence, const float fraction, const string memo );

      [[eosio::action]]
      void addcategory( const string category, name creator, const string memo );

      [[eosio::action]]
      void delcategory(const string category, name deleter, const string memo );

      [[eosio::action]]
      std::vector<category_entry> categories();

      using mark_action = eosio::action_wrapper<"mark"_n, &markTxn::mark>;
      using addcategory_action = eosio::action_wrapper<"addcategory"_n, &markTxn::addcategory>;
      using delcategory_action = eosio::action_wrapper<"delcategory"_n, &markTxn::delcategory>;
      using categories_action = eosio::action_wrapper<"categories"_n, &markTxn::categories>;
   private:
      uint32_t max_categories_count;
      uint32_t max_category_size;
      uint32_t max_memo_size;
      category_table category_entries{"categories"_n};
      uint32_t categories_count;

};
