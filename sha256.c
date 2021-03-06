// Derrick Conway, 2019
// The Secure Hash Alorithm, 256 bit version
// Link, https://ws680.nist.gov/publication/get_pdf.cfm?pub_id=910977

// The input output header file
#include <stdio.h>
// The use of fixed lenght integers.
#include <stdint.h>

//https://codereview.stackexchange.com/questions/151049/endianness-conversion-in-c
// got this code from the webpage above.

#define REVERSE_UINT32(n) ((uint32_t) ((((n) & 0xFF) << 24) | \
                                           (((n) & 0xFF00) << 8) | \
                                           (((n) & 0xFF0000) >> 8) | \
                                           (((n) & 0xFF000000) >> 24)))

//#define REVERSE_UINT16(n) ((uint16_t) ((((n) & 0xFF) << 8) | \
                                             (((n) & 0xFF00) >> 8)))
 
#define REVERSE_UINT16 (*(uint16_t *)"\0\xff" < 0x64)

void sha256(FILE *msgf);

// Sections 4.1.2 for defintions
uint32_t sig0(uint32_t x);
uint32_t sig1(uint32_t x);

// Section 3.2 for defintion
uint32_t rotr(uint32_t n, uint32_t x);
uint32_t shr(uint32_t n, uint32_t x);

// section 4.1.2
uint32_t SIG0(uint32_t x);
uint32_t SIG1(uint32_t x);

// section 4.1.2
uint32_t Ch(uint32_t x, uint32_t y, uint32_t z);
uint32_t Maj(uint32_t x, uint32_t y, uint32_t z);

// message block
union msgblock{
  uint8_t   e[64];
  uint32_t  t[16];
  uint64_t  s[8];
};

enum status {READ, PAD0, PAD1, FINISH};


// retrieve next msg block
int nextmsgBlock(FILE *msgf, union msgblock *M, enum status *S, uint64_t *nobits);

// main method
int main(int argc, char *argv[]){

  // open the file given as  first cmd argument
  FILE* msgf;
  msgf = fopen(argv[1], "r");

  // call the function in main method to compile
  sha256(msgf);

  // close the file
  fclose(msgf);

  // must add a return method
  return 0;
}

// functions
void sha256(FILE *msgf){

  // current message block
  union msgblock M;
  // number of bits read from the file
  uint64_t nobits = 0;
  // message block status(Padding)
  enum status S = READ;

  // k constants. Section 4.2.2
  uint32_t K[] = {
  0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
  0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
  0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
  0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
  0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
  0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
  0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
  0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
  0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
  0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
  0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
  0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
  0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
  0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
  0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
  0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
  };

  // message schedule(section 6.2)
  uint32_t W[64];
  // working var (section 6.2)
  uint32_t a, b, c, d, e, f, g, h;
  // 2 temporary variables (section 6.2)
  uint32_t T1, T2;

  // hash value (section 6.2)
  // values from section 5.3.3
  uint32_t H[8] = {
     0x6a09e667, 0xbb67ae85
   , 0x3c6ef372, 0xa54ff53a
   , 0x510e527f, 0x9b05688c
   , 0x1f83d9ab, 0x5be0cd19

  };

  // current message block
  // not needed
  //uint32_t M[16] = {0, 0, 0, 0, 0, 0, 0, 0};
  
  // looping
  int i,t;

  // loop through message block as per page 22
  while(nextmsgBlock(msgf, &M, &S, &nobits)){
  
  // from page 22, W[t] = M[t] for 0 <= t <= 15
  for(t = 0; t< 16; t++)
    W[t] = M.t[t];
  
  // from page 22, W[t] = ...
  for(t = 16; t < 64; t++)
   W[t] =  sig1(W[t-2]) + W[t-7] + sig0(W[t-15]) + W[t-16];
  
  // initialize a, b, c, ... as per step 2
  a = H[0]; b =H[1]; c = H[2]; d = H[3];
  e = H[4]; f = H[5]; g = H[6]; h = H[7];

  // step 3
  for (t = 0; t < 64; t++){
    T1 = h + SIG1(e) + Ch(e, f ,g) + K[t] + W[t];
    T2 = SIG0(a) + Maj(a, b ,c);
    h = g;
    g = f;
    f = e;
    e = d + T1;
    d = c;
    c = b;
    b = a;
    a = T1 + T2;
  }
   // step 4
   H[0] = a + H[0]; H[1] = b + H[1];
   H[2] = c + H[2]; H[3] = d + H[3];
   H[4] = e + H[4]; H[5] = f + H[5];
   H[6] = g + H[6]; H[7] = h + H[7];

}
  
    printf("**************************************************\n");
    printf("SHA-256 convering from small endian to Big endian\n");
    printf("**************************************************\n\n");
// output of the file
  printf("-----------------------------Smail Endian------------------------------\n");
  printf("%08x %08x %08x %08x %08x %08x %08x %08x\n", H[0], H[1], H[2], H[3], H[4], H[5], H[6], H[7]);
  printf("\n");
if(REVERSE_UINT16){
     printf("%08x %08x %08x %08x %08x %08x %08x %08x\n\n",H[0], H[1],H[2],H[3], H[4], H[5], H[6],  H[7]);
      printf("*somthing went wrong*\n");
   }
// if(REVERSE_UINT16){
  // printf("%08x %08x %08x %08x %08x %08x %08x %08x\n\n",REVERSE_UINT16(H[0]),REVERSE_UINT16(H[1]),REVERSE_UINT16(H[2]),REVERSE_UINT16(H[3]),REVERSE_UINT16(H[4]),REVERSE_UINT16(H[5]),REVERSE_UINT16(H[6]),REVERSE_UINT16(H[7]));
 // }
else{
      printf("------------------------Converted to Big endian------------------------\n\n");
     printf("%08x %08x %08x %08x %08x %08x %08x %08x\n",REVERSE_UINT32(H[0]),REVERSE_UINT32(H[1]),REVERSE_UINT32(H[2]),
    REVERSE_UINT32(H[3]),REVERSE_UINT32(H[4]),REVERSE_UINT32(H[5]),REVERSE_UINT32(H[6]),REVERSE_UINT32(H[7]));
      printf("\n**********************************************************************\n");
 }

}
// rotate right
uint32_t rotr(uint32_t n, uint32_t x){
  return (x >> n) | (x << (32 - n));
}
// shift right
uint32_t shr(uint32_t n, uint32_t x){
  return (x >> n);
}

