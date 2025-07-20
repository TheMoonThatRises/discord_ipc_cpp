/*
  Copyright 2025 Peter Duanmu

  You should have received a copy of the GNU General Public License along
  with discord_ipc_cpp. If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef DISCORD_IPC_CPP_INCLUDE_DISCORD_IPC_CPP_JSON_HPP_
#define DISCORD_IPC_CPP_INCLUDE_DISCORD_IPC_CPP_JSON_HPP_

#include <map>
#include <string>
#include <sstream>
#include <variant>
#include <vector>

namespace discord_ipc_cpp::json {
class JSON;

typedef std::nullptr_t JSONNull;
typedef std::string JSONString;
typedef int JSONInt;
typedef double JSONDouble;
typedef bool JSONBool;
typedef std::map<std::string, JSON> JSONObject;
typedef std::vector<JSON> JSONArray;

class JSON {
 private:
  using JSONValue = std::variant<
    JSONNull,
    JSONString,
    JSONInt,
    JSONDouble,
    JSONBool,
    JSONArray,
    JSONObject
  >;

  JSONValue _value;

 private:
  void stringify(std::ostream& os) const;

 public:
  JSON();
  explicit JSON(JSONNull value);
  explicit JSON(const JSONString& value);
  explicit JSON(const char* value);
  explicit JSON(JSONInt value);
  explicit JSON(JSONDouble value);
  explicit JSON(JSONBool value);
  explicit JSON(const JSONArray& value);
  explicit JSON(const JSONObject& value);

  JSON& operator[](const JSONString& key);
  JSON operator[](const JSONString& key) const;

  template<typename T>
  T as() const;

  template<typename T>
  bool is() const;

  void push_back(const JSON& item);

  std::string to_string() const;
};
}  // namespace discord_ipc_cpp::json

#endif  // DISCORD_IPC_CPP_INCLUDE_DISCORD_IPC_CPP_JSON_HPP_
