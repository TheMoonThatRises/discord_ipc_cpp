/*
  Copyright 2025 Peter Duanmu

  You should have received a copy of the GNU General Public License along
  with discord_ipc_cpp. If not, see <https://www.gnu.org/licenses/>.
*/

#include <poll.h>
#include <sys/socket.h>
#include <unistd.h>

#include <string>
#include <optional>
#include <vector>

#include "discord_ipc_cpp/socket_client.hpp"

namespace discord_ipc_cpp::websockets {
SocketClient::SocketClient(
  const std::string& socket_file)
: _socket_file(socket_file) {
  int opt = 1;

  _client_socket = ::socket(AF_UNIX, SOCK_STREAM, 0);
  setsockopt(_client_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

  std::memset(&_server_addr, 0, sizeof(_server_addr));

  _server_addr.sun_family = AF_UNIX;
  std::strncpy(_server_addr.sun_path,
               _socket_file.c_str(),
               sizeof(_server_addr.sun_path) - 1);

  _fds[0].fd = _client_socket;
  _fds[0].events = POLLIN;
}

SocketClient::~SocketClient() {
  close();
}

bool SocketClient::connect() {
  if (_client_socket < 0) {
    return false;
  }

  int ret = ::connect(_client_socket,
                      reinterpret_cast<const sockaddr*>(&_server_addr),
                      sizeof(sockaddr_un));

  return ret != -1;
}

bool SocketClient::close() {
  if (_client_socket > 0) {
    ::close(_client_socket);

    _client_socket = -1;

    return true;
  } else {
    return false;
  }
}

bool SocketClient::send_data(const std::vector<char>& data) {
  if (_client_socket < 0) {
    return false;
  }

  int ret = ::send(_client_socket, data.data(), data.size(), 0);

  return ret != -1;
}

std::optional<std::vector<char>> SocketClient::recv_data(int buffer_size) {
  std::vector<char> buffer(buffer_size);

  int ret = ::recv(_client_socket, buffer.data(), buffer.size(), 0);

  if (ret == -1) {
    return std::nullopt;
  }

  return buffer;
}

std::optional<std::vector<char>> SocketClient::recv_data(
  int buffer_size, int timeout
) {
  int ret = ::poll(_fds, 1, timeout);

  if (ret > 0 && _fds[0].revents & POLLIN) {
    return recv_data(buffer_size);
  } else {
    return std::nullopt;
  }
}
}  // namespace discord_ipc_cpp::websockets
