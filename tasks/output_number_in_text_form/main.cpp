/*
 *  Copyright (c) 2011 Evgeny Proydakov <lord.tiran@gmail.com>
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *  THE SOFTWARE.
 */

#include <map>
#include <list>
#include <cmath>
#include <vector>
#include <string>
#include <cassert>
#include <iostream>


// common types
namespace common {
typedef long long   number_type;
typedef long long   index_type;
typedef std::string mstring;
};

using namespace common;


class convert_number_system
{
public:
    static number_type convert(number_type num, number_type num_base) ;
};


struct translation_main
{
    typedef std::vector<mstring>        text_container;
    typedef std::vector<text_container> main_container;
    
    mstring m_sign_plus_text;
    mstring m_sign_minus_text;
    
    main_container m_text_data;
    text_container m_text_short_tens;
    
    text_container m_thousand_text;
    text_container m_million_text;
    text_container m_billion_text;
};


class translation_exceptions
{
public:
    struct texception_info
    {
        texception_info() {}
        texception_info(index_type pos, number_type value) :
            m_pos(pos),
            m_value(value)
        {
        }
        
        index_type  m_pos;
        number_type m_value;
        
        bool operator<(const texception_info& info) const {
            return (m_pos * 10 + m_value) > (info.m_pos * 10 + info.m_value);
        }
    };
    
    typedef std::map<texception_info, mstring> exception_container;
    
public:
    translation_exceptions(const exception_container& container);
    
    bool get_exception(index_type pos, number_type num, mstring& text) const;
    
private:
    exception_container m_exception_container;
};


class conversion_rules
{
public:
    enum text_comment_size { text_short = 0, text_normal, text_long };
    enum degree_size { degree_thousands, degree_millions, degree_billions };
    
public:
    conversion_rules(const translation_main& tr_main, const translation_exceptions& tr_ex);
    
    void get_text_from_num(number_type num, index_type pos, mstring& text) const;
    void get_text_of_sign(number_type num, mstring& text) const;
    void get_short_text_of_sign(number_type num, mstring& text) const;
    void get_degree_text(mstring& text, int degree, int size) const;
    
    bool get_exception(index_type pos, number_type num, mstring& text) const;
    
private:
    translation_main        m_translation;
    translation_exceptions   m_exceptions;
};


class output_num_to_text
{
public:
    output_num_to_text(const mstring& comment);
    
    void output(const mstring& text);
    void set_comment(const mstring& comment);
    
private:
    mstring m_comment;
};


class converter_num_to_text
{
public:
    static void convert(number_type num, mstring& text, const conversion_rules& rules);
    
private:
    enum { AVALIABLE_SIZE  = 11 };
    
private:
    typedef std::list<mstring> text_container;
    static void text_from_list(const text_container& list, mstring& text);
};


translation_main* create_translation_main();
translation_exceptions* create_translation_exceptions();

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;
    
    number_type input;
    std::cout << "Ведите число [-68719476735, 68719476735]: ";
    std::cin >> input;
    
    number_type system_eight = 8;
    
    number_type num_ten = input;
    number_type num_eight = convert_number_system::convert(input, system_eight);
    
    //std::cout << num_ten << std::endl;
    //std::cout << num_eight << std::endl;
    
    translation_main* tr_main = create_translation_main();
    translation_exceptions* tr_ex = create_translation_exceptions();
    
    conversion_rules rules(*tr_main, *tr_ex);
    
    delete tr_main;
    delete tr_ex;
    
    mstring num_ten_text;
    mstring num_eight_text;
    
    converter_num_to_text::convert(num_ten, num_ten_text, rules);
    converter_num_to_text::convert(num_eight, num_eight_text, rules);
    
    output_num_to_text outputer("в десятичной системе");
    outputer.output(num_ten_text);
    outputer.set_comment("в восьмеричной системе");
    outputer.output(num_eight_text);
    
    return 0;
}

