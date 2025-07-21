/*
  Copyright 2025 Peter Duanmu

  You should have received a copy of the GNU General Public License along
  with discord_ipc_cpp. If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef DISCORD_IPC_CPP_INCLUDE_DISCORD_IPC_CPP_DISCORD_IPC_CLIENT_HPP_
#define DISCORD_IPC_CPP_INCLUDE_DISCORD_IPC_CPP_DISCORD_IPC_CLIENT_HPP_

#include <thread>
#include <string>
#include <optional>
#include <vector>

#include "discord_ipc_cpp/socket_client.hpp"
#include "discord_ipc_cpp/ipc_types.hpp"
#include "discord_ipc_cpp/json.hpp"

namespace discord_ipc_cpp {
class DiscordIPCClient {
 private:
  const pid_t _pid;
  std::string _client_id;

  websockets::SocketClient _socket;
  std::thread _socket_recv_thread;

  std::atomic_bool _stop_recv_thread;
  std::atomic_bool _successful_auth;

 private:
  static std::vector<char> encode_packet(const ipc_types::Payload& payload);
  void recv_thread();

 protected:
  bool send_packet(const ipc_types::Payload& payload);
  std::optional<ipc_types::Payload> recv_packet();

  ipc_types::Payload construct_presence_payload(
    const ipc_types::RichPresence& presence);

  bool attempt_send_payload(
    const ipc_types::Payload& payload, int max_retry_count);

 public:
  explicit DiscordIPCClient(const std::string& client_id);
  ~DiscordIPCClient();

  bool connect();
  bool close();

  bool set_presence(const ipc_types::RichPresence& presence);
  bool set_empty_presence();
};
}  // namespace discord_ipc_cpp

#endif  // DISCORD_IPC_CPP_INCLUDE_DISCORD_IPC_CPP_DISCORD_IPC_CLIENT_HPP_
