#if defined(_WIN32) || defined(_WIN64)

#include <algorithm>
#include "linux/linux_wrapper.hpp"

#else
#define OS 1
#endif

namespace wrapper {

    struct dir_entry;

    template<typename BaseStream>
    class wrapped_file {
    public:
        bool is_dir();

        bool is_open();

        std::string name();

        bool rename(std::unary_function<std::string, std::string> uop);

        BaseStream base_stream();

    private:
        std::string str_name;
        BaseStream stream;
    };

    class dir_iterator : public std::iterator<std::input_iterator_tag, dir_entry> {
    public:
        bool has_next();

        struct dir_entry *next();

    };

    struct dir_entry {

    };

    template<typename BaseStream>
    wrapped_file<BaseStream> wrap_file_stream(std::string &name) {
        return new wrapped_file<BaseStream>(name);
    }

}