translation_main* create_translation_main()
{
    // This function can be replaced by something more intelligent reads 
    // settings from the localization file
    
    translation_main* tr_main = new translation_main;
    
    tr_main->m_sign_plus_text = "";
    tr_main->m_sign_minus_text = "минус";
    
    translation_main::text_container unit;
    unit.push_back("");
    unit.push_back("один");
    unit.push_back("два");
    unit.push_back("три");
    unit.push_back("четыре");
    unit.push_back("пять");
    unit.push_back("шесть");
    unit.push_back("семь");
    unit.push_back("восемь");
    unit.push_back("девять");
    
    translation_main::text_container tens;
    tens.push_back("");
    tens.push_back("десять");
    tens.push_back("двадцать");
    tens.push_back("тридцать");
    tens.push_back("сорок");
    tens.push_back("пятьдесят");
    tens.push_back("шестьдесят");
    tens.push_back("семьдесят");
    tens.push_back("восемьдесят");
    tens.push_back("девяносто");
    
    translation_main::text_container hundreds;
    hundreds.push_back("");
    hundreds.push_back("сто");
    hundreds.push_back("двести");
    hundreds.push_back("триста");
    hundreds.push_back("четыреста");
    hundreds.push_back("пятьсот");
    hundreds.push_back("шестьсот");
    hundreds.push_back("семьсот");
    hundreds.push_back("восемьсот");
    hundreds.push_back("девятьсот");
    
    tr_main->m_text_data.push_back(unit);
    tr_main->m_text_data.push_back(tens);
    tr_main->m_text_data.push_back(hundreds);
    
    tr_main->m_text_short_tens.push_back("");
    tr_main->m_text_short_tens.push_back("одиннадцать");
    tr_main->m_text_short_tens.push_back("двенадцать");
    tr_main->m_text_short_tens.push_back("тринадцать");
    tr_main->m_text_short_tens.push_back("четырнадцать");
    tr_main->m_text_short_tens.push_back("пятнадцать");
    tr_main->m_text_short_tens.push_back("шестнадцать");
    tr_main->m_text_short_tens.push_back("семнадцать");
    tr_main->m_text_short_tens.push_back("восемнадцать");
    tr_main->m_text_short_tens.push_back("девятнадцать");
    
    tr_main->m_thousand_text.push_back("тысяча");
    tr_main->m_thousand_text.push_back("тысячи");
    tr_main->m_thousand_text.push_back("тысяч");
    
    tr_main->m_million_text.push_back("миллион");
    tr_main->m_million_text.push_back("миллиона");
    tr_main->m_million_text.push_back("миллионов");
    
    tr_main->m_billion_text.push_back("миллиард");
    tr_main->m_billion_text.push_back("миллиарда");
    tr_main->m_billion_text.push_back("миллиардов");
    
    return tr_main;
}

translation_exceptions* create_translation_exceptions()
{
    // This function can be replaced by something more intelligent reads 
    // settings from the localization file
    
    translation_exceptions::exception_container container;
    translation_exceptions::texception_info info;
    
    info.m_pos = 3;
    info.m_value = 1;
    
    container.insert(translation_exceptions::exception_container::value_type(info, "одна"));
    
    info.m_pos = 3;
    info.m_value = 2;
    
    container.insert(translation_exceptions::exception_container::value_type(info, "две"));
    
    translation_exceptions* tr_ex = new translation_exceptions(container);
    
    return tr_ex;
}

// ------------------------------------------------------------------------- //

number_type convert_number_system::convert(number_type num, number_type num_base) 
{
    number_type result = 0;
    
    for(index_type i = 0; num != 0; ++i) {
        result += num % num_base * pow(10, i);
        num /= num_base;
    }
    return result;
}

// ------------------------------------------------------------------------- //

translation_exceptions::translation_exceptions(const exception_container& container) :
    m_exception_container(container)
{
}

bool translation_exceptions::get_exception(index_type pos, number_type num, mstring& text) const
{
    texception_info info(pos, num);
    exception_container::const_iterator it = m_exception_container.find(info);
    if(it != m_exception_container.end()) {
        text = it->second;
        return true;
    }
    return false;
}

// ------------------------------------------------------------------------- //

conversion_rules::conversion_rules(const translation_main& tr_main, const translation_exceptions& tr_ex) :
    m_translation(tr_main),
    m_exceptions(tr_ex)
{    
}

