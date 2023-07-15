#include <iostream>
#include <vector>

#include "padding/ANSI_X9_23.hpp"
#include "padding/ISO_IEC_7816_4.hpp"
#include "padding/PKCS_5_7.hpp"

#include "small_test.hpp"

int main() {
  smlts::test t;

  // ############# BLOCK CIPHER ###############3

  std::cout << "Padding ANSI_X9_23: \n";
  {
    size_t padding_block = 8;
    unsigned char subject1[] = {0xfd, 0xfd, 0xfd};
    unsigned char subject2[] = {
        0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd,
    };
    unsigned char subject3[] = {0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd};

    unsigned char validator1[] = {
        0xfd, 0xfd, 0xfd, 0x00, 0x00, 0x00, 0x00, 0x05,
    };
    unsigned char validator2[] = {
        0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0x01,
    };
    unsigned char validator3[] = {
        0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
    };

    Padding::ByteArray answer1 = Padding::ANSI_X9_23::Add(subject1, sizeof(subject1), padding_block);
    Padding::ByteArray backan1 = Padding::ANSI_X9_23::Remove(answer1.data(), answer1.size());
    t.byte_eq(validator1, (unsigned char *) answer1.data(), sizeof(validator1), "ANSI_X9_23 padding add test");
    t.byte_eq(subject1, (unsigned char *) backan1.data(), sizeof(subject1), "ANSI_X9_23 padding remove test");

    Padding::ByteArray answer2 = Padding::ANSI_X9_23::Add(subject2, sizeof(subject2), padding_block);
    Padding::ByteArray backan2 = Padding::ANSI_X9_23::Remove(answer2.data(), answer2.size());
    t.byte_eq(validator2, (unsigned char *) answer2.data(), sizeof(validator2), "ANSI_X9_23 padding add test");
    t.byte_eq(subject2, (unsigned char *) backan2.data(), sizeof(subject2), "ANSI_X9_23 padding remove test");

    Padding::ByteArray answer3 = Padding::ANSI_X9_23::Add(subject3, sizeof(subject3), padding_block);
    Padding::ByteArray backan3 = Padding::ANSI_X9_23::Remove(answer3.data(), answer3.size());
    t.byte_eq(validator3, (unsigned char *) answer3.data(), sizeof(validator3), "ANSI_X9_23 padding add test");
    t.byte_eq(subject3, (unsigned char *) backan3.data(), sizeof(subject3), "ANSI_X9_23 padding remove test");
  }

  std::cout << "PKCS_5_7: \n";
  {
    size_t padding_block = 8;
    unsigned char subject1[] = {0xfd, 0xfd, 0xfd};
    unsigned char subject2[] = {
        0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd,
    };
    unsigned char subject3[] = {0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd};

    unsigned char validator1[] = {
        0xfd, 0xfd, 0xfd, 0x05, 0x05, 0x05, 0x05, 0x05,
    };
    unsigned char validator2[] = {
        0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0x01,
    };
    unsigned char validator3[] = {
        0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
    };

    Padding::ByteArray answer1 = Padding::PKCS_5_7::Add(subject1, sizeof(subject1), padding_block);
    Padding::ByteArray backan1 = Padding::PKCS_5_7::Remove(answer1.data(), answer1.size());
    t.byte_eq(validator1, (unsigned char *) answer1.data(), sizeof(validator1), "PKCS_5_7 padding add test");
    t.byte_eq(subject1, (unsigned char *) backan1.data(), sizeof(subject1), "PKCS_5_7 padding remove test");

    Padding::ByteArray answer2 = Padding::PKCS_5_7::Add(subject2, sizeof(subject2), padding_block);
    Padding::ByteArray backan2 = Padding::PKCS_5_7::Remove(answer2.data(), answer2.size());
    t.byte_eq(validator2, (unsigned char *) answer2.data(), sizeof(validator2), "PKCS_5_7 padding add test");
    t.byte_eq(subject2, (unsigned char *) backan2.data(), sizeof(subject2), "PKCS_5_7 padding remove test");

    Padding::ByteArray answer3 = Padding::PKCS_5_7::Add(subject3, sizeof(subject3), padding_block);
    Padding::ByteArray backan3 = Padding::PKCS_5_7::Remove(answer3.data(), answer3.size());
    t.byte_eq(validator3, (unsigned char *) answer3.data(), sizeof(validator3), "PKCS_5_7 padding add test");
    t.byte_eq(subject3, (unsigned char *) backan3.data(), sizeof(subject3), "PKCS_5_7 padding remove test");
  }

  std::cout << "Padding ISO_IEC_7816_4: \n";
  {
    size_t padding_block = 8;
    unsigned char subject1[] = {0xfd, 0xfd, 0xfd};
    unsigned char subject2[] = {
        0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd,
    };
    unsigned char subject3[] = {0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd};

    unsigned char validator1[] = {
        0xfd, 0xfd, 0xfd, 0x80, 0x00, 0x00, 0x00, 0x00,
    };
    unsigned char validator2[] = {
        0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0x80,
    };
    unsigned char validator3[] = {
        0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    };

    Padding::ByteArray answer1 = Padding::ISO_IEC_7816_4::Add(subject1, sizeof(subject1), padding_block);
    Padding::ByteArray backan1 = Padding::ISO_IEC_7816_4::Remove(answer1.data(), answer1.size());
    t.byte_eq(validator1, (unsigned char *) answer1.data(), sizeof(validator1), "ISO_IEC_7816_4 padding add test");
    t.byte_eq(subject1, (unsigned char *) backan1.data(), sizeof(subject1), "ISO_IEC_7816_4 padding remove test");

    Padding::ByteArray answer2 = Padding::ISO_IEC_7816_4::Add(subject2, sizeof(subject2), padding_block);
    Padding::ByteArray backan2 = Padding::ISO_IEC_7816_4::Remove(answer2.data(), answer2.size());
    t.byte_eq(validator2, (unsigned char *) answer2.data(), sizeof(validator2), "ISO_IEC_7816_4 padding add test");
    t.byte_eq(subject2, (unsigned char *) backan2.data(), sizeof(subject2), "ISO_IEC_7816_4 padding remove test");

    Padding::ByteArray answer3 = Padding::ISO_IEC_7816_4::Add(subject3, sizeof(subject3), padding_block);
    Padding::ByteArray backan3 = Padding::ISO_IEC_7816_4::Remove(answer3.data(), answer3.size());
    t.byte_eq(validator3, (unsigned char *) answer3.data(), sizeof(validator3), "ISO_IEC_7816_4 padding add test");
    t.byte_eq(subject3, (unsigned char *) backan3.data(), sizeof(subject3), "ISO_IEC_7816_4 padding remove test");
  }

  return t.get_final_verdict();
}