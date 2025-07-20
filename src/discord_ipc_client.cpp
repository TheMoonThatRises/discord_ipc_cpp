/*
  Copyright 2025 Peter Duanmu

  You should have received a copy of the GNU General Public License along
  with discord_ipc_cpp. If not, see <https://www.gnu.org/licenses/>.
*/

#include <unistd.h>

#include <thread>
#include <string>
#include <optional>
#include <vector>
#include <iostream>

#include "discord_ipc_cpp/discord_ipc_client.hpp"
#include "discord_ipc_cpp/socket_client.hpp"
#include "discord_ipc_cpp/json.hpp"

#include "include/utils.hpp"
#include "include/parser.hpp"

using discord_ipc_cpp::json::JSON;
using discord_ipc_cpp::json::JSONObject;
using discord_ipc_cpp::json::Parser;
using discord_ipc_cpp::ipc_types::IPCOpcodes;
using discord_ipc_cpp::ipc_types::IPCPayload;

namespace discord_ipc_cpp {
std::vector<char> DiscordIPCClient::encode_packet(
  const IPCPayload& payload
) {
  std::string data = payload.payload.to_string();
  int data_len = data.size();

  std::vector<char> packet(8 + data_len);

  std::memcpy(&packet[0], &payload.opcode, 4);
  std::memcpy(&packet[4], &data_len, 4);
  std::memcpy(&packet[8], data.data(), data_len);

  return packet;
}

void DiscordIPCClient::recv_thread() {
  while (!_stop_recv_thread) {
    auto optional_payload = recv_packet();

    if (!optional_payload.has_value()) {
      continue;
    }

    IPCPayload recv_payload = optional_payload.value();

    std::cout << recv_payload.opcode << std::endl;
    std::cout << recv_payload.payload.to_string() << std::endl;

    switch (recv_payload.opcode) {
      case IPCOpcodes::ping:
        send_packet({ IPCOpcodes::pong, recv_payload.payload });

        break;
      case IPCOpcodes::frame: {
        if (recv_payload.payload["cmd"].as<std::string>() == "DISPATCH") {
          JSON activity = JSON();

          activity["cmd"] = JSON("SET_ACTIVITY");
          activity["args"] = JSON({
            {"pid", JSON(_pid)},
            {"activity", JSON({
              {"state", JSON("test state")},
              {"details", JSON("test details")}
            })}
          });
          activity["nonce"] = JSON(utils::generate_uuid());

          send_packet({ IPCOpcodes::frame, activity });
        }
        break;
      }
      case IPCOpcodes::close:
        close();

        break;
      default:
        break;
    }
  }

  std::cout << "socket connection closed" << std::endl;
}

DiscordIPCClient::DiscordIPCClient(const std::string& client_id)
: _pid(getpid()),
_client_id(client_id),
_socket(utils::find_discord_ipc_file()),
_stop_recv_thread(false) {}

DiscordIPCClient::~DiscordIPCClient() {
  close();
}

bool DiscordIPCClient::send_packet(const IPCPayload& payload) {
  std::vector<char> packet = encode_packet(payload);

  return _socket.send_data(packet);
}

std::optional<IPCPayload> DiscordIPCClient::recv_packet() {
  int opcode, data_len;
  std::string data;
  std::vector<char> opcode_buffer(4), data_len_buffer(4), buffer;

  auto poll_buffer = _socket.recv_data(4, 1000);

  if (!poll_buffer.has_value()) {
    return {};
  }

  opcode_buffer = poll_buffer.value();

  data_len_buffer = _socket.recv_data(4).value();

  std::memcpy(&opcode, opcode_buffer.data(), opcode_buffer.size());
  std::memcpy(&data_len, data_len_buffer.data(), data_len_buffer.size());

  buffer.resize(data_len);

  buffer = _socket.recv_data(data_len).value();

  data = std::string(buffer.begin(), buffer.end());

  return IPCPayload {
    static_cast<IPCOpcodes>(opcode),
    Parser::parse(data)
  };
}

bool DiscordIPCClient::connect() {
  bool ret = _socket.connect();

  if (!ret) {
    return false;
  }

  ret = send_packet({
    IPCOpcodes::handshake,
    JSON({
      {"v", JSON(1)},
      {"client_id", JSON(_client_id)}
    })
  });

  if (!ret) {
    return false;
  }

  _socket_recv_thread = std::thread { &DiscordIPCClient::recv_thread, this };

  struct sched_param sch_params;
  sch_params.sched_priority = 0;

  pthread_setschedparam(
    _socket_recv_thread.native_handle(), SCHED_OTHER, &sch_params);

  _socket_recv_thread.detach();

  return true;
}

bool DiscordIPCClient::close() {
  send_packet({ IPCOpcodes::close, {} });

  _stop_recv_thread = true;

  std::this_thread::sleep_for(std::chrono::milliseconds(1000));

  return _socket.close();
}
}  // namespace discord_ipc_cpp
