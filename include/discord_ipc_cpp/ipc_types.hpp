/*
  Copyright 2025 Peter Duanmu

  You should have received a copy of the GNU General Public License along
  with discord_ipc_cpp. If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef DISCORD_IPC_CPP_INCLUDE_DISCORD_IPC_CPP_IPC_TYPES_HPP_
#define DISCORD_IPC_CPP_INCLUDE_DISCORD_IPC_CPP_IPC_TYPES_HPP_

namespace discord_ipc_cpp::ipc_types {
enum IPCOpcodes : int {
  handshake = 0,
  frame = 1,
  close = 2,
  ping = 3,
  pong = 4
};

struct IPCPayload {
  const IPCOpcodes opcode;
  const json::JSON payload;
};
}  // namespace discord_ipc_cpp::ipc_types

#endif  // DISCORD_IPC_CPP_INCLUDE_DISCORD_IPC_CPP_IPC_TYPES_HPP_
