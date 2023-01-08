#include "Parser.h"
#include<fstream>
#include<sstream>
using namespace xml;

xml::Parser::Parser():m_str(""),m_idx(0)
{
}

bool xml::Parser::load_file(const string& file)
{
	fstream fin(file);
	if (fin.fail()) {
		return false;
	}
	stringstream ss;
	ss << fin.rdbuf();
	m_str = ss.str();
	m_idx = 0;
	return true;
}

bool xml::Parser::load_string(const string& str)
{
	m_str = str;
	m_idx = 0;
	return true;
}

Xml xml::Parser::parse()
{
	skip();
	int findpos1 = m_str.compare(m_idx, 5, "<?xml");
	if (findpos1 == 0) {
		if (!parse_declaration()) {
			throw logic_error("parse_declaration error");
		}
	}
	
	skip();

	while (m_str.compare(m_idx, 4, "<!--") == 0) {
		if (!parse_comment()) {
			throw logic_error("parse_comment error");
		}
		skip();
	}
	//char a = m_str[m_idx];
	//char b = m_str[m_idx+1];
	if (m_str[m_idx] == '<' && (isalpha(m_str[m_idx + 1]) || m_str[m_idx+1] == '_' )){
		 return parse_element();
	}
	throw new logic_error("element error");
}

void xml::Parser::skip()
{
	while (m_str[m_idx] == ' ' || m_str[m_idx] == '\r' || m_str[m_idx] == '\n' || m_str[m_idx] == '\t') {
		m_idx++;
	}
}

bool xml::Parser::parse_declaration()
{
	m_idx += 5;
	size_t pos = m_str.find("?>", m_idx);
	if (pos == string::npos) {
		return false;
	}
	m_idx =pos+ 2;
	return true;
}

bool xml::Parser::parse_comment()
{
	m_idx += 4;
	size_t pos = m_str.find("-->", m_idx);
	if (pos == string::npos) {
		return false;
	}
	m_idx = pos+3;
	return true;
}

Xml xml::Parser::parse_element()
{
	Xml elem;
	m_idx++;
	skip();
	const string& name = parse_name();
	elem.name(name);
	while (m_str[m_idx] != '/0') {
		skip();
		if (m_str[m_idx] == '/')
		{//<test />½áÊø
			if (m_str[m_idx + 1] == '>')
			{
				m_idx += 2;
				break;
			}
			else
			{
				throw new logic_error(" elem error");
			}
		}

		else if (m_str[m_idx] == '>') 
		{
			m_idx++;
			skip();
			const string& text = parse_text();
			if (text != "") {
				elem.text(text);
			}
		}

		else if (m_str[m_idx] == '<')
		{
			if (m_str[m_idx + 1] == '/')
			{
				string end_tag = "</" + name + ">";
				
				
				size_t pos = m_str.find(end_tag, m_idx);
				if (pos == string::npos) {
					throw new logic_error("xml element name error");

				}
				m_idx = (pos + end_tag.size());
				break;
			}
			else if (m_str.compare(m_idx, 4, "<!--") == 0)
			{
				if (!parse_comment()) {
					throw new logic_error("comment eror");
				}
			}
				else {

					elem.append(parse_element());
				}
			
		}
		
				else
		{
			string key = parse_attrs_key();
			skip();
			if (m_str[m_idx] != '=') {
				throw new logic_error("error");
			}
			m_idx++;
			
			string val = parse_attrs_val();
			elem.attrs(key, val);
		     }
		
		
    }

	return elem;
}		

	    
	


string xml::Parser::parse_name()
{
	int pos = m_idx;
	//char a =m_str[m_idx];
	if (isalpha(m_str[m_idx]) || (m_str[m_idx] == '_')) {
		m_idx++;
		while (isalnum(m_str[m_idx])||(m_str[m_idx]=='_')||(m_str[m_idx]=='-')||((m_str[m_idx] == '-')==':')) {
			m_idx++;
		}
	}
	//string name = m_str.substr(pos, m_idx - pos);
	return m_str.substr(pos,m_idx -pos);
}

string xml::Parser::parse_text()
{
	int pos = m_idx;
	while (m_str[m_idx] != '<') {
		m_idx++;
	}
	return m_str.substr(pos, m_idx-pos);
}

string xml::Parser::parse_attrs_key()
{
	int pos = m_idx;
	//char a = m_str[m_idx];
	if (isalpha(m_str[m_idx]) || (m_str[m_idx] == '_')) {
		m_idx++;
		while (isalnum(m_str[m_idx]) || (m_str[m_idx] == '_') || (m_str[m_idx] == '-') || (m_str[m_idx] == ':')) {
			m_idx++;
		}
	}
	//string b = m_str.substr(pos, m_idx - pos);
	return m_str.substr(pos, m_idx - pos);
	
}

string xml::Parser::parse_attrs_val()
{
	if (m_str[m_idx] != '"') {
		throw new logic_error("Val error");

	}
	//m_idx++;
	int pos = m_idx;
	char a = m_str[m_idx];
	while (m_str[m_idx] != '"') {
		m_idx++;
	}
	m_idx++;
	//string b = m_str.substr(pos, m_idx - pos - 1);
	return m_str.substr(pos, m_idx - pos-1);
}
