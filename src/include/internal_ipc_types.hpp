/*
  Copyright 2025 Peter Duanmu

  You should have received a copy of the GNU General Public License along
  with discord_ipc_cpp. If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef DISCORD_IPC_CPP_SRC_INCLUDE_INTERNAL_IPC_TYPES_HPP_
#define DISCORD_IPC_CPP_SRC_INCLUDE_INTERNAL_IPC_TYPES_HPP_

#include <map>
#include <optional>
#include <string>
#include <variant>

#include "discord_ipc_cpp/json.hpp"
#include "discord_ipc_cpp/ipc_types.hpp"

namespace discord_ipc_cpp::internal_ipc_types {
enum JoinReply {
  no,
  yes,
  ignore
};

struct AuthorizationRequest {
  const std::string version;
  const std::string client_id;

 public:
  json::JSON to_json() const;
};

struct CommandRequest {
 public:
  using RequestArgs = std::variant<
    int,
    std::string,
    ipc_types::RichPresence
  >;

  enum CommandType {
    dispatch,
    authorize,
    subscribe,
    setActivity,
    sendActivityJoinInvite,
    closeActivityJoinRequest
  };

  enum EventType {
    error,
    join,
    joinRequest,
    ready,
    spectate
  };

 public:
  const CommandType cmd;
  const std::string nonce;
  const std::optional<std::map<std::string, RequestArgs>> args;
  const std::optional<json::JSON> data;
  const EventType evt;

 public:
  json::JSON to_json() const;
  static CommandRequest from_json(const json::JSON& data);

 private:
  static const std::map<CommandType, std::string> _cmd_str_map;
  static const std::map<EventType, std::string> _evt_str_map;
};

struct PartialUser {
  const std::string avatar;
  const std::string discriminator;
  const std::string user_id;
  const std::string username;

 public:
  static PartialUser from_json(const json::JSON& data);
};
}  // namespace discord_ipc_cpp::internal_ipc_types

#endif  // DISCORD_IPC_CPP_SRC_INCLUDE_INTERNAL_IPC_TYPES_HPP_
