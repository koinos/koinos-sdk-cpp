#pragma once

#include <koinos/system/system_calls.hpp>

namespace koinos::contracts {

namespace detail {
   const std::string claim_name = "claim";
   const std::string governance_name = "governance";
   const std::string koin_name = "koin";
   const std::string pob_name = "pob";
   const std::string resources_name = "resources";
   const std::string vhp_name = "vhp";
}

inline const std::string& claim_address()
{
   static std::string address;

   if ( !address.size() )
      address = system::get_contract_address( detail::claim_name );

   return address;
}

inline const std::string& governance_address()
{
   static std::string address;

   if ( !address.size() )
      address = system::get_contract_address( detail::governance_name );

   return address;
}

inline const std::string& koin_address()
{
   static std::string address;

   if ( !address.size() )
      address = system::get_contract_address( detail::koin_name );

   return address;
}

inline const std::string& pob_address()
{
   static std::string address;

   if ( !address.size() )
      address = system::get_contract_address( detail::pob_name );

   return address;
}

inline const std::string& resources_address()
{
   static std::string address;

   if ( !address.size() )
      address = system::get_contract_address( detail::resources_name );

   return address;
}

inline const std::string& vhp_address()
{
   static std::string address;

   if ( !address.size() )
      address = system::get_contract_address( detail::vhp_name );

   return address;
}

} // koinos::contracts
