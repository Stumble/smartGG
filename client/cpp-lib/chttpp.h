/* pre: apt-get install libcurl4-openssl-dev */

#ifndef CHTTPP
#define CHTTPP

#include <iostream>
#include <string>
#include <sstream>
#include <curl/curl.h>

class CHttpp
{
public:
    CHttpp();
    bool isMoistureOpen();
    void syncData(int * data, int size);
    void setIp(std::string);
private:
    bool get(const char * url);
    bool post(const char * url, const std::string & postData);
    std::string genPostData(const std::string * naming, int * data, int size);
private:
    std::string m_Ip;
    std::string m_getUrl;
    std::string m_postUrl;
};

#endif