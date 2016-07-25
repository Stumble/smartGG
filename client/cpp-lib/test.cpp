#include "call-py.hpp"

int main(int argc, char *argv[])
{
    long data[] = {1, 2, 3, 4, 5};
    const char * cmd = "echo";
    CallPy::act(cmd, data, 5);
    return 0;
}
