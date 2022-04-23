#pragma once

/*

Utility class to parse options provided through the libenv interface

There is no error if an option is missing, the passed value is not changed in that case.

*/

#include <string>
#include <vector>
#include <cheerp/client.h>

enum libenv_dtype {
    LIBENV_DTYPE_UNUSED = 0,
    LIBENV_DTYPE_UINT8 = 1,
    LIBENV_DTYPE_INT32 = 2,
    LIBENV_DTYPE_FLOAT32 = 3,
};

#define LIBENV_MAX_NAME_LEN 128
struct libenv_option {
    char name[LIBENV_MAX_NAME_LEN];
    enum libenv_dtype dtype;
    int count;
    void *data;
};

class VecOptions {
  public:
    VecOptions(client::Object* options);
    void consume_string(std::string name, std::string *value);
    void consume_int(std::string name, int32_t *value);
    void consume_bool(std::string name, bool *value);
    void ensure_empty();

  private:
    std::vector<libenv_option> m_options;
    libenv_option find_option(std::string name, enum libenv_dtype dtype);
};
