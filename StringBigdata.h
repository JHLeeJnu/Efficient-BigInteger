#ifndef BIGNUMBER_ADD
#define BIGNUMBER_ADD
#include "iostream"
#include  "string"
#include "algorithm"

using namespace std;

const int M =7;
string add(const string& ans, const string& temp);
string multiply(const string& x,const string& y);
inline int Mod(string&, int&);//����ʵ�ִ�������1 : A%B(A�ܴ�B������������ʾ)
string Mod(const string&, const string&);//ʵ�ִ�������2 : A%B(A��B��������������ʾ)
string Subtract(const  string& a, const string& b, bool reverse = false);//ʵ�ִ�������� A-B
inline string remove_pre_zero(const string& a);
string convert_to_bin(const string&);//ʵ�ִ���ת����������
string Effective_multiply(const string&, const string&);
int      Power_mod(int& x, int& y, int& z);
string Power_mod(const string& x, const string& y, const  string& z);//x,y,z���ܴ�,����x=5423123456789987654331452345;


#endif
