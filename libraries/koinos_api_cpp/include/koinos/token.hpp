#pragma once
#include <koinos/system/system_calls.hpp>

namespace koinos {

namespace detail {

enum entries : uint32_t
{
   name_entry         = 0x76ea4297,
   symbol_entry       = 0x7e794b24,
   decimals_entry     = 0x59dc15ce,
   total_supply_entry = 0xcf2e8212,
   balance_of_entry   = 0x15619248,
   transfer_entry     = 0x62efa292,
   mint_entry         = 0xc2f82bdc
};

struct transfer_args
{
   protocol::account_type from;
   protocol::account_type to;
   uint64_t               value;
};

struct mint_args
{
   protocol::account_type to;
   uint64_t               value;
};

} // detail

class token
{
   private:
      contract_id_type _contract_address;

   public:
      inline token( const contract_id_type& contract_address ) :
         _contract_address( contract_address )
      {}

      inline token( const protocol::account_type& contract_address ) :
         _contract_address( pack::from_variable_blob< contract_id_type >( contract_address ) )
      {}

      inline token( const uint160_t& contract_address ) :
         _contract_address( pack::from_variable_blob< contract_id_type >( pack::to_variable_blob( contract_address ) ) )
      {}

      inline std::string name()
      {
         return pack::from_variable_blob< std::string >(
            system::execute_contract(
               _contract_address,
               detail::entries::name_entry,
               variable_blob()
            )
         );
      }

      inline std::string symbol()
      {
         return pack::from_variable_blob< std::string >(
            system::execute_contract(
               _contract_address,
               detail::entries::symbol_entry,
               variable_blob()
            )
         );
      }

      inline uint8_t decimals()
      {
         return pack::from_variable_blob< uint8_t >(
            system::execute_contract(
               _contract_address,
               detail::entries::decimals_entry,
               variable_blob()
            )
         );
      }

      inline uint64_t total_supply()
      {
         return pack::from_variable_blob< uint64_t >(
            system::execute_contract(
               _contract_address,
               detail::entries::total_supply_entry,
               variable_blob()
            )
         );
      }

      inline uint64_t balance_of( const protocol::account_type& owner )
      {
         return pack::from_variable_blob< uint64_t >(
            system::execute_contract(
               _contract_address,
               detail::entries::balance_of_entry,
               pack::to_variable_blob( owner )
            )
         );
      }

      inline bool transfer( const protocol::account_type& from, const protocol::account_type& to, const uint64_t& value )
      {
         return pack::from_variable_blob< bool >(
            system::execute_contract(
               _contract_address,
               detail::entries::transfer_entry,
               pack::to_variable_blob( detail::transfer_args {
                  .from = from,
                  .to = to,
                  .value = value
               } )
            )
         );
      }

      inline bool mint( const protocol::account_type& to, const uint64_t& value )
      {
         return pack::from_variable_blob< bool >(
            system::execute_contract(
               _contract_address,
               detail::entries::mint_entry,
               pack::to_variable_blob( detail::mint_args {
                  .to = to,
                  .value = value
               } )
            )
         );
      }
};

} // koinos

KOINOS_REFLECT( koinos::detail::transfer_args, (from)(to)(value) );
KOINOS_REFLECT( koinos::detail::mint_args,     (to)(value) );
