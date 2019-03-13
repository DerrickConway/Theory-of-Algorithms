// Derrick Conway, 2019
// The Secure Hash Alorithm, 256 bit version
// Link, https://ws680.nist.gov/publication/get_pdf.cfm?pub_id=910977

// The input output header file
#include <stdio.h>
// The use of fixed lenght integers.
#include <stdint.h>

void sha256();

int main(int argc, char *argv[]) {

  sha256();

  return 0;
}

void sha256(){

  // Message Schedule (Section 6.2)
  uint32_t w[64];
  //Working variables (Section 6.2)
  uint32_t a, b, c, d, e, f, g, h;
  // The hash value (Section 6.2)
  uint32_t H[8];
  // Two temporery variables (Section 6.2)
  uint32_t T1, T2;
 

}

