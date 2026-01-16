#pragma once

#include <cstdint>
#include <array>
#include <bit>
#include <string_view>
#include <utility>

namespace archon {

   template <std::size_t Bytes, std::endian Endianess>
   struct hexcode {
      constexpr static std::size_t bits = Bytes * 8;
      constexpr static std::endian endianess = Endianess;
      constexpr static std::size_t cardinality = 2;

      constexpr static auto digits = std::array{
         "00","01","02","03","04","05","06","07","08","09","0A","0B","0C","0D","0E","0F",
         "10","11","12","13","14","15","16","17","18","19","1A","1B","1C","1D","1E","1F",
         "20","21","22","23","24","25","26","27","28","29","2A","2B","2C","2D","2E","2F",
         "30","31","32","33","34","35","36","37","38","39","3A","3B","3C","3D","3E","3F",
         "40","41","42","43","44","45","46","47","48","49","4A","4B","4C","4D","4E","4F",
         "50","51","52","53","54","55","56","57","58","59","5A","5B","5C","5D","5E","5F",
         "60","61","62","63","64","65","66","67","68","69","6A","6B","6C","6D","6E","6F",
         "70","71","72","73","74","75","76","77","78","79","7A","7B","7C","7D","7E","7F",
         "80","81","82","83","84","85","86","87","88","89","8A","8B","8C","8D","8E","8F",
         "90","91","92","93","94","95","96","97","98","99","9A","9B","9C","9D","9E","9F",
         "A0","A1","A2","A3","A4","A5","A6","A7","A8","A9","AA","AB","AC","AD","AE","AF",
         "B0","B1","B2","B3","B4","B5","B6","B7","B8","B9","BA","BB","BC","BD","BE","BF",
         "C0","C1","C2","C3","C4","C5","C6","C7","C8","C9","CA","CB","CC","CD","CE","CF",
         "D0","D1","D2","D3","D4","D5","D6","D7","D8","D9","DA","DB","DC","DD","DE","DF",
         "E0","E1","E2","E3","E4","E5","E6","E7","E8","E9","EA","EB","EC","ED","EE","EF",
         "F0","F1","F2","F3","F4","F5","F6","F7","F8","F9","FA","FB","FC","FD","FE","FF"
      };

      constexpr inline hexcode(uint64_t value = 0)
         : bytes(generate_array(value, std::make_index_sequence<Bytes>{})) {
      }

      template <std::size_t... Is>
      constexpr static inline std::array<char, Bytes * cardinality> generate_array(uint64_t value, std::index_sequence<Is...>) {
         constexpr auto offset = [](std::size_t i) {
            if constexpr (endianess == std::endian::little) {
               return i * 8;
            } else {
               return (bits - 8 - (i * 8));
            }
         };

         std::array<char, Bytes * cardinality> output;
         (
            (
               output[cardinality * Is + 0] = digits[(value >> offset(Is)) & 0xFF][0],
               output[cardinality * Is + 1] = digits[(value >> offset(Is)) & 0xFF][1]
            ),
            ...
         );
         return output;
      }

      constexpr inline std::string_view as_string_view() const {
         return std::string_view{bytes.data(), bytes.size()};
      }

      std::array<char, Bytes * cardinality> bytes;
   };

   template <std::endian Endian=std::endian::native>
   using hex8_t  = hexcode<1, Endian>;
   template <std::endian Endian=std::endian::native>
   using hex16_t = hexcode<2, Endian>;
   template <std::endian Endian=std::endian::native>
   using hex32_t = hexcode<4, Endian>;
   template <std::endian Endian=std::endian::native>
   using hex64_t = hexcode<8, Endian>;

   using hexle8_t  = hex8_t<std::endian::little>;
   using hexle16_t = hex16_t<std::endian::little>;
   using hexle32_t = hex32_t<std::endian::little>;
   using hexle64_t = hex64_t<std::endian::little>;

   using hexbe8_t  = hex8_t<std::endian::big>;
   using hexbe16_t = hex16_t<std::endian::big>;
   using hexbe32_t = hex32_t<std::endian::big>;
   using hexbe64_t = hex64_t<std::endian::big>;

} // namespace archon