#pragma once
#include <koinos/system/system_calls.hpp>
#include <koinos/chain/error.h>
#include <koinos/contracts/token/token.h>

namespace koinos {

namespace detail {

enum entries : uint32_t
{
   name_entry         = 0x82a3537f,
   symbol_entry       = 0xb76a7ca1,
   decimals_entry     = 0xee80fd2f,
   total_supply_entry = 0xb0da3934,
   balance_of_entry   = 0x5c721497,
   transfer_entry     = 0x27f576ca,
   mint_entry         = 0xdc6f17bb,
   burn_entry         = 0x859facc5
};

constexpr std::size_t max_address_size = 25;

using name_result = koinos::contracts::token::name_result< 32 >;
using symbol_result = koinos::contracts::token::symbol_result< 8 >;

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
         auto [ code, ret_value ] = system::call( _contract_address, detail::entries::name_entry, std::string() );
         if ( code != 0 )
            system::revert();
         koinos::read_buffer buf( (uint8_t*)ret_value.get_object().get_const(), ret_value.get_object().get_length() );
         detail::name_result res;
         res.deserialize( buf );
         return std::string( res.get_value().get_const(), res.get_value().get_length() );
      }

      inline std::string symbol()
      {
         auto [ code, ret_value ] = system::call( _contract_address, detail::entries::symbol_entry, std::string() );
         if ( code != 0 )
            system::revert();
         koinos::read_buffer buf( (uint8_t*)ret_value.get_object().get_const(), ret_value.get_object().get_length() );
         detail::symbol_result res;
         res.deserialize( buf );
         return std::string( res.get_value().get_const(), res.get_value().get_length() );
      }

      inline uint8_t decimals()
      {
         auto [ code, ret_value ] = system::call( _contract_address, detail::entries::decimals_entry, std::string() );
         if ( code != 0 )
            system::revert();
         koinos::read_buffer buf( (uint8_t*)ret_value.get_object().get_const(), ret_value.get_object().get_length() );
         koinos::contracts::token::decimals_result res;
         res.deserialize( buf );
         return res.get_value();
      }

      inline uint64_t total_supply()
      {
         auto [ code, ret_value ] = system::call( _contract_address, detail::entries::total_supply_entry, std::string() );
         if ( code != 0 )
            system::revert();
         koinos::read_buffer buf( (uint8_t*)ret_value.get_object().get_const(), ret_value.get_object().get_length() );
         koinos::contracts::token::total_supply_result res;
         res.deserialize( buf );
         return res.get_value();
      }

      inline uint64_t balance_of( const std::string& owner )
      {
         koinos::contracts::token::balance_of_arguments< detail::max_address_size > args;
         std::array< uint8_t, 1024 > buffer;
         args.mutable_owner().set( const_cast< uint8_t* >( reinterpret_cast< const uint8_t* >( owner.data() ) ), owner.size() );
         koinos::write_buffer wbuf( buffer.data(), buffer.size() );
         args.serialize( wbuf );

         auto [ code, ret_value ] = system::call( _contract_address, detail::entries::balance_of_entry, std::string( reinterpret_cast< char* >( wbuf.data() ), wbuf.get_size() ) );
         koinos::read_buffer buf( (uint8_t*)ret_value.get_object().get_const(), ret_value.get_object().get_length() );
         koinos::contracts::token::balance_of_result res;
         res.deserialize( buf );
         return res.get_value();
      }

      inline bool transfer( const std::string& from, const std::string& to, const uint64_t& value )
      {
         koinos::contracts::token::transfer_arguments< detail::max_address_size, detail::max_address_size > args;
         std::array< uint8_t, 1024 > buffer;
         args.mutable_from().set( const_cast< uint8_t* >( reinterpret_cast< const uint8_t* >( from.data() ) ), from.size() );
         args.mutable_to().set( const_cast< uint8_t* >( reinterpret_cast< const uint8_t* >( to.data() ) ), to.size() );
         args.mutable_value() = value;
         koinos::write_buffer wbuf( buffer.data(), buffer.size() );
         args.serialize( wbuf );

         auto [ code, ret_value ] = system::call( _contract_address, detail::entries::transfer_entry, std::string( reinterpret_cast< char* >( wbuf.data() ), wbuf.get_size() ) );
         return code == std::underlying_type_t< koinos::chain::error_code >( koinos::chain::error_code::success );
      }

      inline bool mint( const std::string& to, const uint64_t& value )
      {
         koinos::contracts::token::mint_arguments< detail::max_address_size > args;
         std::array< uint8_t, 1024 > buffer;
         args.mutable_to().set( const_cast< uint8_t* >( reinterpret_cast< const uint8_t* >( to.data() ) ), to.size() );
         args.mutable_value() = value;
         koinos::write_buffer wbuf( buffer.data(), buffer.size() );
         args.serialize( wbuf );

         auto [ code, ret_value ] = system::call( _contract_address, detail::entries::mint_entry, std::string( reinterpret_cast< char* >( wbuf.data() ), wbuf.get_size() ) );
         return code == std::underlying_type_t< koinos::chain::error_code >( koinos::chain::error_code::success );
      }

      inline bool burn( const std::string& from, const uint64_t& value )
      {
         koinos::contracts::token::burn_arguments< detail::max_address_size > args;
         std::array< uint8_t, 1024 > buffer;
         args.mutable_from().set( const_cast< uint8_t* >( reinterpret_cast< const uint8_t* >( from.data() ) ), from.size() );
         args.mutable_value() = value;
         koinos::write_buffer wbuf( buffer.data(), buffer.size() );
         args.serialize( wbuf );

         auto [ code, ret_value ] = system::call( _contract_address, detail::entries::burn_entry, std::string( reinterpret_cast< char* >( wbuf.data() ), wbuf.get_size() ) );
         return code == std::underlying_type_t< koinos::chain::error_code >( koinos::chain::error_code::success );
      }
};

} // koinos
