# crc-catalog

crc-catalog implements numerous CRCs using a bitwise algorithm implemented as a single C++ template. This can be useful for verifying existing or new CRC algorithms. Well-known CRCs are implemented as specific functions with intuitive names. There are function bindings for both the C++ as well as the C language.

Using crc-catalog is straightforward. For instance, let's calculate the standard check of CRC16/CCITT-FALSE

#include <array>
#include <iomanip>
#include <iostream>

#include <crc_catalog_c.h>

int main()
{
  const std::array<std::uint8_t, 9U> crc_test_data =
  {{
    0x31U, 0x32U, 0x33U, 0x34U, 0x35U, 0x36U, 0x37U, 0x38U, 0x39U
  }};

  const std::uint16_t crc_result =
    crc_crc16_ccitt_false(crc_test_data.data(), crc_test_data.size());

  const bool crc_result_is_ok = (crc_result == UINT16_C(0x29B1));

  std::cout << "crc_result_is_ok: " << std::boolalpha << crc_result_is_ok << std::endl;
}
