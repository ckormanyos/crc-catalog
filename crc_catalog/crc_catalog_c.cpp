///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2000 - 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <crc_catalog.h>
#include <crc_catalog_c.h>

extern "C" uint8_t  crc_crc03_gsm         (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc03_gsm         (message, count); }
extern "C" uint8_t  crc_crc03_rohc        (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc03_rohc        (message, count); }
extern "C" uint8_t  crc_crc04_interlaken  (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc04_interlaken  (message, count); }
extern "C" uint8_t  crc_crc04_itu         (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc04_itu         (message, count); }
extern "C" uint8_t  crc_crc05_epc         (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc05_epc         (message, count); }
extern "C" uint8_t  crc_crc05_itu         (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc05_itu         (message, count); }
extern "C" uint8_t  crc_crc05_usb         (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc05_usb         (message, count); }
extern "C" uint8_t  crc_crc06_cdma2000_a  (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc06_cdma2000_a  (message, count); }
extern "C" uint8_t  crc_crc06_cdma2000_b  (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc06_cdma2000_b  (message, count); }
extern "C" uint8_t  crc_crc06_darc        (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc06_darc        (message, count); }
extern "C" uint8_t  crc_crc06_gsm         (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc06_gsm         (message, count); }
extern "C" uint8_t  crc_crc06_itu         (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc06_itu         (message, count); }
extern "C" uint8_t  crc_crc07             (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc07             (message, count); }
extern "C" uint8_t  crc_crc07_rohc        (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc07_rohc        (message, count); }
extern "C" uint8_t  crc_crc07_umts        (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc07_umts        (message, count); }
extern "C" uint8_t  crc_crc08             (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc08             (message, count); }
extern "C" uint8_t  crc_crc08_autosar     (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc08_autosar     (message, count); }
extern "C" uint8_t  crc_crc08_bluetooth   (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc08_bluetooth   (message, count); }
extern "C" uint8_t  crc_crc08_cdma2000    (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc08_cdma2000    (message, count); }
extern "C" uint8_t  crc_crc08_darc        (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc08_darc        (message, count); }
extern "C" uint8_t  crc_crc08_dvb_s2      (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc08_dvb_s2      (message, count); }
extern "C" uint8_t  crc_crc08_ebu         (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc08_ebu         (message, count); }
extern "C" uint8_t  crc_crc08_gsm_a       (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc08_gsm_a       (message, count); }
extern "C" uint8_t  crc_crc08_gsm_b       (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc08_gsm_b       (message, count); }
extern "C" uint8_t  crc_crc08_i_code      (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc08_i_code      (message, count); }
extern "C" uint8_t  crc_crc08_itu         (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc08_itu         (message, count); }
extern "C" uint8_t  crc_crc08_lte         (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc08_lte         (message, count); }
extern "C" uint8_t  crc_crc08_maxim       (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc08_maxim       (message, count); }
extern "C" uint8_t  crc_crc08_opensafety  (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc08_opensafety  (message, count); }
extern "C" uint8_t  crc_crc08_rohc        (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc08_rohc        (message, count); }
extern "C" uint8_t  crc_crc08_sae_j1850   (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc08_sae_j1850   (message, count); }
extern "C" uint8_t  crc_crc08_wcdma       (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc08_wcdma       (message, count); }
extern "C" uint16_t crc_crc10             (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc10             (message, count); }
extern "C" uint16_t crc_crc10_cdma2000    (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc10_cdma2000    (message, count); }
extern "C" uint16_t crc_crc10_gsm         (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc10_gsm         (message, count); }
extern "C" uint16_t crc_crc11             (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc11             (message, count); }
extern "C" uint16_t crc_crc11_umts        (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc11_umts        (message, count); }
extern "C" uint16_t crc_crc12_cdma2000    (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc12_cdma2000    (message, count); }
extern "C" uint16_t crc_crc12_dect        (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc12_dect        (message, count); }
extern "C" uint16_t crc_crc12_gsm         (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc12_gsm         (message, count); }
extern "C" uint16_t crc_crc12_umts        (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc12_umts        (message, count); }
extern "C" uint16_t crc_crc13_bbc         (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc13_bbc         (message, count); }
extern "C" uint16_t crc_crc14_darc        (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc14_darc        (message, count); }
extern "C" uint16_t crc_crc14_gsm         (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc14_gsm         (message, count); }
extern "C" uint16_t crc_crc15             (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc15             (message, count); }
extern "C" uint16_t crc_crc15_mpt1327     (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc15_mpt1327     (message, count); }
extern "C" uint16_t crc_crc16_arc         (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc16_arc         (message, count); }
extern "C" uint16_t crc_crc16_aug_ccitt   (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc16_aug_ccitt   (message, count); }
extern "C" uint16_t crc_crc16_buypass     (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc16_buypass     (message, count); }
extern "C" uint16_t crc_crc16_ccitt_false (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc16_ccitt_false (message, count); }
extern "C" uint16_t crc_crc16_cdma2000    (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc16_cdma2000    (message, count); }
extern "C" uint16_t crc_crc16_cms         (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc16_cms         (message, count); }
extern "C" uint16_t crc_crc16_dds_110     (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc16_dds_110     (message, count); }
extern "C" uint16_t crc_crc16_dect_r      (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc16_dect_r      (message, count); }
extern "C" uint16_t crc_crc16_dect_x      (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc16_dect_x      (message, count); }
extern "C" uint16_t crc_crc16_dnp         (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc16_dnp         (message, count); }
extern "C" uint16_t crc_crc16_en_13757    (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc16_en_13757    (message, count); }
extern "C" uint16_t crc_crc16_genibus     (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc16_genibus     (message, count); }
extern "C" uint16_t crc_crc16_gsm         (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc16_gsm         (message, count); }
extern "C" uint16_t crc_crc16_lj1200      (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc16_lj1200      (message, count); }
extern "C" uint16_t crc_crc16_maxim       (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc16_maxim       (message, count); }
extern "C" uint16_t crc_crc16_mcrf4xx     (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc16_mcrf4xx     (message, count); }
extern "C" uint16_t crc_crc16_opensafety_a(const uint8_t* message, const size_t count) { return crc::catalog::crc_crc16_opensafety_a(message, count); }
extern "C" uint16_t crc_crc16_opensafety_b(const uint8_t* message, const size_t count) { return crc::catalog::crc_crc16_opensafety_b(message, count); }
extern "C" uint16_t crc_crc16_profibus    (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc16_profibus    (message, count); }
extern "C" uint16_t crc_crc16_riello      (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc16_riello      (message, count); }
extern "C" uint16_t crc_crc16_t10_dif     (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc16_t10_dif     (message, count); }
extern "C" uint16_t crc_crc16_teledisk    (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc16_teledisk    (message, count); }
extern "C" uint16_t crc_crc16_tms37157    (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc16_tms37157    (message, count); }
extern "C" uint16_t crc_crc16_usb         (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc16_usb         (message, count); }
extern "C" uint16_t crc_crc16_a           (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc16_a           (message, count); }
extern "C" uint16_t crc_crc16_kermit      (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc16_kermit      (message, count); }
extern "C" uint16_t crc_crc16_modbus      (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc16_modbus      (message, count); }
extern "C" uint16_t crc_crc16_x_25        (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc16_x_25        (message, count); }
extern "C" uint16_t crc_crc16_xmodem      (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc16_xmodem      (message, count); }
extern "C" uint32_t crc_crc17_can_fd      (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc17_can_fd      (message, count); }
extern "C" uint32_t crc_crc21_can_fd      (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc21_can_fd      (message, count); }
extern "C" uint32_t crc_crc24             (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc24             (message, count); }
extern "C" uint32_t crc_crc24_ble         (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc24_ble         (message, count); }
extern "C" uint32_t crc_crc24_flexray_a   (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc24_flexray_a   (message, count); }
extern "C" uint32_t crc_crc24_flexray_b   (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc24_flexray_b   (message, count); }
extern "C" uint32_t crc_crc24_interlaken  (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc24_interlaken  (message, count); }
extern "C" uint32_t crc_crc24_lte_a       (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc24_lte_a       (message, count); }
extern "C" uint32_t crc_crc24_lte_b       (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc24_lte_b       (message, count); }
extern "C" uint32_t crc_crc30_cdma        (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc30_cdma        (message, count); }
extern "C" uint32_t crc_crc31_philips     (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc31_philips     (message, count); }
extern "C" uint32_t crc_crc32             (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc32             (message, count); }
extern "C" uint32_t crc_crc32_autosar     (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc32_autosar     (message, count); }
extern "C" uint32_t crc_crc32_bzip2       (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc32_bzip2       (message, count); }
extern "C" uint32_t crc_crc32_c           (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc32_c           (message, count); }
extern "C" uint32_t crc_crc32_d           (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc32_d           (message, count); }
extern "C" uint32_t crc_crc32_mpeg_2      (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc32_mpeg_2      (message, count); }
extern "C" uint32_t crc_crc32_posix       (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc32_posix       (message, count); }
extern "C" uint32_t crc_crc32_q           (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc32_q           (message, count); }
extern "C" uint32_t crc_crc32_jamcrc      (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc32_jamcrc      (message, count); }
extern "C" uint32_t crc_crc32_xfer        (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc32_xfer        (message, count); }
extern "C" uint64_t crc_crc40_gsm         (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc40_gsm         (message, count); }
extern "C" uint64_t crc_crc64             (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc64             (message, count); }
extern "C" uint64_t crc_crc64_go_iso      (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc64_go_iso      (message, count); }
extern "C" uint64_t crc_crc64_we          (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc64_we          (message, count); }
extern "C" uint64_t crc_crc64_xz          (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc64_xz          (message, count); }
extern "C" uint64_t crc_crc64_jones_redis (const uint8_t* message, const size_t count) { return crc::catalog::crc_crc64_jones_redis (message, count); }
