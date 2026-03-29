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

// ── debug macro ─────────────────────────────────────────────────────────────
// Active only when compiled with -DLOCAL (auto-injected by assistant.nvim).
// Usage: dbg(x) prints "x = <value>" to /tmp/assistant_dbg.log.
// Completely bypasses stdout/stderr so it won't affect test results.

#ifdef LOCAL
#include <cstdio>
#include <type_traits>

namespace _lc {
inline FILE* _dbg_file() {
  static FILE* f = fopen("/tmp/assistant_dbg.log", "w");
  return f;
}

// trait: iterable container (has begin/end) but not std::string
template <typename T, typename = void>
struct _is_container : std::false_type {};
template <typename T>
struct _is_container<T, std::void_t<
  decltype(std::begin(std::declval<const T&>())),
  decltype(std::end(std::declval<const T&>()))
>> : std::conditional_t<std::is_same_v<std::decay_t<T>, std::string>, std::false_type, std::true_type> {};

// ── _dbg_pr: single dispatch point (struct with overloaded operator()) ──────
struct _dbg_pr {
  // ── primitives ────────────────────────────────────────────────────────────
  void operator()(FILE* f, int v) const { fprintf(f, "%d", v); }
  void operator()(FILE* f, long long v) const { fprintf(f, "%lld", v); }
  void operator()(FILE* f, unsigned v) const { fprintf(f, "%u", v); }
  void operator()(FILE* f, unsigned long long v) const { fprintf(f, "%llu", v); }
  void operator()(FILE* f, double v) const { fprintf(f, "%g", v); }
  void operator()(FILE* f, float v) const { fprintf(f, "%g", (double)v); }
  void operator()(FILE* f, bool v) const { fprintf(f, "%s", v ? "true" : "false"); }
  void operator()(FILE* f, char v) const { fprintf(f, "'%c'", v); }
  void operator()(FILE* f, const char* v) const { fprintf(f, "\"%s\"", v); }
  void operator()(FILE* f, const std::string& v) const { fprintf(f, "\"%s\"", v.c_str()); }

  // ── pair ──────────────────────────────────────────────────────────────────
  template <typename A, typename B>
  void operator()(FILE* f, const std::pair<A, B>& p) const {
    fprintf(f, "(");
    (*this)(f, p.first);
    fprintf(f, ", ");
    (*this)(f, p.second);
    fprintf(f, ")");
  }

  // ── tuple ─────────────────────────────────────────────────────────────────
  template <typename Tuple, size_t... Is>
  void print_tuple(FILE* f, const Tuple& t, std::index_sequence<Is...>) const {
    ((Is == 0 ? (void)0 : (void)fprintf(f, ", "), (*this)(f, std::get<Is>(t))), ...);
  }
  template <typename... Args>
  void operator()(FILE* f, const std::tuple<Args...>& t) const {
    fprintf(f, "(");
    print_tuple(f, t, std::index_sequence_for<Args...>{});
    fprintf(f, ")");
  }

  // ── optional ──────────────────────────────────────────────────────────────
  template <typename T>
  void operator()(FILE* f, const std::optional<T>& v) const {
    if (v.has_value()) (*this)(f, *v);
    else fprintf(f, "nullopt");
  }

  // ── stack ─────────────────────────────────────────────────────────────────
  template <typename T, typename C>
  void operator()(FILE* f, std::stack<T, C> s) const {
    fprintf(f, "{");
    bool first = true;
    while (!s.empty()) {
      if (!first) fprintf(f, ", ");
      (*this)(f, s.top());
      s.pop();
      first = false;
    }
    fprintf(f, "}");
  }

  // ── queue ─────────────────────────────────────────────────────────────────
  template <typename T, typename C>
  void operator()(FILE* f, std::queue<T, C> q) const {
    fprintf(f, "{");
    bool first = true;
    while (!q.empty()) {
      if (!first) fprintf(f, ", ");
      (*this)(f, q.front());
      q.pop();
      first = false;
    }
    fprintf(f, "}");
  }

  // ── priority_queue ────────────────────────────────────────────────────────
  template <typename T, typename C, typename Cmp>
  void operator()(FILE* f, std::priority_queue<T, C, Cmp> pq) const {
    fprintf(f, "{");
    bool first = true;
    while (!pq.empty()) {
      if (!first) fprintf(f, ", ");
      (*this)(f, pq.top());
      pq.pop();
      first = false;
    }
    fprintf(f, "}");
  }

  // ── bitset ────────────────────────────────────────────────────────────────
  template <size_t N>
  void operator()(FILE* f, const std::bitset<N>& b) const {
    auto s = b.to_string();
    fprintf(f, "%s", s.c_str());
  }

  // ── generic iterable container (vector, set, map, deque, list, array…) ──
  template <typename T>
  std::enable_if_t<_is_container<std::decay_t<T>>::value>
  operator()(FILE* f, const T& v) const {
    fprintf(f, "{");
    bool first = true;
    for (const auto& elem : v) {
      if (!first) fprintf(f, ", ");
      (*this)(f, elem);
      first = false;
    }
    fprintf(f, "}");
  }
};

inline constexpr _dbg_pr _dbg_p{};

// ── dbg_out (variadic name=value printer) ───────────────────────────────────
inline void _dbg_out(FILE* f) { fprintf(f, "\n"); fflush(f); }
template <typename T, typename... Args>
inline void _dbg_out(FILE* f, const char* name, T&& val, Args&&... args) {
  const char* comma = name;
  while (*comma && *comma != ',') ++comma;
  fwrite(name, 1, comma - name, f);
  fprintf(f, " = ");
  _dbg_p(f, std::forward<T>(val));
  if constexpr (sizeof...(args) > 0) {
    fprintf(f, ", ");
    ++comma;
    while (*comma == ' ') ++comma;
    _dbg_out(f, comma, std::forward<Args>(args)...);
  } else {
    fprintf(f, "\n");
    fflush(f);
  }
}
} // namespace _lc
#define dbg(...) do { FILE* _f = _lc::_dbg_file(); fprintf(_f, "[DBG] "); _lc::_dbg_out(_f, #__VA_ARGS__, __VA_ARGS__); } while(0)
#else
#define dbg(...)
#endif

#endif // LEETCODE_IO_H
