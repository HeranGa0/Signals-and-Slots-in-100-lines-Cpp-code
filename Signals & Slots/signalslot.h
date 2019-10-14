#include<iostream>
#include<map>
#include <functional>
#include<string>
#include<type_traits>
#include<tuple>
#pragma once
using namespace std;
class Object;
using omfptr = void(Object::*)();

class MPointer
{
public:
	virtual void sendback(Object* optr) = 0;
	virtual omfptr get_mfptr() = 0;
	bool operator< (const MPointer& rhs) const
	{
		return true;
	}
};

class DPointer :public MPointer
{
public:
	DPointer(void(Object::*mfptr)()) :_mfptr(mfptr) {}
	void(Object::*_mfptr)();
	virtual void sendback(Object* optr)override
	{
		(optr->*_mfptr)();		
	}

	virtual omfptr get_mfptr() override
	{
		return omfptr(_mfptr);
	}
};

template<int ...>
struct seq { };

template<int N, int ...S>
struct gens : gens<N - 1, N - 1, S...> { };

template<int ...S>
struct gens<0, S...> {
	typedef seq<S...> type;
};

template<int ...S, typename T,typename... Types>
void callFunc(seq<S...>, const T&tuple, MPointer* mptr, Object* optr, std::tuple<Types...> &ty) {
	auto mfptr = mptr->get_mfptr();
	auto cast_omfptr = (void (Object::*)(Types...))mfptr;
	(optr->*cast_omfptr)(std::get<S>(tuple) ...);
}

template<typename T, typename... Types>
void delayed_dispatch(const T& tup, MPointer* mptr, Object* optr, std::tuple<Types...> &ty) {
	callFunc(typename gens<std::tuple_size<T>::value >::type(), tup, mptr, optr,ty);
}

std::map<std::pair<std::pair<std::string, MPointer*>, Object*>, std::pair<std::pair<std::string, MPointer*>, Object*>> _map;

#define connect(obj_ptr1,omfunc1,obj_ptr2,omfunc2)\
do{\
auto mfptr1=omfunc1;\
auto mfptr2=omfunc2;\
auto cast_mid_mfptr1=(void (std::remove_reference<decltype(*obj_ptr2)>::type ::*)())(mfptr1);\
auto cast_mfptr1=omfptr(cast_mid_mfptr1);\
auto cast_mid_mfptr2=(void (std::remove_reference<decltype(*obj_ptr2)>::type ::*)())(mfptr2);\
auto cast_mfptr2=omfptr(cast_mid_mfptr2);\
auto m1=new DPointer(cast_mfptr1);\
auto m2=new DPointer(cast_mfptr2);\
_map.insert(make_pair(std::make_pair(std::make_pair(#omfunc1,m1),obj_ptr1),std::make_pair(std::make_pair(#omfunc2,m2),obj_ptr2)));}\
while(0);

#define emit(func)\
do{\
func();\
for(auto _outPair:_map){\
std::size_t pos=_outPair.first.first.first.rfind("::");\
std::string funcName=_outPair.first.first.first.substr(pos+2);\
if((funcName==#func)&&(_outPair.first.second==this)){\
_outPair.second.first.second->sendback(_outPair.second.second);}}}\
while(0);
auto t = std::make_tuple(10, 20);

#define emitWithParam(func,signalArgs,slotsArgs)\
do{\
func signalArgs ;\
auto tuple = std::make_tuple slotsArgs ;\
for(auto _outPair:_map){\
std::size_t pos=_outPair.first.first.first.rfind("::");\
std::string funcName=_outPair.first.first.first.substr(pos+2);\
if((funcName==#func)&&(_outPair.first.second==this)){\
delayed_dispatch(tuple,_outPair.second.first.second,_outPair.second.second,tuple);\
}}}\
while(0);
