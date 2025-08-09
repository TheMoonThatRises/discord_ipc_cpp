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
/**
 * \brief Parses JSON strings into the \ref discord_ipc_cpp::json::JSON class.
 *
 * \see discord_ipc_cpp::json::JSON
 */
class Parser {
 public:
  /**
   * \brief Parses JSON string into \ref discord_ipc_cpp::json::JSON class.
   *
   * \param json Input string representation of the JSON object.
   *
   * \return Parsed JSON content.
   */
  static JSON parse(const std::string& json);

 private:
  /**
   * \brief Stored input string representation of the JSON object.
   */
  const std::string& _json;
  /**
   * \brief Parser position within the JSON String.
   */
  size_t _pos;

 private:
  /**
   * \brief Creates the JSON parser.
   *
   * \param json Input string representation of the JSON object.
   */
  explicit Parser(const std::string& json);

  /**
   * \brief Move parser position across all whitespaces.
   */
  void skip_whitespace();
  /**
   * \brief Expect a character at parser position.
   *
   * \param item Expected character.
   *
   * \throws std::runtime_error If the current character is not the expected
   *         character.
   */
  void expect(char item);

  /**
   * \brief Parses a generic JSON value.
   *
   * \return Parsed JSON item.
   *
   * \throws std::runtime_error If the JSON is malformed.
   */
  JSON parse_value();

  /**
   * \brief Parses a JSON object.
   *
   * \return Parsed JSON object.
   *
   * \see discord_ipc_cpp::json::JSONObject
   *
   * \throws std::runtime_error If the JSON is malformed.
   */
  JSON parse_object();
  /**
   * \brief Parses a JSON array.
   *
   * \return Parsed JSON array.
   *
   * \see discord_ipc_cpp::json::JSONArray
   *
   * \throws std::runtime_error If the JSON is malformed.
   */
  JSON parse_array();
  /**
   * \brief Parses a JSON string.
   *
   * \return Parsed JSON string.
   *
   * \see discord_ipc_cpp::json::JSONString
   *
   * \throws std::runtime_error If the JSON is malformed.
   */
  std::string parse_string();
  /**
   * \brief Parses a JSON number.
   *
   * This will attempt to parse the number into either an \c int, \c uint_64,
   * or a \c double.
   *
   * \return Parsed JSON number.
   *
   * \see discord_ipc_cpp::json::JSONInt
   * \see discord_ipc_cpp::json::JSONLong
   * \see discord_ipc_cpp::json::JSONDouble
   *
   * \throws std::runtime_error If the JSON is malformed.
   */
  JSON parse_number();
  /**
   * \brief Parses a JSON literal.
   *
   * This will attempt to parse the literal into either a \c nullptr or \c bool.
   *
   * \return Parsed JSON literal.
   *
   * \see discord_ipc_cpp::json::JSONNull
   * \see discord_ipc_cpp::json::JSONBool
   *
   * \throws std::runtime_error If the JSON is malformed.
   */
  JSON parse_literal();
};
}  // namespace discord_ipc_cpp::json

#endif  // DISCORD_IPC_CPP_INCLUDE_DISCORD_IPC_CPP_PARSER_HPP_
