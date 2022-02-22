#pragma once

#include <koinos/system/system_calls.hpp>

namespace koinos {

namespace detail {
   constexpr char default_prefix = 0x00;
}

namespace multicodec {

constexpr uint64_t sha1       = 0x11;
constexpr uint64_t sha2_256   = 0x12;
constexpr uint64_t sha2_512   = 0x13;
constexpr uint64_t keccak_256 = 0x1b;
constexpr uint64_t ripemd_160 = 0x1053;

}

struct multihash
{
   uint64_t    code = 0;
   std::string digest;

   void deserialize( const std::string& );
   std::string serialize();
};

inline std::string address_from_public_key( const std::string& pub_key, char prefix = detail::default_prefix )
{
   // Address is:
   // 1 byte prefix
   // 20 byte ripemd
   // 4 byte checksum

   multihash sha256, ripemd160;
   sha256.deserialize( system::hash( multicodec::sha2_256, pub_key ) );
   ripemd160.deserialize( system::hash( multicodec::ripemd_160, sha256.digest ) );
   std::string address( ripemd160.digest.size() + 1, prefix );
   std::memcpy( const_cast< char* >( address.data() ) + 1, ripemd160.digest.data(), ripemd160.digest.size() );
   sha256.deserialize( system::hash( multicodec::sha2_256, address ) );
   sha256.deserialize( system::hash( multicodec::sha2_256, sha256.digest ) );
   address.resize( address.size() + 4 );
   std::memcpy( const_cast< char* >( address.data() ) + address.size() - 4, sha256.digest.data(), 4 );
   return address;
}

} // koinos
