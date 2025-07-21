/*
  Copyright 2025 Peter Duanmu

  You should have received a copy of the GNU General Public License along
  with discord_ipc_cpp. If not, see <https://www.gnu.org/licenses/>.
*/

#include <format>
#include <string>
#include <sstream>
#include <variant>
#include <vector>

#include "discord_ipc_cpp/json.hpp"

#include "include/utils.hpp"

namespace discord_ipc_cpp::json {
using discord_ipc_cpp::utils::escape_string;

JSON::JSON() : _value(JSONObject{}) {}

JSON::JSON(JSONNull value) : _value(value) {}

JSON::JSON(const JSONString& value) : _value(value) {}

JSON::JSON(const char* value) : _value(std::string(value)) {}

JSON::JSON(JSONInt value) : _value(value) {}

JSON::JSON(JSONLong value) : _value(value) {}

JSON::JSON(JSONDouble value) : _value(value) {}

JSON::JSON(JSONBool value) : _value(value) {}

JSON::JSON(const JSONArray& value) : _value(value) {}

JSON::JSON(const JSONObject& value) : _value(value) {}

JSON& JSON::operator[](const JSONString& key) {
  return std::get<JSONObject>(_value)[key];
}

const JSON& JSON::operator[](const JSONString& key) const {
  return std::get<JSONObject>(_value).at(key);
}

template<typename T>
T JSON::as() const {
  return std::get<T>(_value);
}

template<typename T>
bool JSON::is() const {
  return std::holds_alternative<T>(_value);
}

bool JSON::has(const JSONString& key) const {
  return as<JSONObject>().contains(key);
}

void JSON::push_back(const JSON& item) {
  std::get<JSONArray>(_value).push_back(item);
}

void JSON::stringify(std::ostream& os) const {
  if (is<JSONObject>()) {
    JSONObject object = as<JSONObject>();
    bool first_item = true;

    os << "{";

    for (const auto& [key, value] : object) {
      if (!first_item) {
        os << ",";
      } else {
        first_item = false;
      }

      os << "\"" << escape_string(key) << "\":";
      value.stringify(os);
    }

    os <<"}";
  } else if (is<JSONArray>()) {
    JSONArray array = as<JSONArray>();
    bool first_item = true;

    os << "[";

    for (const auto& item : array) {
      if (!first_item) {
        os << ",";
      } else {
        first_item = false;
      }

      item.stringify(os);
    }

    os << "]";
  } else if (is<JSONString>()) {
    os << "\"" << escape_string(as<JSONString>()) << "\"";
  } else if (is<JSONInt>()) {
    os << std::to_string(as<JSONInt>());
  } else if (is<JSONLong>()) {
    os << std::to_string(as<JSONLong>());
  } else if (is<JSONDouble>()) {
    os << std::to_string(as<JSONDouble>());
  } else if (is<JSONBool>()) {
    os << (as<JSONBool>() ? "true" : "false");
  } else if (is<JSONNull>()) {
    os << "null";
  }
}

std::string JSON::to_string() const {
  std::stringstream os;
  stringify(os);
  return os.str();
}

template JSONString JSON::as<JSONString>() const;
template JSONInt JSON::as<JSONInt>() const;
template JSONDouble JSON::as<JSONDouble>() const;
template JSONBool JSON::as<JSONBool>() const;
template JSONArray JSON::as<JSONArray>() const;
template JSONObject JSON::as<JSONObject>() const;
template JSONNull JSON::as<JSONNull>() const;

template bool JSON::is<JSONString>() const;
template bool JSON::is<JSONInt>() const;
template bool JSON::is<JSONDouble>() const;
template bool JSON::is<JSONBool>() const;
template bool JSON::is<JSONArray>() const;
template bool JSON::is<JSONObject>() const;
template bool JSON::is<JSONNull>() const;
}  // namespace discord_ipc_cpp::json
