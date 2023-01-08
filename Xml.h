#pragma once
#include<iostream>
#include<string.h>
#include<list>
#include<map>
#include<stdexcept>
#include<sstream>
using namespace std;

namespace xml {

	class Value {
	public:
		Value();
		Value(bool value);
		Value(int value);
		Value(double value);
		Value(const string& value);//c++字符串
		Value(const char* value);//c语言风格字符串
		//重载=运算符:V v = 1....
		Value& operator=(bool value);
		Value& operator=(int value);
		Value& operator=(double value);
		Value& operator=(const string& value);
		Value& operator=(const char* value);
		Value& operator = (const Value& other);
		//重载=运算符：类的类型转换为内置数据类型，比如int i = v;
		operator bool();
		operator int();
		operator double();
		operator string();
	private:
		string m_value;
	};



	class Xml {
	public:
		//构造函数
		Xml();
		Xml(const string &name);
		Xml(const char* name);
		Xml(const Xml& other);
		Xml& operator =(const Xml& other);
		string name() const;//获取节点名字
		void name(const string& name);//修改节点内容

		string text() const;//获取节点内容
		void text(const string& text);//修改节点内容

		Value attrs(const string& key) ;//获取节点属性
		void attrs(const string& key, const Value& val);//修改节点属性

		string str()  const;//节点序列化

		void append(const Xml& child);//添加子节点
		Xml& operator [](int index);//下标方式添加子节点或者访问子节点
		Xml& operator [](const char* name);
		Xml& operator [](const string& name);//通过名字访问子节点或者创建子节点

		void clear();//清空节点

		void remove(int index);//删除子节点
		void remove(const char* name);//根据名称删除子节点
		void remove(const string& name);//根据名称删除子节点

		//迭代器遍历子节点
		typedef list<Xml>::iterator iterator;
		iterator begin() {
			return m_child->begin();
		}
		iterator end() {
			return m_child->end();
		}
		iterator erase(iterator it) {
			it->clear();
			return m_child->erase(it);
		}
		int size() const;//获取子节点个数，可以进行遍历。

		bool load(const string& name);//加载文件
		bool parse(const string& name);//字符串方式加载
		bool save(const string& name);//保存文件，1.xml->2.xml
	private:
		string * m_name;//节点名字
		string * m_text;//节点内容
		list<Xml>* m_child;//子节点
		map<string, Value>* m_attrs;//节点属性


	};

	

}