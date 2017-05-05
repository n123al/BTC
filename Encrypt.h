#include <string>

std::string encrypt(unsigned char const* , unsigned int len, std::string const& key);
std::string decrypt(std::string const& s, std::string const& key);