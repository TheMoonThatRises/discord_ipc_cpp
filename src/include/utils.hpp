/*
  Copyright 2025 Peter Duanmu

  You should have received a copy of the GNU General Public License along
  with discord_ipc_cpp. If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef DISCORD_IPC_CPP_SRC_INCLUDE_UTILS_HPP_
#define DISCORD_IPC_CPP_SRC_INCLUDE_UTILS_HPP_

#include <map>
#include <string>
#include <vector>

namespace discord_ipc_cpp::utils {
extern const std::map<std::string, std::string> _escape_key;

std::string find_discord_ipc_file();

std::string unescape_string(const std::string& input);
std::string escape_string(const std::string& input);

template<typename T>
T generate_random_num(T min, T max);

std::string generate_uuid();

template<typename A, typename B>
A reverse_map_search(const std::map<A, B>& map, const B& item);
}  // namespace discord_ipc_cpp::utils

#endif  // DISCORD_IPC_CPP_SRC_INCLUDE_UTILS_HPP_
