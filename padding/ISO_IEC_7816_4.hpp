#ifndef MRDCVLSC_BYTE_PADDING_ISO_IEC_7816_4_HPP
#define MRDCVLSC_BYTE_PADDING_ISO_IEC_7816_4_HPP

#include <cmath>
#include <iostream>
#include <vector>

#include "ByteArray.hpp"

/*
3 bytes: FDFDFD           --> FDFDFD8000000000
7 bytes: FDFDFDFDFDFDFD   --> FDFDFDFDFDFDFD80
8 bytes: FDFDFDFDFDFDFDFD --> FDFDFDFDFDFDFDFD8000000000000000
*/

namespace Padding {
  struct ISO_IEC_7816_4 {
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
      padded.set(length, 0x00, remaining_bytes);
      padded[length] = 0x80;

      return padded;
    }

    static ByteArray Remove(const unsigned char *src, size_t length) {
      size_t remove_size = 0;

      size_t index = length;
      while (!src[--index]) {
        remove_size++;
      }

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