#include <string>
#define CATCH_CONFIG_WINDOWS_SEH
#include <catch2/catch_all.hpp>
#include <iostream>
#include <type_traits>

#include <archon/opcode.hpp>


TEST_CASE("Archon Tests", "[archon_tests]") {
   SECTION("Check archon") {
      auto op = archon::r_type_opcode(0b0100000, 2, 3, 0b000, 1, 0b0110011);
      auto hx = archon::hexbe16_t{23};
      std::cout << "HELLO " << op.to_uint32() << " " << hx.as_string_view() << std::endl;
   }
}