#include "StringUtil.h"
#include <algorithm>
#include <cctype>

std::vector<std::string> Split(std::string text, std::string delimiter)
{
    std::vector<std::string> tokens;

    size_t pos = 0;

    std::string token;

    while((pos = text.find(delimiter)) != std::string::npos)
    {
        token = text.substr(0,pos);
        tokens.push_back(token);
        text.erase(0,pos + delimiter.length());
    }
    tokens.push_back(text);

    return tokens;

}

void Strip (std::string& text)
{
    int index = 0; 
    while(isspace(text[index]))
    {
        index++;
    }

    text.erase(0,index);

    index = text.length() - 1;
    if( index >0)
    {
        while(isspace(text[index]))
        {
            index--;
        }
        if(index != text.length() - 1)
        {
            text.erase(index + 1, text.length() -1);
        }
    }
}