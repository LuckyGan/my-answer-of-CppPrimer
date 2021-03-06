 ///
 /// @file    ex9_43.cc
 /// @author  zack(18357154046@163.com)
 /// @date    2017-10-04 18:07:38
 ///
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

void replaceOldVal(string &str, const string &oldVal, const string &newVal) {
	string::iterator iter = str.begin();
	while (str.end() - iter >= oldVal.begin() - oldVal.end()) {
		if (string(iter, iter + oldVal.size()) == oldVal) {
			str.erase(iter, iter + oldVal.size());
			iter = str.insert(iter, newVal.begin(), newVal.end());//这里之所以要用iter接受返回值，是存在重新迭代器失效的问题(insert后，空间变大，需要重新分配空间)
			iter += newVal.size();
		} else
			++iter;
	}
}

int main() {
	{
		string str{"To drive straight thru is a foolish, tho courageous act."};
		replaceOldVal(str, "thru", "through");
		replaceOldVal(str, "tho", "though");
		cout << str << endl;
	}
	{
		string str{"To drive straight thruthru is a foolish, thotho courageous act."};
		replaceOldVal(str, "thru", "through");
		replaceOldVal(str, "tho", "though");
		cout << str << endl;
	}
	{
		string str{"To drive straight thru is a foolish, tho courageous act."};
		replaceOldVal(str, "thru", "thruthru");
		replaceOldVal(str, "tho", "though");
		cout << str << endl;
	}
	{
		string str{"my world is a big world"};
		replaceOldVal(str, "world", "worldddddddddddddddddddddddddd");
		cout << str << endl;
	}
	return 0;
}
