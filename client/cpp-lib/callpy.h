#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <string>

using std::string;

#ifndef CALL_PY_HPP
#define CALL_PY_HPP

class CallPy
{
public:
  static void act(const char * cmd, long * data, int size) {
    memset(m_str, 0, sizeof(m_str));
    int pos = 0;
    for (int i = 0; i < size; i++) {
      pos += sprintf(m_str + pos, " %ld", data[i]);
    }
    system((string(cmd) + string(m_str)).c_str());
  }
private:
  static char m_str[1000];
};
char CallPy::m_str[1000];
#endif