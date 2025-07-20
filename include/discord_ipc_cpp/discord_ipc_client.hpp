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
#include "discord_ipc_cpp/json.hpp"
#include "discord_ipc_cpp/ipc_types.hpp"

namespace discord_ipc_cpp {
class DiscordIPCClient {
 private:
  const pid_t _pid;
  std::string _client_id;

  websockets::SocketClient _socket;
  std::thread _socket_recv_thread;

  std::atomic_bool _stop_recv_thread;

 private:
  static std::vector<char> encode_packet(const ipc_types::IPCPayload& payload);
  void recv_thread();

 protected:
  bool send_packet(const ipc_types::IPCPayload& payload);
  std::optional<ipc_types::IPCPayload> recv_packet();

 public:
  explicit DiscordIPCClient(const std::string& client_id);
  ~DiscordIPCClient();

  bool connect();
  bool close();
};
}  // namespace discord_ipc_cpp

#endif  // DISCORD_IPC_CPP_INCLUDE_DISCORD_IPC_CPP_DISCORD_IPC_CLIENT_HPP_
