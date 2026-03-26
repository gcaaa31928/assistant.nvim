#ifndef LEETCODE_IO_H
#define LEETCODE_IO_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// ── helpers ──────────────────────────────────────────────────────────────────

namespace _lc {

inline std::string read_token() {
  std::string line;
  std::getline(std::cin, line);
  // trim leading/trailing whitespace
  auto s = line.find_first_not_of(" \t\r\n");
  auto e = line.find_last_not_of(" \t\r\n");
  if (s == std::string::npos) return "";
  return line.substr(s, e - s + 1);
}

// ── parse primitives ─────────────────────────────────────────────────────────

inline int parse_int(const std::string& s, size_t& pos) {
  while (pos < s.size() && (s[pos] == ' ' || s[pos] == ',')) ++pos;
  bool neg = false;
  if (pos < s.size() && s[pos] == '-') { neg = true; ++pos; }
  int v = 0;
  while (pos < s.size() && s[pos] >= '0' && s[pos] <= '9')
    v = v * 10 + (s[pos++] - '0');
  return neg ? -v : v;
}

inline long long parse_ll(const std::string& s, size_t& pos) {
  while (pos < s.size() && (s[pos] == ' ' || s[pos] == ',')) ++pos;
  bool neg = false;
  if (pos < s.size() && s[pos] == '-') { neg = true; ++pos; }
  long long v = 0;
  while (pos < s.size() && s[pos] >= '0' && s[pos] <= '9')
    v = v * 10 + (s[pos++] - '0');
  return neg ? -v : v;
}

inline double parse_double(const std::string& s, size_t& pos) {
  while (pos < s.size() && (s[pos] == ' ' || s[pos] == ',')) ++pos;
  size_t start = pos;
  if (pos < s.size() && (s[pos] == '-' || s[pos] == '+')) ++pos;
  while (pos < s.size() && ((s[pos] >= '0' && s[pos] <= '9') || s[pos] == '.'))
    ++pos;
  return std::stod(s.substr(start, pos - start));
}

inline bool parse_bool(const std::string& s, size_t& pos) {
  while (pos < s.size() && (s[pos] == ' ' || s[pos] == ',')) ++pos;
  if (s.substr(pos, 4) == "true") { pos += 4; return true; }
  if (s.substr(pos, 5) == "false") { pos += 5; return false; }
  // fallback: treat non-zero as true
  return parse_int(s, pos) != 0;
}

inline char parse_char(const std::string& s, size_t& pos) {
  while (pos < s.size() && (s[pos] == ' ' || s[pos] == ',' || s[pos] == '"' || s[pos] == '\'')) ++pos;
  char c = s[pos++];
  while (pos < s.size() && (s[pos] == '"' || s[pos] == '\'')) ++pos;
  return c;
}

inline std::string parse_string(const std::string& s, size_t& pos) {
  while (pos < s.size() && s[pos] != '"') ++pos;
  ++pos; // skip opening "
  std::string result;
  while (pos < s.size() && s[pos] != '"') {
    if (s[pos] == '\\' && pos + 1 < s.size()) {
      ++pos;
      switch (s[pos]) {
        case 'n': result += '\n'; break;
        case 't': result += '\t'; break;
        case '\\': result += '\\'; break;
        case '"': result += '"'; break;
        default: result += s[pos]; break;
      }
    } else {
      result += s[pos];
    }
    ++pos;
  }
  if (pos < s.size()) ++pos; // skip closing "
  return result;
}

// ── parse from string ────────────────────────────────────────────────────────

inline void parse(const std::string& s, size_t& pos, int& v) { v = parse_int(s, pos); }
inline void parse(const std::string& s, size_t& pos, long long& v) { v = parse_ll(s, pos); }
inline void parse(const std::string& s, size_t& pos, double& v) { v = parse_double(s, pos); }
inline void parse(const std::string& s, size_t& pos, bool& v) { v = parse_bool(s, pos); }
inline void parse(const std::string& s, size_t& pos, char& v) { v = parse_char(s, pos); }
inline void parse(const std::string& s, size_t& pos, std::string& v) { v = parse_string(s, pos); }

template <typename T>
inline void parse(const std::string& s, size_t& pos, std::vector<T>& v) {
  v.clear();
  while (pos < s.size() && s[pos] != '[') ++pos;
  ++pos; // skip '['
  while (pos < s.size() && s[pos] != ']') {
    while (pos < s.size() && (s[pos] == ' ' || s[pos] == ',')) ++pos;
    if (pos < s.size() && s[pos] == ']') break;
    T elem;
    parse(s, pos, elem);
    v.push_back(std::move(elem));
  }
  if (pos < s.size()) ++pos; // skip ']'
}

} // namespace _lc

// ── lc_read ──────────────────────────────────────────────────────────────────

inline void lc_read(int& v) {
  std::string t = _lc::read_token();
  size_t pos = 0;
  _lc::parse(t, pos, v);
}

inline void lc_read(long long& v) {
  std::string t = _lc::read_token();
  size_t pos = 0;
  _lc::parse(t, pos, v);
}

inline void lc_read(double& v) {
  std::string t = _lc::read_token();
  size_t pos = 0;
  _lc::parse(t, pos, v);
}

inline void lc_read(bool& v) {
  std::string t = _lc::read_token();
  size_t pos = 0;
  _lc::parse(t, pos, v);
}

inline void lc_read(char& v) {
  std::string t = _lc::read_token();
  size_t pos = 0;
  _lc::parse(t, pos, v);
}

inline void lc_read(std::string& v) {
  std::string t = _lc::read_token();
  size_t pos = 0;
  _lc::parse(t, pos, v);
}

template <typename T>
inline void lc_read(std::vector<T>& v) {
  std::string t = _lc::read_token();
  size_t pos = 0;
  _lc::parse(t, pos, v);
}

// ── lc_print helpers (element printing via overloading) ──────────────────────

namespace _lc {
inline void print_elem(int v) { std::cout << v; }
inline void print_elem(long long v) { std::cout << v; }
inline void print_elem(double v) { std::cout << v; }
inline void print_elem(bool v) { std::cout << (v ? "true" : "false"); }
inline void print_elem(char v) { std::cout << '"' << v << '"'; }
inline void print_elem(const std::string& v) { std::cout << '"' << v << '"'; }

template <typename T>
inline void print_elem(const std::vector<T>& v) {
  std::cout << '[';
  for (size_t i = 0; i < v.size(); ++i) {
    if (i > 0) std::cout << ',';
    print_elem(v[i]);
  }
  std::cout << ']';
}
} // namespace _lc

// ── lc_print ─────────────────────────────────────────────────────────────────

inline void lc_print(int v) { std::cout << v << std::endl; }
inline void lc_print(long long v) { std::cout << v << std::endl; }
inline void lc_print(double v) { std::cout << v << std::endl; }
inline void lc_print(bool v) { std::cout << (v ? "true" : "false") << std::endl; }
inline void lc_print(char v) { std::cout << '"' << v << '"' << std::endl; }
inline void lc_print(const std::string& v) { std::cout << '"' << v << '"' << std::endl; }

template <typename T>
inline void lc_print(const std::vector<T>& v) {
  _lc::print_elem(v);
  std::cout << std::endl;
}

#endif // LEETCODE_IO_H
