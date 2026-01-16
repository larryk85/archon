#pragma once

#include <cstdint>

#include <array>
#include <string_view>

#include "hexcode.hpp"

namespace archon {

   struct opcode {
      uint8_t value : 7;
   };

   struct r_type_opcode {
      uint32_t funct7 : 7;
      uint32_t rs2    : 5;
      uint32_t rs1    : 5;
      uint32_t funct3 : 3;
      uint32_t rd     : 5;
      uint32_t opcode : 7;

      constexpr r_type_opcode(uint32_t instr)
          : funct7((instr >> 25) & 0x7F)
          , rs2((instr >> 20) & 0x1F)
          , rs1((instr >> 15) & 0x1F)
          , funct3((instr >> 12) & 0x07)
          , rd((instr >> 7) & 0x1F)
          , opcode(instr & 0x7F)
      {}

      constexpr r_type_opcode(uint8_t opc)
          : funct7(0)
          , rs2(0)
          , rs1(0)
          , funct3(0)
          , rd(0)
          , opcode(opc)
      {}

      constexpr r_type_opcode(uint8_t f7, uint8_t r2, uint8_t r1, uint8_t f3, uint8_t d, uint8_t opc)
          : funct7(f7)
          , rs2(r2)
          , rs1(r1)
          , funct3(f3)
          , rd(d)
          , opcode(opc)
      {}

      constexpr uint32_t to_uint32() const {
          return (static_cast<uint32_t>(funct7) << 25) |
                 (static_cast<uint32_t>(rs2)    << 20) |
                 (static_cast<uint32_t>(rs1)    << 15) |
                 (static_cast<uint32_t>(funct3) << 12) |
                 (static_cast<uint32_t>(rd)     << 7)  |
                 (static_cast<uint32_t>(opcode));
      }
   };

   struct i_type_opcode {
      uint32_t imm    : 12;
      uint32_t rs1    : 5;
      uint32_t funct3 : 3;
      uint32_t rd     : 5;
      uint32_t opcode : 7;
   };

   struct s_type_opcode {
      uint32_t imm15_5 : 5;
      uint32_t rs2    : 5;
      uint32_t rs1    : 5;
      uint32_t funct3 : 3;
      uint32_t imm4_0: 7;
      uint32_t opcode : 7;
   };

   struct b_type_opcode {
      uint32_t imm12  : 1;
      uint32_t imm10_5: 6;
      uint32_t rs2    : 5;
      uint32_t rs1    : 5;
      uint32_t funct3 : 3;
      uint32_t imm4_1 : 4;
      uint32_t imm11  : 1;
      uint32_t opcode : 7;
   };

   struct u_type_opcode {
      uint32_t imm31_12 : 20;
      uint32_t rd       : 5;
      uint32_t opcode   : 7;
   };

   struct j_type_opcode {
      uint32_t imm20   : 1;
      uint32_t imm10_1 : 10;
      uint32_t imm11   : 1;
      uint32_t imm19_12: 8;
      uint32_t rd      : 5;
      uint32_t opcode  : 7;
   };
} // namespace archon