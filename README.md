# BytePadding - A collection of different byte padding methods

![tests](https://github.com/mrdcvlsc/BytePadding/actions/workflows/tests.yml/badge.svg)

BytePadding is a small and simple repository that offers a collection of various byte padding methods.

Byte padding is a technique used to add additional bytes to a data stream, typically at the end, to ensure the data meets specific alignment requirements or fits a particular format.

-----------

## **Requirements**

- Requires C++17 so you need to compile it with the compilation flag `-std=c++17`.

## **Currently Available Padding Headers**

```c++
#include "padding/ANSI_X9_23.hpp"
#include "padding/PKCS_5_7.hpp"
#include "padding/ISO_IEC_7816_4.hpp"
```

## **Sample program:**

```c++
/*    sample.cpp    */
#include <iostream>
#include "padding/PKCS_5_7.hpp"

using namespace Padding;

int main()
{
    size_t padding_block = 8;

    unsigned char data1[] = { 0xfd, 0xfd, 0xfd, };

    unsigned char data2[] = {
      0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd,
    };

    unsigned char data3[] = {
      0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd,
    };

    ByteArray pad1 = PKCS_5_7::Add(subject1, sizeof(subject1), padding_block);
    ByteArray old1 = PKCS_5_7::Remove(pad1.data(), pad1.size());

    ByteArray pad2 = PKCS_5_7::Add(subject2, sizeof(subject2), padding_block);
    ByteArray old2 = PKCS_5_7::Remove(pad2.data(), pad2.size());

    ByteArray pad3 = PKCS_5_7::Add(subject3, sizeof(subject3), padding_block);
    ByteArray old3 = PKCS_5_7::Remove(pad3.data(), pad3.size());
}
```

**Encrypted Value:**

```c++
// data 1 padded result
0xfd, 0xfd, 0xfd, 0x05, 0x05, 0x05, 0x05, 0x05,

// data 2 padded result
0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0x01,

// data 3 padded result
0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd,
0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
```

**Byte Array Holder Class**

The `Padding::ByteArray` class is used to hold the result of the padding function and it offeres a small amount of method to handle different operations, and a destructor to automatically free the array after going out of scope.

If you want to **read** the array of a `Padding::ByteArray` object instance you can call the `ByteArray.data()` method, this method will return a `const unsigned char *` containing the array values.

If you want to manage the **Raw C style array** yourself, you can use the `ByteArray.size()` method to get the size of the array, then `ByteArray.detach()` method to get the `unsigned char *` pointer of the array, **this will detach the pointer inside the `ByteArray` so you will need to dellocate the detached pointer yourself!** `free()`/`delete []`.