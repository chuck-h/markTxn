#include <eosio/eosio.hpp>
using namespace eosio;
using std::string;

class [[eosio::contract]] markTxn : public contract {
   public:
      using contract::contract;
      markTxn(name receiver, name code, datastream<const char *> ds) :
         contract(receiver, code, ds) {
         }

      [[eosio::action]]
      void mark( checksum256 txn, string category, uint8_t confidence, float fraction, string memo );

      [[eosio::action]]
      void register_category( string category, string memo );

      [[eosio::action]]
      void unregister_category( string category, string memo );

      using mark_action = eosio::action_wrapper<"mark"_n, &markTxn::mark>;
      using register_category_action = eosio::action_wrapper<"register"_n, &markTxn::register_category>;
      using unregister_category_action = eosio::action_wrapper<"unregister"_n, &markTxn::unregister_category>;
   private:
};
