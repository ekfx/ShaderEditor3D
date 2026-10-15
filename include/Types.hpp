#pragma once

#include <cstdint>
#include <cstddef>

template <size_t numbers_of_bits>
struct Bit
{
  static_assert((numbers_of_bits % 2) == 0, "NUMBERS_OF_BITS_MUST_BE_FROM_2_BASE");

  typedef std::uint64_t memory_filler;
  static constexpr int single_memory_number_of_bits = 64;

  static constexpr int bit_array_size = numbers_of_bits / single_memory_number_of_bits;
  memory_filler data[bit_array_size]{0};

  // Constructor
  Bit(const bool value = false) noexcept
  {
    if (value)
    {
      for (int i = 0; i < bit_array_size; i++)
      {
        data[i] = ~data[i];
      }
    }
  }

  std::uint64_t &operator[](const size_t &index_t) noexcept
  {
    if (index_t < numbers_of_bits)
    {
      return *(data + (index_t / single_memory_number_of_bits));
    }
    else
    {
      return *(data + 0);
    }
  }

  size_t size() const noexcept
  {
    return numbers_of_bits;
  }

  bool isTrue(const size_t &index) noexcept
  {
    size_t bit_target = index % single_memory_number_of_bits;
    auto &target = operator[](index);

    bool result = (target & (1ULL << bit_target));
    return result;
  }

  void setBit(const size_t &index, const bool &value) noexcept
  {
    size_t bit_target = index % single_memory_number_of_bits;
    memory_filler &target = operator[](index);

    if (value)
    {
      (target |= (1ULL << bit_target));
    }
    else
    {
      (target &= ~(1ULL << bit_target));
      /*
              Cria uma mascara com 1 bit ativado, com ~ então inverte,
              deixando positivos falso, e falsos positivo:
              ~0000100 = 1111011
              e então atribui a variavel apenas os bits que forem positivos
              na mascara AND na variavel:
              target = 1111111
              mask = 1111011
              target &= mask
              1111111
              1111011
                      ^ uma delas é falso, logo mantenha falso
              target = 1111011
      */
    }
  }
};

/*
        Bitwise:
                * Lembre-se: Usar masks (a << b) é a mesma coisa que uma variável criada
                * com valor (a << b).

        int a = 0101;
        int b = 1011;

        Operadores:
                AND: & -> retorna se os bits forem positivos nas duas variaveis: if ((a & b) != 0) {..}
                        0101 & 1011 = 0001

                OR: | -> retorna se um dos bits forem ativos: if (a | b) {..}
                        0101 | 1011 = 1111 -> as posicoes estão ativas em uma das variaveis

                XOR: ^ -> retorna se os bits forem diferentes: if (a ^ b) {..}
                        0101 ^ 1011 = 1110 -> diferentes se tornam true e iguais false

                NOT: ~ -> inverte todos os bits: b = ~a; b == 1010

                << -> desloca X casas para esquerda: b = (1 << 10); b == 10000000000
                >> -> desloca X casas para direita: b = (1 >> 10); b == 0000000000
                &= -> atribui apenas bits positivos: a &= b; a == 0001
                |= -> atribui bits de outra variavel: a |= b; a == 1111
                ^= -> atribui bits que forem diferentes como 1: a ^= b; a == 1110
                <<= -> atribui deslocamento para esquerda.
                >>= -> atribui deslocamento para direita.

*/
