#include "file/file_wrapper.hpp"

template<class BaseWrapper>
class WrappedStream {
public:
    WrappedStream(WrappedFile* file) {
        this->file = file;
    }

    virtual ~WrappedStream() = default; // Destructor must be implemented in specified wrapper

    BaseWrapper base_wrapper();
protected:
    WrappedFile * file;
};

class __WrappedStream
{

};