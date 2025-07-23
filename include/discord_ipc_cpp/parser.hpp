/*
  Copyright 2025 Peter Duanmu

  You should have received a copy of the GNU General Public License along
  with discord_ipc_cpp. If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef DISCORD_IPC_CPP_INCLUDE_DISCORD_IPC_CPP_PARSER_HPP_
#define DISCORD_IPC_CPP_INCLUDE_DISCORD_IPC_CPP_PARSER_HPP_

#include <string>

#include "discord_ipc_cpp/json.hpp"

namespace discord_ipc_cpp::json {
class Parser {
 public:
  static JSON parse(const std::string& json);

 private:
  const std::string& _json;
  size_t _pos;

 private:
  explicit Parser(const std::string& json);

  void skip_whitespace();
  void expect(char item);

  JSON parse_value();

  JSON parse_object();
  JSON parse_array();
  std::string parse_string();
  JSON parse_number();
  JSON parse_literal();
};
}  // namespace discord_ipc_cpp::json

#endif  // DISCORD_IPC_CPP_INCLUDE_DISCORD_IPC_CPP_PARSER_HPP_
