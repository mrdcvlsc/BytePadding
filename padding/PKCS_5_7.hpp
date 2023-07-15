#ifndef MRDCVLSC_BYTE_PADDING_PKCS_5_7_HPP
#define MRDCVLSC_BYTE_PADDING_PKCS_5_7_HPP

#include <cmath>
#include <iostream>
#include <vector>

#include "ByteArray.hpp"

/*
3 bytes: FDFDFD           --> FDFDFD0505050505
7 bytes: FDFDFDFDFDFDFD   --> FDFDFDFDFDFDFD01
8 bytes: FDFDFDFDFDFDFDFD --> FDFDFDFDFDFDFDFD0808080808080808
*/

namespace Padding {
  struct PKCS_5_7 {
    static ByteArray Add(const unsigned char *src, size_t length, size_t BLOCK_SIZE) {
      if (length > BLOCK_SIZE) {
        return NULL;
      }

      int remaining_bytes = BLOCK_SIZE - length;
      constexpr int max_val = (sizeof(unsigned char) << __CHAR_BIT__) - 1;
      if (remaining_bytes > max_val) {
        return NULL;
      }

      size_t padded_size = BLOCK_SIZE;

      if (length == BLOCK_SIZE) {
        padded_size += BLOCK_SIZE;
        remaining_bytes += BLOCK_SIZE;
      }

      ByteArray padded(padded_size);

      padded.cpy(src, length);
      padded.set(length, remaining_bytes, remaining_bytes);

      return padded;
    }

    static ByteArray Remove(const unsigned char *src, size_t length) {
      size_t remove_size = src[length - 1];

      if (remove_size >= length) {
        return NULL;
      }

      ByteArray nopadding(length - remove_size);
      nopadding.cpy(src, length - remove_size);

      return nopadding;
    }
  };
} // namespace Padding

#endif