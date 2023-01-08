#pragma once
#include<string>
#include "Xml.h"
using namespace std;

namespace xml {
	class Parser {
	public:
		Parser();
		bool load_file(const string& file);//解析文件格式
		bool load_string(const string& str);//解析字符串
		Xml parse();//开始解析,跳过声明和注释，调用 parse_element() 
	private:
		void skip();//跳过多余字符，比如空格等
		bool parse_declaration();//忽略声明
		bool parse_comment();//解析注释
		Xml parse_element();//解析节点  调用其它私有函数
		string parse_name();//解析节点名称
		string parse_text();//解析节点内容
		string parse_attrs_key();//解析节点属性
		string parse_attrs_val();//解析节点值
	private:
		string m_str;
		int m_idx;
	};
}