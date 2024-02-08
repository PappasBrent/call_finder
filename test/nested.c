#define C 1
#define B C
#define A B

#define Z() 0
#define Y() Z()
#define X() Y()

void g() {}

void f() { g(); }

#define G() g()
#define F() G()

int main(void) {
  A;
  B;
  C;
  X();
  Y();
  Z();

  f();
  g();
  F();
  F();
  F();
  return 0;
}
