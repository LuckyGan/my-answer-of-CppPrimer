 ///
 /// @file    ex13_44.h
 /// @author  zack(18357154046@163.com)
 /// @date    2017-09-06 20:57:52
 ///
#ifndef __CP5_EX13_44_H__
#define __CP5_EX13_44_H__
#include <memory>
using std::pair;
using std::uninitialized_copy;

class String{
public:
	String();
	String(const char*);
	String(const String&);
	String& operator=(const String&);
	~String();
	const char* c_str() const;
	size_t size() const;
private:
	pair<char*, char*> alloc_n_copy(const char*, const char*);
	void range_initializer(const char*, const char*);
	void free();
private:
	char* elements;
	char* end;
	static std::allocator<char> alloc;
};

String::String():String("") {
}

String::String(const char *s) {
	const char *s1 = s;
	while (*s1)
		++s1;
	range_initializer(s, ++s1);
}

String::String(const String &rhs) {
	range_initializer(rhs.elements, rhs.end);
}

String& String::operator=(const String &rhs) {
	auto data = alloc_n_copy(rhs.elements, rhs.end);
	free();
	elements = data.first;
	end = data.second;
	return *this;
}

String::~String() {
	free();
}

const char* String::c_str() const {
	return elements;
}

size_t String::size() const {
	return end - elements;
}
 
pair<char*, char*> String::alloc_n_copy(const char *begin, const char *end) {
	auto data = alloc.allocate(end - begin);
	return {data, uninitialized_copy(begin, end, data)};
}

void String::free() {
	if (elements) {
		for (auto p = end; p != elements; )
			alloc.destroy(--p);
		alloc.deallocate(elements, end - elements);
	}
}

void String::range_initializer(const char *begin, const char *end) {
	auto data = alloc_n_copy(begin, end);
	elements = data.first;
	end = data.second;
}

#endif
