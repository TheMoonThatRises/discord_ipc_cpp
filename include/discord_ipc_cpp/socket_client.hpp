/*
  Copyright 2025 Peter Duanmu

  You should have received a copy of the GNU General Public License along
  with discord_ipc_cpp. If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef DISCORD_IPC_CPP_INCLUDE_DISCORD_IPC_CPP_SOCKET_CLIENT_HPP_
#define DISCORD_IPC_CPP_INCLUDE_DISCORD_IPC_CPP_SOCKET_CLIENT_HPP_

#include <poll.h>
#include <sys/socket.h>
#include <sys/un.h>

#include <string>
#include <optional>
#include <vector>

namespace discord_ipc_cpp::websockets {
class SocketClient {
 private:
    std::string _socket_file;

    int _client_socket;
    struct sockaddr_un _server_addr;

    struct pollfd _fds[1];

 public:
    explicit SocketClient(const std::string& socket_file);
    ~SocketClient();

    bool connect();
    bool close();

    bool send_data(const std::vector<char>& data);
    std::optional<std::vector<char>> recv_data(int buffer_size);
    std::optional<std::vector<char>> recv_data(int buffer_size, int timeout);
};
}  // namespace discord_ipc_cpp::websockets

#endif  // DISCORD_IPC_CPP_INCLUDE_DISCORD_IPC_CPP_SOCKET_CLIENT_HPP_
