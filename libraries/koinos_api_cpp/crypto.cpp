#include <koinos/crypto.hpp>

#include <sstream>

namespace koinos {

struct unsigned_varint
{
   unsigned_varint( uint64_t v ) : value( v ) {}
   unsigned_varint() = default;
   uint64_t value = 0;
};

void to_binary( std::ostream& s, const unsigned_varint& v )
{
   char tmp[ ( sizeof( v.value ) * 8 + 6 ) / 7 ];
   uint64_t n = v.value;
   uint32_t len = 0;

   while ( true )
   {
      tmp[len] = ( n & 0x7F );

      if ( n <= 0x7F )
         break;

      tmp[len] |= 0x80;
      n = ( n >> 7 );
      len++;
   }

   for ( uint32_t i = 0; i <= len; i++ )
   {
      s.write( tmp + i, sizeof( char ) );
   }
}

void from_binary( std::istream& s, unsigned_varint& v )
{
   v.value = 0;
   char data = 0;
   uint32_t i = 0;
   do
   {
      s.get( data );

      if ( !( s.good() ) )
         throw std::runtime_error( "error reading from stream" );

      v.value |= ( data & 0x7f ) << i;
      i += 7;
   } while( data & 0x80 );
}

void multihash::deserialize( const std::string& s )
{
   std::stringstream ss( s );

   unsigned_varint mh_code;
   unsigned_varint mh_size;

   from_binary( ss, mh_code );
   from_binary( ss, mh_size );

   digest.resize( mh_size.value );
   ss.read( reinterpret_cast< char* >( digest.data() ), mh_size.value );

   code = mh_code.value;
}

std::string multihash::serialize()
{
   unsigned_varint mh_code{ code };
   unsigned_varint mh_size{ digest.size() };

   std::stringstream ss;

   to_binary( ss, mh_code );
   to_binary( ss, mh_size );

   ss.write( digest.data(), digest.size() );
}

} // koinos
