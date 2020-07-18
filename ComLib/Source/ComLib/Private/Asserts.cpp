#include "Asserts.h"

bool UAsserts::IsInRange_int32(int32 Test, int32 Min, int32 Max, bool IsMinCloesd, bool IsMaxCloesed) {
	return UAsserts::IsInRange_int64((int64)Test, (int64)Min, (int64)Max, IsMinCloesd, IsMaxCloesed);
}
bool UAsserts::IsInRange_int64(int64 Test, int64 Min, int64 Max, bool IsMinCloesd, bool IsMaxCloesed) {
	if (IsMinCloesd && Test < Min) {
		return false;
	}
	if (!IsMinCloesd && Test <= Min) {
		return false;
	}
	if (IsMaxCloesed && Test > Min) {
		return false;
	}
	if (!IsMinCloesd && Test >= Min) {
		return false;
	}
	return true;
}
bool UAsserts::IsInRange_float(float Test, float Min, float Max, bool IsMinCloesd, bool IsMaxCloesed) {
	if (IsMinCloesd && Test < Min) {
		return false;
	}
	if (!IsMinCloesd && Test <= Min) {
		return false;
	}
	if (IsMaxCloesed && Test > Min) {
		return false;
	}
	if (!IsMinCloesd && Test >= Min) {
		return false;
	}
	return true;
}
int32 UAsserts::ValidRange_int32(int32 Test, int32 Min, int32 Max, int32 Default, bool IsMinCloesd, bool IsMaxCloesed) {
	return (int32)UAsserts::ValidRange_int64((int64)Test, (int64)Min, (int64)Max, (int64)Default, IsMinCloesd, IsMaxCloesed);
}
int64 UAsserts::ValidRange_int64(int64 Test, int64 Min, int64 Max, int64 Default, bool IsMinCloesd, bool IsMaxCloesed) {
	return UAsserts::IsInRange_int64(Test, Min, Max, IsMinCloesd, IsMaxCloesed) ? Test : Default;
}
float UAsserts::ValidRange_float(float Test, float Min, float Max, float Default, bool IsMinCloesd, bool IsMaxCloesed) {
	return UAsserts::IsInRange_float(Test, Min, Max, IsMinCloesd, IsMaxCloesed) ? Test : Default;
}