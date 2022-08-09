#include <koinos/crypto.hpp>

#include <koinos/buffer.hpp>

namespace koinos {

struct unsigned_varint
{
   unsigned_varint( uint64_t v ) : value( v ) {}
   unsigned_varint() = default;
   uint64_t value = 0;
};

void to_binary( EmbeddedProto::WriteBufferInterface& s, const unsigned_varint& v )
{
   uint8_t tmp[ ( sizeof( v.value ) * 8 + 6 ) / 7 ];
   uint64_t n = v.value;
   uint32_t len = 0;

   while ( true )
   {
      tmp[ len ] = ( n & 0x7F );

      if ( n <= 0x7F )
         break;

      tmp[ len ] |= 0x80;
      n = ( n >> 7 );
      len++;
   }

   s.push( tmp, len + 1 );
}

void from_binary( EmbeddedProto::ReadBufferInterface& s, unsigned_varint& v )
{
   v.value = 0;
   uint8_t data = 0;
   uint32_t i = 0;
   do
   {
      if ( !s.get_size() )
         throw std::runtime_error( "error reading from stream" );

      s.pop( data );

      v.value |= ( data & 0x7f ) << i;
      i += 7;
   } while( data & 0x80 );
}

void multihash::deserialize( const std::string& s )
{
   read_buffer rb( reinterpret_cast< const uint8_t* >( s.data() ), s.size() );

   unsigned_varint mh_code;
   unsigned_varint mh_size;

   from_binary( rb, mh_code );
   from_binary( rb, mh_size );

   digest.resize( mh_size.value );
   auto data = reinterpret_cast< uint8_t* >( digest.data() );
   for ( uint64_t i = 0; i < mh_size.value; i++ )
   {
      rb.pop( data[ i ] );
   }

   code = mh_code.value;
}

std::string multihash::serialize()
{
   uint8_t buffer[ 532 ];
   write_buffer wb( buffer, 532 );

   unsigned_varint mh_code{ code };
   unsigned_varint mh_size{ digest.size() };

   to_binary( wb, mh_code );
   to_binary( wb, mh_size );

   wb.push( reinterpret_cast< const uint8_t* >( digest.data() ), digest.size() );

   return std::string( (const char*)wb.data(), (size_t)wb.get_size() );
}

} // koinos
