#ifndef __CP5_EX14_26_STRING_H__
#define __CP5_EX14_26_STRING_H__

#include <string.h>
#include <iostream>
#include <memory>
using std::ostream;
using std::pair;
using std::uninitialized_copy;

class String {
	friend ostream& operator<<(ostream&, const String&);
	friend bool operator==(const String&, const String&);
	friend bool operator!=(const String&, const String&);
	friend bool operator<(const String&, const String&);
	friend bool operator<=(const String&, const String&);
	friend bool operator>(const String&, const String&);
	friend bool operator>=(const String&, const String&);
public:
	String();
	String(const char*);
	String(const String&);
	String& operator=(const String&);
	~String();
	const char* c_str() const;
	size_t size() const;
	char& operator[](size_t);
	const char& operator[](size_t) const;
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

ostream& operator<<(ostream &os, const String &str) {
	os << str.c_str();
	return os;
}

bool operator==(const String &lhs, const String &rhs) {
	return !strcmp(lhs.c_str(), rhs.c_str());
}

bool operator!=(const String &lhs, const String &rhs) {
	return !(lhs == rhs);
}

bool operator<(const String &lhs, const String &rhs) {
	return strcmp(lhs.c_str(), rhs.c_str()) < 0;
}

bool operator<=(const String &lhs, const String &rhs) {
	return !(lhs > rhs);

}

bool operator>(const String &lhs, const String &rhs) {
	return rhs < lhs;
}

bool operator>=(const String &lhs, const String &rhs) {
	return !(lhs < rhs);

}

char& String::operator[](size_t idx) {
	return *(elements + idx);
}

const char& String::operator[](size_t idx) const {
	return *(elements + idx); 
}

#endif
