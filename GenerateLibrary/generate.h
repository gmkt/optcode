#include "../BaseLibrary/base.h"
#include "../BoundLibrary/bound.h"
#include <list>

//template<class T>
///*__declspec(dllexport) */bool gen_next_binomial_with_reps(T*, int, T);
list<RightPayload> step_matrices(const list<RightPayload>& matrices, strategy_step st, int d);
