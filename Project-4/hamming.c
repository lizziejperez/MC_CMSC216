#define WORD_SIZE 16

int main() {

  int input = 138;	// Assume the input is in R3;
  int output = 0;   // Assume the output will return in R0;
  int position = 0;

  for (int bit = 1; bit < WORD_SIZE; bit <<= 1) {
    int parity = 0;
    for (int pos = 1; pos <= WORD_SIZE; pos++) 
      if ((pos & bit) && ((input >> (WORD_SIZE-pos)) & 1)) 
		  parity++;
    if (parity & 1)
      position += bit;
  }
  if (position) {
	position = WORD_SIZE - position;
	output = input ^ (1 << position);
  }
  
}