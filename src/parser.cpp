/*
  Copyright 2025 Peter Duanmu

  You should have received a copy of the GNU General Public License along
  with discord_ipc_cpp. If not, see <https://www.gnu.org/licenses/>.
*/

#include <limits>
#include <string>

#include "include/parser.hpp"
#include "include/utils.hpp"

namespace discord_ipc_cpp::json {
using discord_ipc_cpp::utils::unescape_string;

JSON Parser::parse(const std::string& json) {
  return Parser(json).parse_value();
}

Parser::Parser(const std::string& json) : _json(json), _pos(0) {}

void Parser::skip_whitespace() {
  while (_pos < _json.length() && isspace(_json[_pos])) {
    ++_pos;
  }
}

void Parser::expect(char item) {
  skip_whitespace();

  if (_json[_pos] != item) {
    throw std::runtime_error("Unexpected char");
  }

  ++_pos;
}

JSON Parser::parse_value() {
  skip_whitespace();

  switch (_json[_pos]) {
    case '{': return parse_object();
    case '[': return parse_array();
    case '"': return JSON(parse_string());
    case 't':
    case 'f':
    case 'n': return parse_literal();
    default: return parse_number();
  }
}

JSON Parser::parse_object() {
  JSON base(JSONObject{});

  expect('{');
  skip_whitespace();

  if (_json[_pos] == '}') {
    ++_pos;

    return base;
  }

  while (true) {
    std::string key = parse_string();

    expect(':');

    base[key] = parse_value();

    skip_whitespace();

    if (_json[_pos] == '}') {
      ++_pos;

      break;
    }

    expect(',');
  }

  return base;
}

JSON Parser::parse_array() {
  JSON base(JSONArray{});

  expect('[');
  skip_whitespace();

  if (_json[_pos] == ']') {
    ++_pos;

    return base;
  }

  while (true) {
    base.push_back(parse_value());

    skip_whitespace();

    if (_json[_pos] == ']') {
      ++_pos;

      break;
    }

    expect(',');
  }

  return base;
}

std::string Parser::parse_string() {
  size_t start_pos = _pos + 1;
  size_t end_pos = start_pos;

  while (end_pos < _json.length()) {
    if (_json[end_pos] == '"' && _json[end_pos - 1] != '\\') {
      break;
    } else {
      ++end_pos;
    }
  }

  _pos = end_pos + 1;

  return unescape_string(_json.substr(start_pos, end_pos - start_pos));
}

JSON Parser::parse_number() {
  size_t start_pos = _pos;
  size_t end_pos = start_pos;

  bool is_double = false;

  while (end_pos < _json.length()) {
    char check = _json[end_pos];

    if (isdigit(check) || check == '-' || check == '.' || check == 'e') {
      ++end_pos;

      if (check == '.' || check == 'e') {
        is_double = true;
      }
    } else {
      break;
    }
  }

  std::string number = _json.substr(start_pos, end_pos - start_pos);

  _pos = end_pos;

  if (is_double) {
    return JSON(stod(number));
  } else {
    try {
      return JSON(stoi(number));
    } catch (const std::out_of_range&) {
      return JSON(stol(number));
    }
  }
}

JSON Parser::parse_literal() {
  JSON base;
  std::string literal;

  switch (_json[_pos]) {
    case 't':
      literal = "true";
      base = JSON(true);

      break;
    case 'f':
      literal = "false";
      base = JSON(false);

      break;
    default:
      literal = "null";
      base = JSON(nullptr);
  }

  _pos += literal.length();

  return base;
}
}  // namespace discord_ipc_cpp::json
