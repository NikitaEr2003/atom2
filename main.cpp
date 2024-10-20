#include <Windows.h>

#include <atomic>
#include <chrono>
#include <iostream>
#include <mutex>

#include "thread"
using namespace std;
class Data {
 public:
  Data(int a, double b) : m_a(a), m_b(b) {}
  int m_a;
  double m_b;
  mutex m;
};

void Swap(Data& obj1, Data& obj2) {
  if(&obj1 == &obj2)
   return;
  std::lock(obj1.m, obj2.m);
  lock_guard<mutex> lock1(obj1.m, adopt_lock);
  lock_guard<mutex> lock2(obj2.m, adopt_lock);
  std::swap(obj1.m_a, obj2.m_a);
  std::swap(obj1.m_b, obj2.m_b);

  this_thread::sleep_for(1s);
}

void Swap1(Data& obj1, Data& obj2) {
  if(&obj1 == &obj2)
   return;
  scoped_lock lock(obj1.m, obj2.m);
  std::swap(obj1.m_a, obj2.m_a);
  std::swap(obj1.m_b, obj2.m_b);
  this_thread::sleep_for(1s);
}

void Swap2(Data& obj1, Data& obj2) {
   if(&obj1 == &obj2)
   return;
  unique_lock<mutex> lock1(obj1.m, defer_lock);
  unique_lock<mutex> lock2(obj2.m, defer_lock);
  std::lock(lock1, lock2);

  std::swap(obj1.m_a, obj2.m_a);
  std::swap(obj1.m_b, obj2.m_b);

  this_thread::sleep_for(1s);
}

int main() {
  Data obj1(3, 4.1);
  Data obj2(7, 8.1);

  

  thread first(Swap, ref(obj1), ref(obj2));
  thread second(Swap, ref(obj1), ref(obj2));
  thread third(Swap1, ref(obj1), ref(obj2));
  thread fourth(Swap1, ref(obj1), ref(obj2));
  thread sixth(Swap2, ref(obj1), ref(obj2));
  thread seventh(Swap2, ref(obj1), ref(obj2));

  first.join();
  second.join();
  third.join();
  fourth.join();
  sixth.join();
  seventh.join();

  return 0;
}
