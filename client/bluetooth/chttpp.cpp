#include "chttpp.h"
#include <curl/curl.h>

// compile with following:
// g++  -Wall -Wconversion -g -O2 chttpp.cpp -lm -lcurl -o chttpp

#include <iostream>
#include <cstring>
#include <fstream>

using std::string;
using std::stringstream;

const string names[] = {"MQ2A", "MQ2D", "MQ7A", "MQ7D", "MQ4A", "MQ4D", "MQ135A", "MQ135D", "TEMPERATURE", "MOISTURE"};

CHttpp::CHttpp()
{

}

bool CHttpp::isMoistureOpen()
{
  bool res = get(m_getUrl.c_str());
  bool isOpen = false;
  std::ifstream fin("/tmp/smartgg", std::ios::in);
  if (!res) {
    std::cout << "get HTTP error" << std::endl;
  }
  fin >> isOpen;
  return isOpen;
}

void CHttpp::syncData(int * data, int size)
{
  string parameters = genPostData(names, data, size);
  post(m_postUrl.c_str(), parameters);
}

void CHttpp::setIp(std::string ip)
{
  m_Ip = ip;
  m_getUrl = "http://" + ip + "/smartgg/index.php/sgg/moisture";
  m_postUrl = "http://"+ ip + "/smartgg/index.php/sgg/update";
}

// get data from url, save to rst
bool CHttpp::get(const char * url)
{
  CURL *curl;
  CURLcode res;
  FILE *fp = fopen("/tmp/smartgg", "w");
  curl = curl_easy_init();    // 初始化
  if (curl)
  {
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
    res = curl_easy_perform(curl);   // 执行
    fclose(fp);
    if (res != 0) {
      return false;
    }
    curl_easy_cleanup(curl);
    return true;
  }
  return false;
}

// convert key-data to post parameter string
string CHttpp::genPostData(const string * naming, int * data, int size)
{
  stringstream converter;
  for (int i = 0; i < size; i++) {
    converter << "&" << naming[i] << "=" << data[i];
  }
  return converter.str();
}

// post data to url, data should be a paramter style string
bool CHttpp::post(const char * url, const string & postData)
{
  CURL *curl;
  CURLcode res;
  curl = curl_easy_init();
  if (curl)
  {
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.c_str());    // 指定post内容
    curl_easy_setopt(curl, CURLOPT_URL, url);   // 指定url
    res = curl_easy_perform(curl);
    if (res != 0) {
      std::cout << res << std::endl;
    }
    curl_easy_cleanup(curl);
  }
  return true;
}

int mainsss(int argc, char *argv[])
{
  using std::cout;
  using std::endl;
  CHttpp httpSender;
  httpSender.setIp("localhost");
  if (httpSender.isMoistureOpen()) {
    std::cout << "true" << std::endl;
  } else
    std::cout << "false" << std::endl;

  int data[] = {11, 22, 33, 4, 5, 6, 7, 8, 9, 10};

  httpSender.syncData(data, 10);
  return 0;
}
