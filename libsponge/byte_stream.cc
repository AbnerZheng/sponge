#include "byte_stream.hh"

#include <string>
#include "iostream"
using namespace std;

// Dummy implementation of a flow-controlled in-memory byte stream.

// For Lab 0, please replace with a real implementation that passes the
// automated checks run by `make check_lab0`.

// You will need to add private members to the class declaration in `byte_stream.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

using namespace std;

ByteStream::ByteStream(const size_t cap)
    : capacity(cap), buffer(deque<char>()), total_write(0), total_read(0), ended(false) {}

size_t ByteStream::write(const string &data) {
    if (ended) {
        return 0;
    }
    int n = min(remaining_capacity(), data.length());
    buffer.insert(this->buffer.end(), data.begin(), data.begin() + n);
    total_write += n;
    return n;
}

//! \param[in] len bytes will be copied from the output side of the buffer
string ByteStream::peek_output(const size_t len) const {
    return string(this->buffer.begin(), this->buffer.begin() + len);
}

//! \param[in] len bytes will be removed from the output side of the buffer
void ByteStream::pop_output(const size_t len) {
    size_t n = min(this->buffer.size(), len);
    total_read += n;
    while (n-- > 0) {
        this->buffer.pop_front();
    }
}

//! Read (i.e., copy and then pop) the next "len" bytes of the stream
//! \param[in] len bytes will be popped and returned
//! \returns a string
std::string ByteStream::read(const size_t len) {
    std::size_t n = min(len, buffer.size());
    string s;
    s.insert(s.end(), buffer.begin(), buffer.begin() + n);
    total_read += n;
    return s;
}

void ByteStream::end_input() { ended = true; }

bool ByteStream::input_ended() const { return ended; }

size_t ByteStream::buffer_size() const { return buffer.size(); }

bool ByteStream::buffer_empty() const { return buffer.empty(); }

bool ByteStream::eof() const { return ended && buffer.empty(); }

size_t ByteStream::bytes_written() const { return total_write; }

size_t ByteStream::bytes_read() const { return total_read; }

size_t ByteStream::remaining_capacity() const { return capacity - buffer_size(); }
