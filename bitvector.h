typedef char Bit;
typedef unsigned long long Word;
typedef struct Bitvector Bitvector;
struct Bitvector {
  Word* data;
  int length;
};

int bitvector_get_word_length();
Bitvector* bitvector_construct(int length);
void bitvector_push(Bitvector* bitvector, Bit bit);
