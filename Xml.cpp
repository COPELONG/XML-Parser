#include "Xml.h"
#include "Parser.h"
#include<fstream>
#include <sstream>
using namespace xml;
xml::Xml::Xml(): m_name(nullptr),m_child(nullptr),m_text(nullptr),m_attrs(nullptr)
{
}

xml::Xml::Xml(const string& name) : m_name(nullptr), m_child(nullptr), m_text(nullptr), m_attrs(nullptr)
{
	m_name = new string(name);
}

xml::Xml::Xml(const char* name) : m_name(nullptr), m_child(nullptr), m_text(nullptr), m_attrs(nullptr)
{
	m_name = new string(name);
}

xml::Xml::Xml(const Xml& other)
{
	m_name = other.m_name;
	m_text = other.m_text;
	m_attrs = other.m_attrs;
	m_child = other.m_child;
}

Xml& xml::Xml::operator=(const Xml& other)
{
	clear();
	m_name = other.m_name;
	m_text = other.m_text;
	m_attrs = other.m_attrs;
	m_child = other.m_child;
	return *this;
}

string xml::Xml::name() const
{
	if (m_name == nullptr) {
		return "";
}
	return *m_name;
}

void xml::Xml::name(const string& name)
{
	if (m_name!= nullptr) {
		delete m_name;
		m_name = nullptr;
	}
	m_name = new string(name);
}

string xml::Xml::text() const
{
	if (m_text == nullptr) {
		return "";
	}
	return *m_text;
}

void xml::Xml::text(const string& text)
{
	if (m_text != nullptr) {
		delete m_text;
		m_text = nullptr;
	}
	m_text = new string(text);
}

Value xml::Xml::attrs(const string& key)  {
	if (m_attrs == nullptr) {
		m_attrs = new map<string, Value>();
	}
	return (*m_attrs)[key];
}
void xml::Xml::attrs(const string& key, const Value& val) {
	if (m_attrs == nullptr) {
		m_attrs = new map<string, Value>();
	}
	(*m_attrs)[key] = val;
}

string xml::Xml::str() const
{
	if (m_name == nullptr) {
		throw new logic_error("null");
	}
	stringstream ss;
	ss << "<";
	ss << *m_name;
	if (m_attrs != nullptr) {
		for (auto it = m_attrs->begin(); it != m_attrs->end(); it++) {
			ss << " " << it->first << "=\"" << string(it->second) << "\"";
		}
	}
	ss << ">";
	if (m_child != nullptr) {
		for (auto it = m_child->begin(); it != m_child->end(); it++) {
			ss<<it->str();
		}
	}
	if (m_text != nullptr) {
		ss << *m_text;
	}
	ss << "</" << *m_name << ">";
	return ss.str();
}

void xml::Xml::append(const Xml& child)
{
	if (m_child == nullptr) {
		m_child = new list<Xml>();
	}
	m_child->push_back(child);
}

Xml& xml::Xml::operator[](int index)
{
	
	if (index < 0) {
		throw logic_error("less zero");
	}
	if (m_child == nullptr) {
		m_child == new list<Xml>();
	}
	int size = m_child->size();
	if (index >=0 && index < size) {
		auto it = m_child->begin();
		for (int i = 0; i < index;i++) {
			it++;
		}
		return *it;
	}
	if (index >= size) {
		for (int i = size; i <= index; i++) {
			m_child->push_back(Xml());
		}
	}
      return m_child->back();

}

Xml& xml::Xml::operator[](const char* name)
{
	return (*this)[string(name)];
}

Xml& xml::Xml::operator[](const string& name)
{
	if (m_child == nullptr) {
		m_child == new list<Xml>();
	}
	for (auto it = m_child->begin(); it != m_child ->end(); it++) {
		if (it->name() == name) {
			return *it;
		}
	}
	m_child->push_back(Xml(name));
	 return m_child->back();
}

void xml::Xml::clear()
{
	if (m_name != nullptr) {
		delete m_name;
		m_name = nullptr;
	}
	if (m_text != nullptr) {
		delete m_text;
		m_text = nullptr;
	}
	if (m_attrs != nullptr) {
		delete m_attrs;
		m_attrs = nullptr;
	}
	
	if (m_child != nullptr) {
		for (auto it = m_child->begin(); it != m_child->end(); it++) {
			it->clear();
		}
	}
	
}

void xml::Xml::remove(int index)
{
	if (m_child == nullptr) {
		return;
	}
	int size = m_child->size();
	if (index < 0 || index >= size) {
		return;
	}
	auto it = m_child->begin();
	for (int i = 0; i < index; i++) {
		it++;
	}
	it->clear();
	m_child->erase(it);
}

void xml::Xml::remove(const char* name)
{
	remove(string(name));
}

void xml::Xml::remove(const string& name)
{
	if (m_child == nullptr) {
		return;
	}
	for (auto it = m_child->begin(); it != m_child->end();) {
		if (it->name() == name) {
			it->clear();
			it = m_child->erase(it);
		}
	}
}

int xml::Xml::size() const
{
	return m_child->size();
}
bool xml::Xml::load(const string& name)
{
	Parser p;
	if (!p.load_file(name)) {
		return false;
	}
	*this = p.parse();
	return true;
}
bool xml::Xml::parse(const string& name)
{
	Parser p;
	if (p.load_string(name)) {
		return false;
	}
	*this = p.parse();
	return true;
}
bool xml::Xml::save(const string& name)
{
	fstream f(name);
	if (f.fail()) {
		return false;

	}
	f << str();//先调用load函数，在调用save函数，使用序列化存入流中。
	f.close();
	return true;

}
Value::Value() {

}
Value::Value(bool value) {
	*this = value;
}
Value::Value(int value) {
	*this = value;
}
Value::Value(double value) {
	*this = value;
}
Value::Value(const string& value) {
	*this = value;
}

Value::Value(const char* value) {
	*this = value;
}
Value& Value::operator=(bool value) {
	m_value = value ? "true" : "false";
	return*this;
}
Value& Value::operator=(int value) {
	stringstream ss;
	ss << value;
	m_value = ss.str();
	return*this;
}
Value& Value::operator=(double value) {
	stringstream ss;
	ss << value;
	m_value = ss.str();
	return*this;
}
Value& Value::operator=(const string& value) {
	m_value = value;
	return*this;
}
Value& Value::operator=(const char* value) {
	m_value = value;
	return*this;
}
Value& xml::Value::operator=(const Value& other)
{
	m_value = other.m_value;
	return *this;
}
Value::operator bool() {
	if (m_value == "true") {
     return true;
	}
	else if (m_value == "false") {
		return false;
	}
	return false;
	
}
Value::operator int() {
	return atoi(m_value.c_str());//先转化为c类型的字符串才能使用atoi将stirng转化为int类型
}
Value::operator double() {
	return atof(m_value.c_str());
}
Value::operator string() {
	return m_value;
}