#include "motor_states.h"

volatile bool motor_state_change_flag = false;

extern inline void motor_stop(); 
extern inline void test_gates_on();

extern inline void f1();
extern inline void f2();
extern inline void f3();

extern inline void b1();
extern inline void b2();
extern inline void b3();