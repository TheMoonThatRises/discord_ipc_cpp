/*
  Copyright 2026 Peter Duanmu

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

/**
 * \namespace discord_ipc_cpp::internal_ipc_types
 *
 * \brief Internal IPC enumerators and structures.
 *
 * These should only be used within the library, as it would not be entirely
 * useful to expose these to the user.
 */
namespace discord_ipc_cpp::internal_ipc_types {
enum JoinReply {
  jr_no,
  jr_yes,
  jr_ignore
};

/**
 * \brief Utility structure to send authorization requests.
 */
struct AuthorizationRequest {
  /**
   * \brief IPC socket API version.
   */
  const std::string version;
  /**
   * \brief ID of the application sending requests.
   */
  const std::string client_id;

 public:
  /**
    * \brief Converts the struct into a JSON.
    *
    * \return JSON representation of the struct.
    *
    * \see discord_ipc_cpp::json::JSON
    */
  json::JSON to_json() const;
};

/**
 * \brief Requests sent and received by the IPC client.
 */
struct CommandRequest {
 public:
  /**
   * \brief Sending request contains arguments of these types.
   */
  using RequestArgs = std::variant<
    int,
    std::string,
    ipc_types::RichPresence
  >;

  /**
   * Commands made by the client to the IPC socket.
   */
  enum CommandType {
    ct_dispatch,                    ///< Event dispatched
    ct_authorize,                   ///< Authorize a new client app
    ct_subscribe,                   ///< Subscribe to an RPC event
    ct_set_activity,                ///< Update user's rich presence
    ct_send_activity_join_invite,   ///< Consent to "Ask to Join" request
    ct_close_activity_join_request  ///< Reject "Ask to Join" request
  };

  /**
   * Events that can be sent from the IPC socket.
   */
  enum EventType {
    et_error,         ///< Sent when there is an error
    et_join,          ///< When user clicks presence join invite in chat
    et_join_request,  ///< When user receives "Ask to Join" request
    et_ready,         ///< Sent immediately after connecting
    et_spectate       ///< When user clicks presence spectate invite in chat
  };

 public:
  // cppcheck-suppress uninitMemberVarNoCtor
  const CommandType cmd;
  const std::optional<std::string> nonce;
  const std::optional<std::map<std::string, RequestArgs>> args;
  const std::optional<json::JSON> data;
  const std::optional<EventType> evt;

 public:
  /**
    * \brief Converts the struct into a JSON.
    *
    * \return JSON representation of the struct.
    *
    * \see discord_ipc_cpp::json::JSON
    */
  json::JSON to_json() const;
  /**
   * \brief Converts JSON data into the parent struct, \ref CommandRequest.
   *
   * \param data JSON data to convert.
   *
   * \return The data in the form of the parent struct.
   */
  static CommandRequest from_json(const json::JSON& data);

 private:
  /**
   * \brief Map of the specific CommandTypes to their string counterpart.
   */
  static const std::map<CommandType, std::string> _cmd_str_map;
  /**
   * \brief Map of the specific EventTypes to their string counterpart.
   */
  static const std::map<EventType, std::string> _evt_str_map;
};

struct PartialUser {
  const std::string avatar;
  const std::string discriminator;
  const std::string user_id;
  const std::string username;

 public:
  /**
   * \brief Converts JSON data into the parent struct, \ref PartialUser.
   *
   * \param data JSON data to convert.
   *
   * \return The data in the form of the parent struct.
   */
  static PartialUser from_json(const json::JSON& data);
};
}  // namespace discord_ipc_cpp::internal_ipc_types

#endif  // DISCORD_IPC_CPP_SRC_INCLUDE_INTERNAL_IPC_TYPES_HPP_
