#ifndef MRDCVLSC_BYTE_PADDING_BYTEARRAY_HPP
#define MRDCVLSC_BYTE_PADDING_BYTEARRAY_HPP

#include <cstring>
#include <iostream>

namespace Padding {
  class ByteArray {
    private:
    size_t length;
    unsigned char *array;

    public:

    const unsigned char *data() const {
      return array;
    }

    unsigned char *detach() {
      unsigned char* data = array;
      array = NULL;
      length = 0;

      return data;
    }

    void cpy(const unsigned char *src, size_t len) {
      std::memcpy(array, src, len);
    }

    void set(size_t start_index, unsigned char value, size_t length) {
      std::memset(&array[start_index], value, length);
    }

    unsigned char& operator[](size_t index) {
      return array[index];
    }

    const unsigned char& operator[](size_t index) const {
      return array[index];
    }

    bool reallocate(size_t length) {
      if (length == this->length) {
        return false;
      }

      if (!length) {
        return false;
      }

      unsigned char *new_array = new unsigned char[length];

      size_t copy_length = std::min(this->length, length);

      if (array) {
        std::memcpy(new_array, this->array, copy_length);
        delete[] array;
      }

      this->array = new_array;
      this->length = length;

      if (length > this->length) {
        std::memset(&new_array[copy_length], 0x00, length - copy_length);
      }

      return true;
    }

    size_t size() const {
      return length;
    }

    ByteArray(size_t length) {
      this->array = new unsigned char[length];
      this->length = length;
    }

    // copy constructor
    ByteArray(const ByteArray &original) {

      std::memcpy(this->array, original.array, original.length);
      this->length = original.length;
    }

    // move constructor
    ByteArray(ByteArray &&temporary) {

      if (&temporary != this) {
        this->array = temporary.array;
        this->length = temporary.length;

        temporary.array = NULL;
        temporary.length = 0;
      }
    }

    // copy assignment
    ByteArray &operator=(const ByteArray &original) {

      if (array) {
        delete[] array;
      }

      std::memcpy(this->array, original.array, original.length);
      this->length = original.length;

      return *this;
    }

    // move assignment
    ByteArray &operator=(ByteArray &&temporary) {
      if (&temporary != this) {
        if (array) {
          delete[] array;
        }

        this->array = temporary.array;
        this->length = temporary.length;

        temporary.array = NULL;
        temporary.length = 0;
      }

      return *this;
    }

    ~ByteArray() {
      if (array) {
        delete[] array;
      }

      length = 0;
    }
  };
} // namespace Padding

#endif