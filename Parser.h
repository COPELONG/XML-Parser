#pragma once
#include<string>
#include "Xml.h"
using namespace std;

namespace xml {
	class Parser {
	public:
		Parser();
		bool load_file(const string& file);//�����ļ���ʽ
		bool load_string(const string& str);//�����ַ���
		Xml parse();//��ʼ����,����������ע�ͣ����� parse_element() 
	private:
		void skip();//���������ַ�������ո��
		bool parse_declaration();//��������
		bool parse_comment();//����ע��
		Xml parse_element();//�����ڵ�  ��������˽�к���
		string parse_name();//�����ڵ�����
		string parse_text();//�����ڵ�����
		string parse_attrs_key();//�����ڵ�����
		string parse_attrs_val();//�����ڵ�ֵ
	private:
		string m_str;
		int m_idx;
	};
}