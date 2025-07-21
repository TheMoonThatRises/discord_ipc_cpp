/*
  Copyright 2025 Peter Duanmu

  You should have received a copy of the GNU General Public License along
  with discord_ipc_cpp. If not, see <https://www.gnu.org/licenses/>.
*/

#include <unistd.h>

#include <map>
#include <string>
#include <vector>
#include <random>
#include <regex>

#include "include/utils.hpp"

namespace discord_ipc_cpp::utils {
const std::map<std::string, std::string> _escape_key {
  {"\\\"", "\""}
};

std::string find_discord_ipc_file() {
  std::string user_tmp_dir = getenv("TMPDIR");
  std::string base_ipc_name = "discord-ipc-";

  for (int i = 0; i < 10; ++i) {
    std::string test_path = user_tmp_dir + base_ipc_name + std::to_string(i);

    if (access(test_path.c_str(), R_OK) >= 0) {
      return test_path;
    }
  }

  return "";
}

std::string unescape_string(const std::string& input) {
  std::string output = input;

  for (const auto& [key, value] : _escape_key) {
    output = std::regex_replace(output, std::regex(key), value);
  }

  return output;
}

std::string escape_string(const std::string& input) {
  std::string output = input;

  for (const auto& [key, value] : _escape_key) {
    output = std::regex_replace(output, std::regex(value), key);
  }

  return output;
}

template<typename T>
T generate_random_num(T min, T max) {
  static std::random_device _rdev;
  static std::mt19937 _rng(_rdev());
  static std::uniform_real_distribution<> _rdist(min, max);

  return _rdist(_rng);
}

std::string generate_uuid() {
  static const std::string _valid_chars = "0123456789abcdef";
  static const std::vector<int> _dashes = {
    0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0
  };

  std::string uuid = "";

  for (int i = 0; i < 16; ++i) {
    if (_dashes[i]) {
      uuid += '-';
    }

    uuid += _valid_chars[generate_random_num(0, 15)];
    uuid += _valid_chars[generate_random_num(0, 15)];
  }

  return uuid;
}

template<typename A, typename B>
A reverse_map_search(const std::map<A, B>& map, const B& item) {
  for (const auto& [key, value] : map) {
    if (value == item) {
      return key;
    }
  }

  return nullptr;
}

template double generate_random_num(double, double);
template int generate_random_num(int, int);
}  // namespace discord_ipc_cpp::utils
