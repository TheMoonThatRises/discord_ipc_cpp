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

using discord_ipc_cpp::websockets::SocketClient;
using discord_ipc_cpp::json::JSON;

namespace discord_ipc_cpp {
enum IPCOpcodes : int {
  handshake = 0,
  frame = 1,
  close = 2,
  ping = 3,
  pong = 4
};

struct IPCPayload {
  const IPCOpcodes opcode;
  const JSON payload;
};

class DiscordIPCClient {
 private:
  const pid_t _pid;
  std::string _client_id;

  SocketClient _socket;
  std::thread _socket_recv_thread;

  std::atomic_bool _stop_recv_thread;

 private:
  static std::vector<char> encode_packet(const struct IPCPayload& payload);
  void recv_thread();

 protected:
  bool send_packet(const struct IPCPayload& payload);
  std::optional<IPCPayload> recv_packet();

 public:
  explicit DiscordIPCClient(const std::string& client_id);
  ~DiscordIPCClient();

  bool connect();
  bool close();
};
}  // namespace discord_ipc_cpp

#endif  // DISCORD_IPC_CPP_INCLUDE_DISCORD_IPC_CPP_DISCORD_IPC_CLIENT_HPP_