void conversion_rules::get_text_from_num(number_type num, index_type pos, mstring& text) const
{
    text = m_translation.m_text_data[pos][num];
}

void conversion_rules::get_text_of_sign(number_type num, mstring& text) const
{
    if(num < 0)
        text = m_translation.m_sign_minus_text;
    else
        text = m_translation.m_sign_plus_text;
}

void conversion_rules::get_short_text_of_sign(number_type num, mstring& text) const
{
    text = m_translation.m_text_short_tens[num % 10];
}

void conversion_rules::get_degree_text(mstring& text, int degree, int size) const
{
    assert(size >= text_short && size <= text_long);
    
    switch(degree) {
    case degree_thousands:
        text = m_translation.m_thousand_text[static_cast<translation_main::text_container::size_type>(size)];
        break;
        
    case degree_millions:
        text = m_translation.m_million_text[static_cast<translation_main::text_container::size_type>(size)];
        break;
        
    case degree_billions:
        text = m_translation.m_billion_text[static_cast<translation_main::text_container::size_type>(size)];
        break;
        
    default:
        assert(!"INVALID INPUT DATA");
        break;
    }
}

bool conversion_rules::get_exception(index_type pos, number_type num, mstring& text) const
{
    return m_exceptions.get_exception(pos, num, text);
}

// ------------------------------------------------------------------------- //

output_num_to_text::output_num_to_text(const mstring& comment) :
    m_comment(comment)
{
}

void output_num_to_text::output(const mstring& text)
{
    std::cout << text << " " << m_comment << std::endl;
}

void output_num_to_text::set_comment(const mstring& comment)
{
    m_comment = comment;
}

// ------------------------------------------------------------------------- //

void converter_num_to_text::convert(number_type num, mstring& text, const conversion_rules& rules) 
{
    mstring sign_text;
    rules.get_text_of_sign(num, sign_text);
    
    text = sign_text;
    if(sign_text.size())
        text += " ";
    
    num = std::abs(num);
    
    text_container text_list;    
    number_type modulo;
    mstring text_iter;
    bool step = false;
    
    for(index_type i = 0; num > 0; ++i) {
        if(i > AVALIABLE_SIZE)
            assert(!"INVALID INPUT DATA");
        
        modulo = num % 100;
        if(modulo > 10 && modulo < 20 && !(i % 3)) {
            num -= modulo;
            num /= 100;
            rules.get_short_text_of_sign(modulo, text_iter);
            step = true;
        }
        else {
            modulo = num % 10;
            num -= modulo;
            num /= 10;
            rules.get_text_from_num(modulo, i % 3, text_iter);
            step = false;
        }
        
        mstring text_exception;
        if(rules.get_exception(i, modulo, text_exception))
            text_iter = text_exception;
        
        mstring degree;
        
        int csize;
        if(modulo == 1)
            csize = conversion_rules::text_short;
        else if(modulo >= 2 && modulo <= 4)
            csize = conversion_rules::text_normal;
        else
            csize = conversion_rules::text_long;
        
        if(i == 3)    
            rules.get_degree_text(degree, conversion_rules::degree_thousands, csize);
        else if(i == 6)
            rules.get_degree_text(degree, conversion_rules::degree_millions, csize);
        else if(i == 9)
            rules.get_degree_text(degree, conversion_rules::degree_billions, csize);
        
        if(degree.size())
            text_iter += " " + degree;
        
        text_list.push_front(text_iter);
        
        if(step)
            ++i;
    }
    text_from_list(text_list, text);
}

void converter_num_to_text::text_from_list(const text_container& list, mstring& text)
{
    text_container::const_iterator end_it = list.end();
    for(text_container::const_iterator it = list.begin(); it != end_it; ++it) {
        text += *it;
        if((*it).size())
            text += " ";
    }
    
    while(text[text.size() - 1] == ' ')
        text.erase(text.size() - 1, 1);
    
    for(index_type i = 0; i < text.size() - 1; ++i) {
        if(text[i] == ' ' && text[i + 1] == ' ')
            text.erase(i, 1);
    }
}