uint32_t sig0(uint32_t x){
  // sections 3.1 and  4.1.2 for definitions
  return (rotr(7, x) ^ rotr(10, x) ^ shr(3, x));
}

uint32_t sig1(uint32_t x){
  return (rotr(17, x) ^ rotr(19, x) ^ shr(10,x ));
}


uint32_t SIG0(uint32_t x){
  return (rotr(2, x) ^ rotr(13, x) ^ rotr(22, x));
}

uint32_t SIG1(uint32_t x){
  return (rotr(6, x) ^ rotr(11, x) ^ rotr(25, x));
}

// choose
uint32_t Ch(uint32_t x, uint32_t y, uint32_t z){
  return ((x & y) ^ ((!x) & z));
}
// Majority
uint32_t Maj(uint32_t x, uint32_t y, uint32_t z){
  return ((x & y) ^ (x & z) ^ (y & z));
}

int nextmsgBlock(FILE *msgf, union msgblock *M, enum status *S, uint64_t *nobits){
  // for looping
  int i;
  // number of bytes from fread
  uint64_t nobytes;

  // if we have finished all msgblocks, S should FINISH
  if(*S == FINISH){
    return 0;
  }
  
  // otherwise check if we need another block full of padding
  if (*S == PAD0 || *S == PAD1){
      // set first 56 bytes to 0 bits
      for (i = 0; i < 56; i++){
        M->e[i] = 0x00;
      }
      
      // set last 64 bits to the number of bits in the file(should be big endian)
      M->s[7] = *nobits;
      // tell S we are finished
      *S = FINISH;
       
      if (*S == PAD1){
       M->e[0] = 0x80;
      // keep the loop in sha256 for one more iteration
       return 1;
      }
  }
    // get down here we haven't finished reading the file(S == READ)
    nobytes = fread(M->e, 1, 64, msgf);
    
    // Kepp track of the number of bytes we have read
    *nobits = *nobits + (nobytes * 8);

    // if less than 56 bytes is read, all padding can be put in this block
    if (nobytes < 56) {
      // adding 1 bit as standard
      //printf("I found a block with less than 55 bytes\n");
      M->e[nobytes] = 0x80;
     
      // add 0 until last 64
      while (nobytes < 56) {
        nobytes = nobytes + 1;
        // set bytes to zero
        M->e[nobytes] = 0x00;
      }
      
      // append the file size in bits as an unsigned 64 bit int
      M->s[7] = *nobits;
      // S is finished
      *S = FINISH;
    // otherwise, check id can put some padding in this block
    } else if(nobytes < 64){
      // tell S we need another block with padding but no one bit
      *S = PAD0;
      // put one bit into the current block
      M->e[nobytes] = 0x80;
      // pad the rest with 0 bits
      while (nobytes < 64){
        nobytes = nobytes + 1;
        M->e[nobytes] = 0x00;
      }
    // check if we're at the end of the file  
    } else if (feof(msgf)){
      // tell s we need another msg block with all the padding
      *S = PAD1;
 uint32_t sig0(uint32_t x);
uint32_t sig1(uint32_t x);

   }

    // if we get down here, return 1 so so function is called again
    return 1;
  }

