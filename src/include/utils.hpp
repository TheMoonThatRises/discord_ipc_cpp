/*
  Copyright 2025 Peter Duanmu

  You should have received a copy of the GNU General Public License along
  with discord_ipc_cpp. If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef DISCORD_IPC_CPP_SRC_INCLUDE_UTILS_HPP_
#define DISCORD_IPC_CPP_SRC_INCLUDE_UTILS_HPP_

#include <map>
#include <string>
#include <optional>
#include <vector>

namespace discord_ipc_cpp::utils {
extern const std::map<std::string, std::string> _escape_key;

std::string find_discord_ipc_file();

std::string unescape_string(const std::string& input);
std::string escape_string(const std::string& input);

template<typename T>
T generate_random_num(T min, T max);

std::string generate_uuid();

template<typename K, typename V>
std::optional<K> reverse_map_search(const std::map<K, V>& map, const V& item);
}  // namespace discord_ipc_cpp::utils

#endif  // DISCORD_IPC_CPP_SRC_INCLUDE_UTILS_HPP_
