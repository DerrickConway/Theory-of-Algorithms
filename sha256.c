// Derrick Conway, 2019
// The Secure Hash Alorithm, 256 bit version
// Link, https://ws680.nist.gov/publication/get_pdf.cfm?pub_id=910977

// The input output header file
#include <stdio.h>
// The use of fixed lenght integers.
#include <stdint.h>

void sha256();

// see Sections 4.1.2 for defentions
uint32_t sig0(uint32_t x);
uint32_t sig1(uint32_t x);

// See Section 3.2 for defintions
uint32_t rotr(uint32_t n, uint32_t x);
uint32_t shr(uint32_t n, uint32_t x);

int main(int argc, char *argv[]) {

  sha256();

  return 0;
}

void sha256(){

  // Message Schedule (Section 6.2)
  uint32_t w[64];
  //Working variables (Section 6.2)
  uint32_t a, b, c, d, e, f, g, h;
  // Two temporery variables (Section 6.2)
  uint32_t T1, T2;
 
  // The hash value (Section 6.2)
  // the values come from (Section 5.3.3)
  uint32_t H[8] = {
      0x6a09a667
    , 0xbb67ae85
    , 0x3c6ef372
    , 0xa54ff53a
    , 0x510e527f
    , 0x9b05688c
    , 0x1f83d9ad
    , 0x5be0cd19

  };
  
  // The current message block
  uint32_t M[16];
  
  // for looping
  int t;

  // from page 22 of the standered W[t] for 0 <= t <= 15.
  for (t =0; t < 16; t++)
    W[t] = M[t];
 
  // from page 22 W[t] =....
  for (t = 16; t < 64; t++)
    sig_1(W[-2]) + W[t-7] + sig_0(W[t-15]) + W[t-16];



}

// se Section 3.2 for defintions.
uint32_t rotr(uint32_t n, uint32_t x);{
  return (x >> n) | (x << (32 - n);

}
uint32_t shr(uint32_t n, uint32_t x);{
  return (x >>n);

}

uint32_t sig0(uint32_t x);{
  // See Section 3.2 and 4.1.2 for definitions.
  return (rotr(7, x) ^ rotr(18,x) ^ shr(3, x));

}

uint32_t sig1(uint32_t x);{
  // See Section 3.2 and 4.1.2 for defintions
  return (rotr(17, x) ^ rotr(19, x) ^ shr(10, x));


}


