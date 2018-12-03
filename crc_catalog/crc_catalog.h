///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2000 - 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef CRC_CATALOG_2018_10_13_H_
  #define CRC_CATALOG_2018_10_13_H_

  #include <cstddef>
  #include <cstdint>
  #include <limits>
  #include <type_traits>

  namespace crc { namespace catalog {

  namespace detail {

  // Helper templates for selecting an exact unsigned
  // integral type based on a given number of bits.

  template<const std::size_t NumberOfBits,
           typename EnableType = void>
  struct uint_type_helper
  {
  private:
    using exact_unsigned_type = std::uintmax_t;
  };

  template<const std::size_t NumberOfBits>
  struct uint_type_helper<NumberOfBits,
                          typename std::enable_if<(   (NumberOfBits >  0U)
                                                   && (NumberOfBits <= 8U))>::type>
  {
    using exact_unsigned_type = std::uint8_t;
  };

  template<const std::size_t NumberOfBits>
  struct uint_type_helper<NumberOfBits,
                          typename std::enable_if<(   (NumberOfBits >   8U)
                                                   && (NumberOfBits <= 16U))>::type>
  {
    using exact_unsigned_type = std::uint16_t;
  };

  template<const std::size_t NumberOfBits>
  struct uint_type_helper<NumberOfBits,
                          typename std::enable_if<(   (NumberOfBits >  16U)
                                                   && (NumberOfBits <= 32U))>::type>
  {
    using exact_unsigned_type = std::uint32_t;
  };

  template<const std::size_t NumberOfBits>
  struct uint_type_helper<NumberOfBits,
                          typename std::enable_if<(   (NumberOfBits >  32U)
                                                   && (NumberOfBits <= 64U))>::type>
  {
    using exact_unsigned_type = std::uint64_t;
  };

  template<const std::size_t NumberOfBits,
           typename UnsignedIntegralType = typename detail::uint_type_helper<NumberOfBits>::exact_unsigned_type>
  UnsignedIntegralType crc_reflect_template(UnsignedIntegralType data)
  {
    using value_type = UnsignedIntegralType;

    value_type reflected_result(0U);

    for(std::uint_fast8_t i = 0U; i < std::uint_fast8_t(NumberOfBits); ++i)
    {
       // Reflect the next LSB.
       const value_type next_reflected_bit =
         value_type(value_type(std::uint_fast8_t(data) & 0x01U) << (std::uint_fast8_t(NumberOfBits - 1U) - i));

       reflected_result |= next_reflected_bit;

       data >>= 1;
    }

    return reflected_result;
  }

  } // namespace crc::catalog::detail

  template<const std::size_t NumberOfBits,
           typename UnsignedIntegralType = typename detail::uint_type_helper<NumberOfBits>::exact_unsigned_type>
  UnsignedIntegralType crc_bitwise_template(const std::uint8_t*         message,
                                            const std::size_t           count,
                                            const UnsignedIntegralType& polynomial,
                                            const UnsignedIntegralType& initial_value,
                                            const UnsignedIntegralType& final_xor_value,
                                            const bool                  reflect_in,
                                            const bool                  reflect_out)
  {
    using value_type = UnsignedIntegralType;

    // The data_type is fixed to exactly 8-bits in width at the moment.
    using data_type = std::uint8_t;

    static_assert(std::numeric_limits<std::uint8_t>::digits == 8,
                  "Error: The data_type (at the moment) must have exactly 8 bits.");

    value_type crc =
      initial_value << (std::size_t(std::numeric_limits<value_type>::digits) - NumberOfBits);

    // Perform the polynomial division, one element at a time.
    for(std::size_t data_index = 0U; data_index < count; ++data_index)
    {
      // Obtain the next data element (and reflect it if necessary).
      const data_type next_data_element =
        ((reflect_in == false)
          ? message[data_index]
          : detail::crc_reflect_template<std::size_t(std::numeric_limits<data_type>::digits)>(message[data_index]));

      {
        const std::size_t left_shift_amount =
          std::size_t(  std::numeric_limits<value_type>::digits
                      - std::numeric_limits<data_type >::digits);

        crc ^= value_type(value_type(next_data_element) << left_shift_amount);
      }

      // Process the next data byte, one bit at a time.
      for(std::uint_fast8_t bit_index = 0U; bit_index < std::uint_fast8_t(std::numeric_limits<data_type>::digits); ++bit_index)
      {
        const bool high_bit_of_crc_is_set =
          (value_type(crc & value_type(std::uintmax_t(1ULL) << (std::numeric_limits<value_type>::digits - 1))) != 0U);

        crc <<= 1;

        if(high_bit_of_crc_is_set)
        {
          // Shift through the polynomial. Also left-justify the
          // polynomial within the width of value_type, if necessary.
          const std::size_t left_shift_amount =
            std::size_t(std::size_t(std::numeric_limits<value_type>::digits) - NumberOfBits);

          crc ^= value_type(polynomial << left_shift_amount);
        }
      }
    }

    // Downshift the result to compensate for a potential
    // left-justification of the polynomial in the loop above.
    {
      const std::size_t right_shift_amount =
        std::size_t(std::size_t(std::numeric_limits<value_type>::digits) - NumberOfBits);

      crc >>= right_shift_amount;
    }

    if(reflect_out == true)
    {
      // Reflect the output result if necessary.
      crc = detail::crc_reflect_template<NumberOfBits>(crc);
    }

    // Perform the final XOR on the result.
    crc ^= final_xor_value;

    return crc;
  }

  inline std::uint8_t  crc_crc03_gsm         (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template< 3U>(message, count, std::uint8_t (UINTMAX_C(0x0000000000000003)), std::uint8_t (UINTMAX_C(0x0000000000000000)), std::uint8_t (UINTMAX_C(0x0000000000000007)), false, false); } // check: 0x0000000000000004
  inline std::uint8_t  crc_crc03_rohc        (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template< 3U>(message, count, std::uint8_t (UINTMAX_C(0x0000000000000003)), std::uint8_t (UINTMAX_C(0x0000000000000007)), std::uint8_t (UINTMAX_C(0x0000000000000000)), true,  true ); } // check: 0x0000000000000006
  inline std::uint8_t  crc_crc04_interlaken  (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template< 4U>(message, count, std::uint8_t (UINTMAX_C(0x0000000000000003)), std::uint8_t (UINTMAX_C(0x000000000000000F)), std::uint8_t (UINTMAX_C(0x000000000000000F)), false, false); } // check: 0x000000000000000B
  inline std::uint8_t  crc_crc04_itu         (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template< 4U>(message, count, std::uint8_t (UINTMAX_C(0x0000000000000003)), std::uint8_t (UINTMAX_C(0x0000000000000000)), std::uint8_t (UINTMAX_C(0x0000000000000000)), true,  true ); } // check: 0x0000000000000007
  inline std::uint8_t  crc_crc05_epc         (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template< 5U>(message, count, std::uint8_t (UINTMAX_C(0x0000000000000009)), std::uint8_t (UINTMAX_C(0x0000000000000009)), std::uint8_t (UINTMAX_C(0x0000000000000000)), false, false); } // check: 0x0000000000000000
  inline std::uint8_t  crc_crc05_itu         (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template< 5U>(message, count, std::uint8_t (UINTMAX_C(0x0000000000000015)), std::uint8_t (UINTMAX_C(0x0000000000000000)), std::uint8_t (UINTMAX_C(0x0000000000000000)), true,  true ); } // check: 0x0000000000000007
  inline std::uint8_t  crc_crc05_usb         (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template< 5U>(message, count, std::uint8_t (UINTMAX_C(0x0000000000000005)), std::uint8_t (UINTMAX_C(0x000000000000001F)), std::uint8_t (UINTMAX_C(0x000000000000001F)), true,  true ); } // check: 0x0000000000000019
  inline std::uint8_t  crc_crc06_cdma2000_a  (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template< 6U>(message, count, std::uint8_t (UINTMAX_C(0x0000000000000027)), std::uint8_t (UINTMAX_C(0x000000000000003F)), std::uint8_t (UINTMAX_C(0x0000000000000000)), false, false); } // check: 0x000000000000000D
  inline std::uint8_t  crc_crc06_cdma2000_b  (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template< 6U>(message, count, std::uint8_t (UINTMAX_C(0x0000000000000007)), std::uint8_t (UINTMAX_C(0x000000000000003F)), std::uint8_t (UINTMAX_C(0x0000000000000000)), false, false); } // check: 0x000000000000003B
  inline std::uint8_t  crc_crc06_darc        (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template< 6U>(message, count, std::uint8_t (UINTMAX_C(0x0000000000000019)), std::uint8_t (UINTMAX_C(0x0000000000000000)), std::uint8_t (UINTMAX_C(0x0000000000000000)), true,  true ); } // check: 0x0000000000000026
  inline std::uint8_t  crc_crc06_gsm         (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template< 6U>(message, count, std::uint8_t (UINTMAX_C(0x000000000000002F)), std::uint8_t (UINTMAX_C(0x0000000000000000)), std::uint8_t (UINTMAX_C(0x000000000000003F)), false, false); } // check: 0x0000000000000013
  inline std::uint8_t  crc_crc06_itu         (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template< 6U>(message, count, std::uint8_t (UINTMAX_C(0x0000000000000003)), std::uint8_t (UINTMAX_C(0x0000000000000000)), std::uint8_t (UINTMAX_C(0x0000000000000000)), true,  true ); } // check: 0x0000000000000006
  inline std::uint8_t  crc_crc07             (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template< 7U>(message, count, std::uint8_t (UINTMAX_C(0x0000000000000009)), std::uint8_t (UINTMAX_C(0x0000000000000000)), std::uint8_t (UINTMAX_C(0x0000000000000000)), false, false); } // check: 0x0000000000000075
  inline std::uint8_t  crc_crc07_rohc        (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template< 7U>(message, count, std::uint8_t (UINTMAX_C(0x000000000000004F)), std::uint8_t (UINTMAX_C(0x000000000000007F)), std::uint8_t (UINTMAX_C(0x0000000000000000)), true,  true ); } // check: 0x0000000000000053
  inline std::uint8_t  crc_crc07_umts        (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template< 7U>(message, count, std::uint8_t (UINTMAX_C(0x0000000000000045)), std::uint8_t (UINTMAX_C(0x0000000000000000)), std::uint8_t (UINTMAX_C(0x0000000000000000)), false, false); } // check: 0x0000000000000061
  inline std::uint8_t  crc_crc08             (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template< 8U>(message, count, std::uint8_t (UINTMAX_C(0x0000000000000007)), std::uint8_t (UINTMAX_C(0x0000000000000000)), std::uint8_t (UINTMAX_C(0x0000000000000000)), false, false); } // check: 0x00000000000000F4
  inline std::uint8_t  crc_crc08_autosar     (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template< 8U>(message, count, std::uint8_t (UINTMAX_C(0x000000000000002F)), std::uint8_t (UINTMAX_C(0x00000000000000FF)), std::uint8_t (UINTMAX_C(0x00000000000000FF)), false, false); } // check: 0x00000000000000DF
  inline std::uint8_t  crc_crc08_bluetooth   (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template< 8U>(message, count, std::uint8_t (UINTMAX_C(0x00000000000000A7)), std::uint8_t (UINTMAX_C(0x0000000000000000)), std::uint8_t (UINTMAX_C(0x0000000000000000)), true,  true ); } // check: 0x0000000000000026
  inline std::uint8_t  crc_crc08_cdma2000    (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template< 8U>(message, count, std::uint8_t (UINTMAX_C(0x000000000000009B)), std::uint8_t (UINTMAX_C(0x00000000000000FF)), std::uint8_t (UINTMAX_C(0x0000000000000000)), false, false); } // check: 0x00000000000000DA
  inline std::uint8_t  crc_crc08_darc        (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template< 8U>(message, count, std::uint8_t (UINTMAX_C(0x0000000000000039)), std::uint8_t (UINTMAX_C(0x0000000000000000)), std::uint8_t (UINTMAX_C(0x0000000000000000)), true,  true ); } // check: 0x0000000000000015
  inline std::uint8_t  crc_crc08_dvb_s2      (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template< 8U>(message, count, std::uint8_t (UINTMAX_C(0x00000000000000D5)), std::uint8_t (UINTMAX_C(0x0000000000000000)), std::uint8_t (UINTMAX_C(0x0000000000000000)), false, false); } // check: 0x00000000000000BC
  inline std::uint8_t  crc_crc08_ebu         (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template< 8U>(message, count, std::uint8_t (UINTMAX_C(0x000000000000001D)), std::uint8_t (UINTMAX_C(0x00000000000000FF)), std::uint8_t (UINTMAX_C(0x0000000000000000)), true,  true ); } // check: 0x0000000000000097
  inline std::uint8_t  crc_crc08_gsm_a       (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template< 8U>(message, count, std::uint8_t (UINTMAX_C(0x000000000000001D)), std::uint8_t (UINTMAX_C(0x0000000000000000)), std::uint8_t (UINTMAX_C(0x0000000000000000)), false, false); } // check: 0x0000000000000037
  inline std::uint8_t  crc_crc08_gsm_b       (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template< 8U>(message, count, std::uint8_t (UINTMAX_C(0x0000000000000049)), std::uint8_t (UINTMAX_C(0x0000000000000000)), std::uint8_t (UINTMAX_C(0x00000000000000FF)), false, false); } // check: 0x0000000000000094
  inline std::uint8_t  crc_crc08_i_code      (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template< 8U>(message, count, std::uint8_t (UINTMAX_C(0x000000000000001D)), std::uint8_t (UINTMAX_C(0x00000000000000FD)), std::uint8_t (UINTMAX_C(0x0000000000000000)), false, false); } // check: 0x000000000000007E
  inline std::uint8_t  crc_crc08_itu         (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template< 8U>(message, count, std::uint8_t (UINTMAX_C(0x0000000000000007)), std::uint8_t (UINTMAX_C(0x0000000000000000)), std::uint8_t (UINTMAX_C(0x0000000000000055)), false, false); } // check: 0x00000000000000A1
  inline std::uint8_t  crc_crc08_lte         (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template< 8U>(message, count, std::uint8_t (UINTMAX_C(0x000000000000009B)), std::uint8_t (UINTMAX_C(0x0000000000000000)), std::uint8_t (UINTMAX_C(0x0000000000000000)), false, false); } // check: 0x00000000000000EA
  inline std::uint8_t  crc_crc08_maxim       (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template< 8U>(message, count, std::uint8_t (UINTMAX_C(0x0000000000000031)), std::uint8_t (UINTMAX_C(0x0000000000000000)), std::uint8_t (UINTMAX_C(0x0000000000000000)), true,  true ); } // check: 0x00000000000000A1
  inline std::uint8_t  crc_crc08_opensafety  (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template< 8U>(message, count, std::uint8_t (UINTMAX_C(0x000000000000002F)), std::uint8_t (UINTMAX_C(0x0000000000000000)), std::uint8_t (UINTMAX_C(0x0000000000000000)), false, false); } // check: 0x000000000000003E
  inline std::uint8_t  crc_crc08_rohc        (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template< 8U>(message, count, std::uint8_t (UINTMAX_C(0x0000000000000007)), std::uint8_t (UINTMAX_C(0x00000000000000FF)), std::uint8_t (UINTMAX_C(0x0000000000000000)), true,  true ); } // check: 0x00000000000000D0
  inline std::uint8_t  crc_crc08_sae_j1850   (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template< 8U>(message, count, std::uint8_t (UINTMAX_C(0x000000000000001D)), std::uint8_t (UINTMAX_C(0x00000000000000FF)), std::uint8_t (UINTMAX_C(0x00000000000000FF)), false, false); } // check: 0x000000000000004B
  inline std::uint8_t  crc_crc08_wcdma       (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template< 8U>(message, count, std::uint8_t (UINTMAX_C(0x000000000000009B)), std::uint8_t (UINTMAX_C(0x0000000000000000)), std::uint8_t (UINTMAX_C(0x0000000000000000)), true,  true ); } // check: 0x0000000000000025
  inline std::uint16_t crc_crc10             (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template<10U>(message, count, std::uint16_t(UINTMAX_C(0x0000000000000233)), std::uint16_t(UINTMAX_C(0x0000000000000000)), std::uint16_t(UINTMAX_C(0x0000000000000000)), false, false); } // check: 0x0000000000000199
  inline std::uint16_t crc_crc10_cdma2000    (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template<10U>(message, count, std::uint16_t(UINTMAX_C(0x00000000000003D9)), std::uint16_t(UINTMAX_C(0x00000000000003FF)), std::uint16_t(UINTMAX_C(0x0000000000000000)), false, false); } // check: 0x0000000000000233
  inline std::uint16_t crc_crc10_gsm         (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template<10U>(message, count, std::uint16_t(UINTMAX_C(0x0000000000000175)), std::uint16_t(UINTMAX_C(0x0000000000000000)), std::uint16_t(UINTMAX_C(0x00000000000003FF)), false, false); } // check: 0x000000000000012A
  inline std::uint16_t crc_crc11             (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template<11U>(message, count, std::uint16_t(UINTMAX_C(0x0000000000000385)), std::uint16_t(UINTMAX_C(0x000000000000001A)), std::uint16_t(UINTMAX_C(0x0000000000000000)), false, false); } // check: 0x00000000000005A3
  inline std::uint16_t crc_crc11_umts        (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template<11U>(message, count, std::uint16_t(UINTMAX_C(0x0000000000000307)), std::uint16_t(UINTMAX_C(0x0000000000000000)), std::uint16_t(UINTMAX_C(0x0000000000000000)), false, false); } // check: 0x0000000000000061
  inline std::uint16_t crc_crc12_cdma2000    (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template<12U>(message, count, std::uint16_t(UINTMAX_C(0x0000000000000F13)), std::uint16_t(UINTMAX_C(0x0000000000000FFF)), std::uint16_t(UINTMAX_C(0x0000000000000000)), false, false); } // check: 0x0000000000000D4D
  inline std::uint16_t crc_crc12_dect        (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template<12U>(message, count, std::uint16_t(UINTMAX_C(0x000000000000080F)), std::uint16_t(UINTMAX_C(0x0000000000000000)), std::uint16_t(UINTMAX_C(0x0000000000000000)), false, false); } // check: 0x0000000000000F5B
  inline std::uint16_t crc_crc12_gsm         (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template<12U>(message, count, std::uint16_t(UINTMAX_C(0x0000000000000D31)), std::uint16_t(UINTMAX_C(0x0000000000000000)), std::uint16_t(UINTMAX_C(0x0000000000000FFF)), false, false); } // check: 0x0000000000000B34
  inline std::uint16_t crc_crc12_umts        (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template<12U>(message, count, std::uint16_t(UINTMAX_C(0x000000000000080F)), std::uint16_t(UINTMAX_C(0x0000000000000000)), std::uint16_t(UINTMAX_C(0x0000000000000000)), false, true ); } // check: 0x0000000000000DAF
  inline std::uint16_t crc_crc13_bbc         (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template<13U>(message, count, std::uint16_t(UINTMAX_C(0x0000000000001CF5)), std::uint16_t(UINTMAX_C(0x0000000000000000)), std::uint16_t(UINTMAX_C(0x0000000000000000)), false, false); } // check: 0x00000000000004FA
  inline std::uint16_t crc_crc14_darc        (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template<14U>(message, count, std::uint16_t(UINTMAX_C(0x0000000000000805)), std::uint16_t(UINTMAX_C(0x0000000000000000)), std::uint16_t(UINTMAX_C(0x0000000000000000)), true,  true ); } // check: 0x000000000000082D
  inline std::uint16_t crc_crc14_gsm         (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template<14U>(message, count, std::uint16_t(UINTMAX_C(0x000000000000202D)), std::uint16_t(UINTMAX_C(0x0000000000000000)), std::uint16_t(UINTMAX_C(0x0000000000003FFF)), false, false); } // check: 0x00000000000030AE
  inline std::uint16_t crc_crc15             (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template<15U>(message, count, std::uint16_t(UINTMAX_C(0x0000000000004599)), std::uint16_t(UINTMAX_C(0x0000000000000000)), std::uint16_t(UINTMAX_C(0x0000000000000000)), false, false); } // check: 0x000000000000059E
  inline std::uint16_t crc_crc15_mpt1327     (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template<15U>(message, count, std::uint16_t(UINTMAX_C(0x0000000000006815)), std::uint16_t(UINTMAX_C(0x0000000000000000)), std::uint16_t(UINTMAX_C(0x0000000000000001)), false, false); } // check: 0x0000000000002566
  inline std::uint16_t crc_crc16_arc         (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template<16U>(message, count, std::uint16_t(UINTMAX_C(0x0000000000008005)), std::uint16_t(UINTMAX_C(0x0000000000000000)), std::uint16_t(UINTMAX_C(0x0000000000000000)), true,  true ); } // check: 0x000000000000BB3D
  inline std::uint16_t crc_crc16_aug_ccitt   (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template<16U>(message, count, std::uint16_t(UINTMAX_C(0x0000000000001021)), std::uint16_t(UINTMAX_C(0x0000000000001D0F)), std::uint16_t(UINTMAX_C(0x0000000000000000)), false, false); } // check: 0x000000000000E5CC
  inline std::uint16_t crc_crc16_buypass     (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template<16U>(message, count, std::uint16_t(UINTMAX_C(0x0000000000008005)), std::uint16_t(UINTMAX_C(0x0000000000000000)), std::uint16_t(UINTMAX_C(0x0000000000000000)), false, false); } // check: 0x000000000000FEE8
  inline std::uint16_t crc_crc16_ccitt_false (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template<16U>(message, count, std::uint16_t(UINTMAX_C(0x0000000000001021)), std::uint16_t(UINTMAX_C(0x000000000000FFFF)), std::uint16_t(UINTMAX_C(0x0000000000000000)), false, false); } // check: 0x00000000000029B1
  inline std::uint16_t crc_crc16_cdma2000    (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template<16U>(message, count, std::uint16_t(UINTMAX_C(0x000000000000C867)), std::uint16_t(UINTMAX_C(0x000000000000FFFF)), std::uint16_t(UINTMAX_C(0x0000000000000000)), false, false); } // check: 0x0000000000004C06
  inline std::uint16_t crc_crc16_cms         (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template<16U>(message, count, std::uint16_t(UINTMAX_C(0x0000000000008005)), std::uint16_t(UINTMAX_C(0x000000000000FFFF)), std::uint16_t(UINTMAX_C(0x0000000000000000)), false, false); } // check: 0x000000000000AEE7
  inline std::uint16_t crc_crc16_dds_110     (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template<16U>(message, count, std::uint16_t(UINTMAX_C(0x0000000000008005)), std::uint16_t(UINTMAX_C(0x000000000000800D)), std::uint16_t(UINTMAX_C(0x0000000000000000)), false, false); } // check: 0x0000000000009ECF
  inline std::uint16_t crc_crc16_dect_r      (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template<16U>(message, count, std::uint16_t(UINTMAX_C(0x0000000000000589)), std::uint16_t(UINTMAX_C(0x0000000000000000)), std::uint16_t(UINTMAX_C(0x0000000000000001)), false, false); } // check: 0x000000000000007E
  inline std::uint16_t crc_crc16_dect_x      (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template<16U>(message, count, std::uint16_t(UINTMAX_C(0x0000000000000589)), std::uint16_t(UINTMAX_C(0x0000000000000000)), std::uint16_t(UINTMAX_C(0x0000000000000000)), false, false); } // check: 0x000000000000007F
  inline std::uint16_t crc_crc16_dnp         (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template<16U>(message, count, std::uint16_t(UINTMAX_C(0x0000000000003D65)), std::uint16_t(UINTMAX_C(0x0000000000000000)), std::uint16_t(UINTMAX_C(0x000000000000FFFF)), true,  true ); } // check: 0x000000000000EA82
  inline std::uint16_t crc_crc16_en_13757    (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template<16U>(message, count, std::uint16_t(UINTMAX_C(0x0000000000003D65)), std::uint16_t(UINTMAX_C(0x0000000000000000)), std::uint16_t(UINTMAX_C(0x000000000000FFFF)), false, false); } // check: 0x000000000000C2B7
  inline std::uint16_t crc_crc16_genibus     (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template<16U>(message, count, std::uint16_t(UINTMAX_C(0x0000000000001021)), std::uint16_t(UINTMAX_C(0x000000000000FFFF)), std::uint16_t(UINTMAX_C(0x000000000000FFFF)), false, false); } // check: 0x000000000000D64E
  inline std::uint16_t crc_crc16_gsm         (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template<16U>(message, count, std::uint16_t(UINTMAX_C(0x0000000000001021)), std::uint16_t(UINTMAX_C(0x0000000000000000)), std::uint16_t(UINTMAX_C(0x000000000000FFFF)), false, false); } // check: 0x000000000000CE3C
  inline std::uint16_t crc_crc16_lj1200      (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template<16U>(message, count, std::uint16_t(UINTMAX_C(0x0000000000006F63)), std::uint16_t(UINTMAX_C(0x0000000000000000)), std::uint16_t(UINTMAX_C(0x0000000000000000)), false, false); } // check: 0x000000000000BDF4
  inline std::uint16_t crc_crc16_maxim       (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template<16U>(message, count, std::uint16_t(UINTMAX_C(0x0000000000008005)), std::uint16_t(UINTMAX_C(0x0000000000000000)), std::uint16_t(UINTMAX_C(0x000000000000FFFF)), true,  true ); } // check: 0x00000000000044C2
  inline std::uint16_t crc_crc16_mcrf4xx     (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template<16U>(message, count, std::uint16_t(UINTMAX_C(0x0000000000001021)), std::uint16_t(UINTMAX_C(0x000000000000FFFF)), std::uint16_t(UINTMAX_C(0x0000000000000000)), true,  true ); } // check: 0x0000000000006F91
  inline std::uint16_t crc_crc16_opensafety_a(const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template<16U>(message, count, std::uint16_t(UINTMAX_C(0x0000000000005935)), std::uint16_t(UINTMAX_C(0x0000000000000000)), std::uint16_t(UINTMAX_C(0x0000000000000000)), false, false); } // check: 0x0000000000005D38
  inline std::uint16_t crc_crc16_opensafety_b(const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template<16U>(message, count, std::uint16_t(UINTMAX_C(0x000000000000755B)), std::uint16_t(UINTMAX_C(0x0000000000000000)), std::uint16_t(UINTMAX_C(0x0000000000000000)), false, false); } // check: 0x00000000000020FE
  inline std::uint16_t crc_crc16_profibus    (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template<16U>(message, count, std::uint16_t(UINTMAX_C(0x0000000000001DCF)), std::uint16_t(UINTMAX_C(0x000000000000FFFF)), std::uint16_t(UINTMAX_C(0x000000000000FFFF)), false, false); } // check: 0x000000000000A819
  inline std::uint16_t crc_crc16_riello      (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template<16U>(message, count, std::uint16_t(UINTMAX_C(0x0000000000001021)), std::uint16_t(UINTMAX_C(0x000000000000B2AA)), std::uint16_t(UINTMAX_C(0x0000000000000000)), true,  true ); } // check: 0x00000000000063D0
  inline std::uint16_t crc_crc16_t10_dif     (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template<16U>(message, count, std::uint16_t(UINTMAX_C(0x0000000000008BB7)), std::uint16_t(UINTMAX_C(0x0000000000000000)), std::uint16_t(UINTMAX_C(0x0000000000000000)), false, false); } // check: 0x000000000000D0DB
  inline std::uint16_t crc_crc16_teledisk    (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template<16U>(message, count, std::uint16_t(UINTMAX_C(0x000000000000A097)), std::uint16_t(UINTMAX_C(0x0000000000000000)), std::uint16_t(UINTMAX_C(0x0000000000000000)), false, false); } // check: 0x0000000000000FB3
  inline std::uint16_t crc_crc16_tms37157    (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template<16U>(message, count, std::uint16_t(UINTMAX_C(0x0000000000001021)), std::uint16_t(UINTMAX_C(0x00000000000089EC)), std::uint16_t(UINTMAX_C(0x0000000000000000)), true,  true ); } // check: 0x00000000000026B1
  inline std::uint16_t crc_crc16_usb         (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template<16U>(message, count, std::uint16_t(UINTMAX_C(0x0000000000008005)), std::uint16_t(UINTMAX_C(0x000000000000FFFF)), std::uint16_t(UINTMAX_C(0x000000000000FFFF)), true,  true ); } // check: 0x000000000000B4C8
  inline std::uint16_t crc_crc16_a           (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template<16U>(message, count, std::uint16_t(UINTMAX_C(0x0000000000001021)), std::uint16_t(UINTMAX_C(0x000000000000C6C6)), std::uint16_t(UINTMAX_C(0x0000000000000000)), true,  true ); } // check: 0x000000000000BF05
  inline std::uint16_t crc_crc16_kermit      (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template<16U>(message, count, std::uint16_t(UINTMAX_C(0x0000000000001021)), std::uint16_t(UINTMAX_C(0x0000000000000000)), std::uint16_t(UINTMAX_C(0x0000000000000000)), true,  true ); } // check: 0x0000000000002189
  inline std::uint16_t crc_crc16_modbus      (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template<16U>(message, count, std::uint16_t(UINTMAX_C(0x0000000000008005)), std::uint16_t(UINTMAX_C(0x000000000000FFFF)), std::uint16_t(UINTMAX_C(0x0000000000000000)), true,  true ); } // check: 0x0000000000004B37
  inline std::uint16_t crc_crc16_x_25        (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template<16U>(message, count, std::uint16_t(UINTMAX_C(0x0000000000001021)), std::uint16_t(UINTMAX_C(0x000000000000FFFF)), std::uint16_t(UINTMAX_C(0x000000000000FFFF)), true,  true ); } // check: 0x000000000000906E
  inline std::uint16_t crc_crc16_xmodem      (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template<16U>(message, count, std::uint16_t(UINTMAX_C(0x0000000000001021)), std::uint16_t(UINTMAX_C(0x0000000000000000)), std::uint16_t(UINTMAX_C(0x0000000000000000)), false, false); } // check: 0x00000000000031C3
  inline std::uint32_t crc_crc17_can_fd      (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template<17U>(message, count, std::uint32_t(UINTMAX_C(0x000000000001685B)), std::uint32_t(UINTMAX_C(0x0000000000000000)), std::uint32_t(UINTMAX_C(0x0000000000000000)), false, false); } // check: 0x0000000000004F03
  inline std::uint32_t crc_crc21_can_fd      (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template<21U>(message, count, std::uint32_t(UINTMAX_C(0x0000000000102899)), std::uint32_t(UINTMAX_C(0x0000000000000000)), std::uint32_t(UINTMAX_C(0x0000000000000000)), false, false); } // check: 0x00000000000ED841
  inline std::uint32_t crc_crc24             (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template<24U>(message, count, std::uint32_t(UINTMAX_C(0x0000000000864CFB)), std::uint32_t(UINTMAX_C(0x0000000000B704CE)), std::uint32_t(UINTMAX_C(0x0000000000000000)), false, false); } // check: 0x000000000021CF02
  inline std::uint32_t crc_crc24_ble         (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template<24U>(message, count, std::uint32_t(UINTMAX_C(0x000000000000065B)), std::uint32_t(UINTMAX_C(0x0000000000555555)), std::uint32_t(UINTMAX_C(0x0000000000000000)), true,  true ); } // check: 0x0000000000C25A56
  inline std::uint32_t crc_crc24_flexray_a   (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template<24U>(message, count, std::uint32_t(UINTMAX_C(0x00000000005D6DCB)), std::uint32_t(UINTMAX_C(0x0000000000FEDCBA)), std::uint32_t(UINTMAX_C(0x0000000000000000)), false, false); } // check: 0x00000000007979BD
  inline std::uint32_t crc_crc24_flexray_b   (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template<24U>(message, count, std::uint32_t(UINTMAX_C(0x00000000005D6DCB)), std::uint32_t(UINTMAX_C(0x0000000000ABCDEF)), std::uint32_t(UINTMAX_C(0x0000000000000000)), false, false); } // check: 0x00000000001F23B8
  inline std::uint32_t crc_crc24_interlaken  (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template<24U>(message, count, std::uint32_t(UINTMAX_C(0x0000000000328B63)), std::uint32_t(UINTMAX_C(0x0000000000FFFFFF)), std::uint32_t(UINTMAX_C(0x0000000000FFFFFF)), false, false); } // check: 0x0000000000B4F3E6
  inline std::uint32_t crc_crc24_lte_a       (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template<24U>(message, count, std::uint32_t(UINTMAX_C(0x0000000000864CFB)), std::uint32_t(UINTMAX_C(0x0000000000000000)), std::uint32_t(UINTMAX_C(0x0000000000000000)), false, false); } // check: 0x0000000000CDE703
  inline std::uint32_t crc_crc24_lte_b       (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template<24U>(message, count, std::uint32_t(UINTMAX_C(0x0000000000800063)), std::uint32_t(UINTMAX_C(0x0000000000000000)), std::uint32_t(UINTMAX_C(0x0000000000000000)), false, false); } // check: 0x000000000023EF52
  inline std::uint32_t crc_crc30_cdma        (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template<30U>(message, count, std::uint32_t(UINTMAX_C(0x000000002030B9C7)), std::uint32_t(UINTMAX_C(0x000000003FFFFFFF)), std::uint32_t(UINTMAX_C(0x000000003FFFFFFF)), false, false); } // check: 0x0000000004C34ABF
  inline std::uint32_t crc_crc31_philips     (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template<31U>(message, count, std::uint32_t(UINTMAX_C(0x0000000004C11DB7)), std::uint32_t(UINTMAX_C(0x000000007FFFFFFF)), std::uint32_t(UINTMAX_C(0x000000007FFFFFFF)), false, false); } // check: 0x000000000CE9E46C
  inline std::uint32_t crc_crc32             (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template<32U>(message, count, std::uint32_t(UINTMAX_C(0x0000000004C11DB7)), std::uint32_t(UINTMAX_C(0x00000000FFFFFFFF)), std::uint32_t(UINTMAX_C(0x00000000FFFFFFFF)), true,  true ); } // check: 0x00000000CBF43926
  inline std::uint32_t crc_crc32_autosar     (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template<32U>(message, count, std::uint32_t(UINTMAX_C(0x00000000F4ACFB13)), std::uint32_t(UINTMAX_C(0x00000000FFFFFFFF)), std::uint32_t(UINTMAX_C(0x00000000FFFFFFFF)), true,  true ); } // check: 0x000000001697D06A
  inline std::uint32_t crc_crc32_bzip2       (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template<32U>(message, count, std::uint32_t(UINTMAX_C(0x0000000004C11DB7)), std::uint32_t(UINTMAX_C(0x00000000FFFFFFFF)), std::uint32_t(UINTMAX_C(0x00000000FFFFFFFF)), false, false); } // check: 0x00000000FC891918
  inline std::uint32_t crc_crc32_c           (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template<32U>(message, count, std::uint32_t(UINTMAX_C(0x000000001EDC6F41)), std::uint32_t(UINTMAX_C(0x00000000FFFFFFFF)), std::uint32_t(UINTMAX_C(0x00000000FFFFFFFF)), true,  true ); } // check: 0x00000000E3069283
  inline std::uint32_t crc_crc32_d           (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template<32U>(message, count, std::uint32_t(UINTMAX_C(0x00000000A833982B)), std::uint32_t(UINTMAX_C(0x00000000FFFFFFFF)), std::uint32_t(UINTMAX_C(0x00000000FFFFFFFF)), true,  true ); } // check: 0x0000000087315576
  inline std::uint32_t crc_crc32_mpeg_2      (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template<32U>(message, count, std::uint32_t(UINTMAX_C(0x0000000004C11DB7)), std::uint32_t(UINTMAX_C(0x00000000FFFFFFFF)), std::uint32_t(UINTMAX_C(0x0000000000000000)), false, false); } // check: 0x000000000376E6E7
  inline std::uint32_t crc_crc32_posix       (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template<32U>(message, count, std::uint32_t(UINTMAX_C(0x0000000004C11DB7)), std::uint32_t(UINTMAX_C(0x0000000000000000)), std::uint32_t(UINTMAX_C(0x00000000FFFFFFFF)), false, false); } // check: 0x00000000765E7680
  inline std::uint32_t crc_crc32_q           (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template<32U>(message, count, std::uint32_t(UINTMAX_C(0x00000000814141AB)), std::uint32_t(UINTMAX_C(0x0000000000000000)), std::uint32_t(UINTMAX_C(0x0000000000000000)), false, false); } // check: 0x000000003010BF7F
  inline std::uint32_t crc_crc32_jamcrc      (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template<32U>(message, count, std::uint32_t(UINTMAX_C(0x0000000004C11DB7)), std::uint32_t(UINTMAX_C(0x00000000FFFFFFFF)), std::uint32_t(UINTMAX_C(0x0000000000000000)), true,  true ); } // check: 0x00000000340BC6D9
  inline std::uint32_t crc_crc32_xfer        (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template<32U>(message, count, std::uint32_t(UINTMAX_C(0x00000000000000AF)), std::uint32_t(UINTMAX_C(0x0000000000000000)), std::uint32_t(UINTMAX_C(0x0000000000000000)), false, false); } // check: 0x00000000BD0BE338
  inline std::uint64_t crc_crc40_gsm         (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template<40U>(message, count, std::uint64_t(UINTMAX_C(0x0000000004820009)), std::uint64_t(UINTMAX_C(0x0000000000000000)), std::uint64_t(UINTMAX_C(0x000000FFFFFFFFFF)), false, false); } // check: 0x000000D4164FC646
  inline std::uint64_t crc_crc64             (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template<64U>(message, count, std::uint64_t(UINTMAX_C(0x42F0E1EBA9EA3693)), std::uint64_t(UINTMAX_C(0x0000000000000000)), std::uint64_t(UINTMAX_C(0x0000000000000000)), false, false); } // check: 0x6C40DF5F0B497347
  inline std::uint64_t crc_crc64_go_iso      (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template<64U>(message, count, std::uint64_t(UINTMAX_C(0x000000000000001B)), std::uint64_t(UINTMAX_C(0xFFFFFFFFFFFFFFFF)), std::uint64_t(UINTMAX_C(0xFFFFFFFFFFFFFFFF)), true,  true ); } // check: 0xB90956C775A41001
  inline std::uint64_t crc_crc64_we          (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template<64U>(message, count, std::uint64_t(UINTMAX_C(0x42F0E1EBA9EA3693)), std::uint64_t(UINTMAX_C(0xFFFFFFFFFFFFFFFF)), std::uint64_t(UINTMAX_C(0xFFFFFFFFFFFFFFFF)), false, false); } // check: 0x62EC59E3F1A4F00A
  inline std::uint64_t crc_crc64_xz          (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template<64U>(message, count, std::uint64_t(UINTMAX_C(0x42F0E1EBA9EA3693)), std::uint64_t(UINTMAX_C(0xFFFFFFFFFFFFFFFF)), std::uint64_t(UINTMAX_C(0xFFFFFFFFFFFFFFFF)), true,  true ); } // check: 0x995DC9BBDF1939FA
  inline std::uint64_t crc_crc64_jones_redis (const std::uint8_t* message, const std::size_t count) { return crc_bitwise_template<64U>(message, count, std::uint64_t(UINTMAX_C(0xAD93D23594C935A9)), std::uint64_t(UINTMAX_C(0x0000000000000000)), std::uint64_t(UINTMAX_C(0x0000000000000000)), true,  true ); } // check: 0xE9C6D914C4B8D9CA

  } } // namespace crc::catalog

#endif // CRC_CATALOG_2018_10_13_H_
