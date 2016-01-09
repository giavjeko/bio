typedef struct Node Node;
typedef struct WaveletTree Node;
struct Node {
  Bitvector* bitvector;
  Node* left, right;
  char value;
}
