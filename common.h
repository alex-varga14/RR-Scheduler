#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <sstream>

/// reads in a line from stdin
/// returns empty string on EOF
/// return string includes trailing '\n' if present
std::string stdin_readline();

/// splits string into tokens (words)
/// separators are sequences of white spaces
std::vector<std::string> split(const std::string& str);

/// joins a vector of strings into a single string, using a separator
std::string join(const std::vector<std::string>& toks, const std::string& sep = " ");

/// removes leading & trailing white space, and replaces any consecutive
/// whitespaces with a space ' '
std::string simplify(const std::string& str);

/// check if string is alphanumeric
bool is_alnum(const std::string& str);

class Word2Int {
    int counter = 0;
    std::unordered_map<std::string, int> myset;

public:
    int get(const std::string& w);
};

/// timer class for measuring elapsed time
struct Timer {
    // return elapsed time (in seconds) since last reset/or construction
    // reset_p = true will reset the time
    double elapsed(bool reset_p = false);
    // reset the time to 0
    void reset();
    Timer();
    ~Timer();

private:
    struct Pimpl;
    Pimpl* pimpl_;
};

class fatal_error : public std::exception
{
public :
    fatal_error() {;}
    // circumvenging lack of stringstream copy constructor
    fatal_error( const fatal_error &that )
    {
        mWhat += that.mStream.str();
    }
    virtual ~fatal_error() throw(){;}
    virtual const char *what() const throw() override
    {
        if ( mStream.str().size() ) {
            mWhat += mStream.str();
            mStream.str( "" );
        }
        return mWhat.c_str();
    }
    template<typename T>
    fatal_error& operator<<( const T& t )
    {
        mStream << t;
        return *this;
     }
private:
   mutable std::stringstream mStream;
   mutable std::string mWhat;
};

struct Colors {
    constexpr static const char * reset =  "\033[0m" ;
    constexpr static const char * yellow = "\033[0;33m";
    constexpr static const char * byellow = "\033[0;93m";
    constexpr static const char * red= "\033[0;31m";
    constexpr static const char * bred= "\033[0;91m";
    constexpr static const char * green= "\033[0;32m";
    constexpr static const char * bgreen= "\033[0;92m";
};