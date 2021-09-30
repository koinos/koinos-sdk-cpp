#pragma once
#include <koinos/system/system_calls.hpp>
#include <koinos/contracts/token/token.h>

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

constexpr std::size_t max_address_size = 25;

using name_return = koinos::contracts::token::name_return< 32 >;
using symbol_return = koinos::contracts::token::symbol_return< 8 >;

} // detail

class token
{
   private:
      std::string _contract_address;

   public:
      inline token( const std::string& contract_address ) :
         _contract_address( contract_address )
      {}

      inline std::string name()
      {
         auto retstr = system::call_contract( _contract_address, detail::entries::name_entry, std::string() );
         koinos::read_buffer buf( (uint8_t*)retstr.data(), retstr.size() );
         detail::name_return ret;
         ret.deserialize( buf );
         return std::string( ret.get_value().get_const(), ret.get_value().get_length() );
      }

      inline std::string symbol()
      {
         auto retstr = system::call_contract( _contract_address, detail::entries::symbol_entry, std::string() );
         koinos::read_buffer buf( (uint8_t*)retstr.data(), retstr.size() );
         detail::symbol_return ret;
         ret.deserialize( buf );
         return std::string( ret.get_value().get_const(), ret.get_value().get_length() );
      }

      inline uint8_t decimals()
      {
         auto retstr = system::call_contract( _contract_address, detail::entries::decimals_entry, std::string() );
         koinos::read_buffer buf( (uint8_t*)retstr.data(), retstr.size() );
         koinos::contracts::token::decimals_return ret;
         ret.deserialize( buf );
         return ret.get_value();
      }

      inline uint64_t total_supply()
      {
         auto retstr = system::call_contract( _contract_address, detail::entries::total_supply_entry, std::string() );
         koinos::read_buffer buf( (uint8_t*)retstr.data(), retstr.size() );
         koinos::contracts::token::total_supply_return ret;
         ret.deserialize( buf );
         return ret.get_value();
      }

      inline uint64_t balance_of( const std::string& owner )
      {
         koinos::contracts::token::balance_of_args< detail::max_address_size > args;
         std::array< uint8_t, 1024 > buffer;
         args.mutable_owner().set( const_cast< uint8_t* >( reinterpret_cast< const uint8_t* >( owner.data() ) ), owner.size() );
         koinos::write_buffer wbuf( buffer.data(), buffer.size() );
         args.serialize( wbuf );

         auto retstr = system::call_contract( _contract_address, detail::entries::balance_of_entry, std::string( reinterpret_cast< char* >( wbuf.data() ), wbuf.get_size() ) );
         koinos::read_buffer buf( (uint8_t*)retstr.data(), retstr.size() );
         koinos::contracts::token::balance_of_return ret;
         ret.deserialize( buf );
         return ret.get_value();
      }

      inline bool transfer( const std::string& from, const std::string& to, const uint64_t& value )
      {
         koinos::contracts::token::transfer_args< detail::max_address_size, detail::max_address_size > args;
         std::array< uint8_t, 1024 > buffer;
         args.mutable_from().set( const_cast< uint8_t* >( reinterpret_cast< const uint8_t* >( from.data() ) ), from.size() );
         args.mutable_from().set( const_cast< uint8_t* >( reinterpret_cast< const uint8_t* >( to.data() ) ), to.size() );
         args.mutable_value() = value;
         koinos::write_buffer wbuf( buffer.data(), buffer.size() );
         args.serialize( wbuf );

         auto retstr = system::call_contract( _contract_address, detail::entries::transfer_entry, std::string( reinterpret_cast< char* >( wbuf.data() ), wbuf.get_size() ) );
         koinos::read_buffer buf( (uint8_t*)retstr.data(), retstr.size() );
         koinos::contracts::token::transfer_return ret;
         ret.deserialize( buf );
         return ret.get_value();
      }

      inline bool mint( const std::string& to, const uint64_t& value )
      {
         koinos::contracts::token::mint_args< detail::max_address_size > args;
         std::array< uint8_t, 1024 > buffer;
         args.mutable_to().set( const_cast< uint8_t* >( reinterpret_cast< const uint8_t* >( to.data() ) ), to.size() );
         args.mutable_value() = value;
         koinos::write_buffer wbuf( buffer.data(), buffer.size() );
         args.serialize( wbuf );

         auto retstr = system::call_contract( _contract_address, detail::entries::mint_entry, std::string( reinterpret_cast< char* >( wbuf.data() ), wbuf.get_size() ) );
         koinos::read_buffer buf( (uint8_t*)retstr.data(), retstr.size() );
         koinos::contracts::token::mint_return ret;
         ret.deserialize( buf );
         return ret.get_value();
      }
};

} // koinos
