#include "utility.hpp"

namespace vg {

string reverse_complement(const string& seq) {
    string rc;
    rc.assign(seq.rbegin(), seq.rend());
    for (auto& c : rc) {
        switch (c) {
        case 'A': c = 'T'; break;
        case 'T': c = 'A'; break;
        case 'G': c = 'C'; break;
        case 'C': c = 'G'; break;
        case 'N': c = 'N'; break;
        default: break;
        }
    }
    return rc;
}

int get_thread_count(void) {
    int thread_count = 1;
#pragma omp parallel
    {
#pragma omp master
        thread_count = omp_get_num_threads();
    }
    return thread_count;
}

std::vector<std::string> &split_delims(const std::string &s, const std::string& delims, std::vector<std::string> &elems) {
    char* tok;
    char cchars [s.size()+1];
    char* cstr = &cchars[0];
    strcpy(cstr, s.c_str());
    tok = strtok(cstr, delims.c_str());
    while (tok != NULL) {
        elems.push_back(tok);
        tok = strtok(NULL, delims.c_str());
    }
    return elems;
}
std::vector<std::string> split_delims(const std::string &s, const std::string& delims) {
    std::vector<std::string> elems;
    return split_delims(s, delims, elems);
}

const std::string sha1sum(const std::string& data) {
    SHA1 checksum;
    checksum.update(data);
    return checksum.final();
}

const std::string sha1head(const std::string& data, size_t head) {
    return sha1sum(data).substr(0, head);
}

}
