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
		Value(const string& value);//c++�ַ���
		Value(const char* value);//c���Է���ַ���
		//����=�����:V v = 1....
		Value& operator=(bool value);
		Value& operator=(int value);
		Value& operator=(double value);
		Value& operator=(const string& value);
		Value& operator=(const char* value);
		Value& operator = (const Value& other);
		//����=��������������ת��Ϊ�����������ͣ�����int i = v;
		operator bool();
		operator int();
		operator double();
		operator string();
	private:
		string m_value;
	};



	class Xml {
	public:
		//���캯��
		Xml();
		Xml(const string &name);
		Xml(const char* name);
		Xml(const Xml& other);
		Xml& operator =(const Xml& other);
		string name() const;//��ȡ�ڵ�����
		void name(const string& name);//�޸Ľڵ�����

		string text() const;//��ȡ�ڵ�����
		void text(const string& text);//�޸Ľڵ�����

		Value attrs(const string& key) ;//��ȡ�ڵ�����
		void attrs(const string& key, const Value& val);//�޸Ľڵ�����

		string str()  const;//�ڵ����л�

		void append(const Xml& child);//����ӽڵ�
		Xml& operator [](int index);//�±귽ʽ����ӽڵ���߷����ӽڵ�
		Xml& operator [](const char* name);
		Xml& operator [](const string& name);//ͨ�����ַ����ӽڵ���ߴ����ӽڵ�

		void clear();//��սڵ�

		void remove(int index);//ɾ���ӽڵ�
		void remove(const char* name);//��������ɾ���ӽڵ�
		void remove(const string& name);//��������ɾ���ӽڵ�

		//�����������ӽڵ�
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
		int size() const;//��ȡ�ӽڵ���������Խ��б�����

		bool load(const string& name);//�����ļ�
		bool parse(const string& name);//�ַ�����ʽ����
		bool save(const string& name);//�����ļ���1.xml->2.xml
	private:
		string * m_name;//�ڵ�����
		string * m_text;//�ڵ�����
		list<Xml>* m_child;//�ӽڵ�
		map<string, Value>* m_attrs;//�ڵ�����


	};

	

}