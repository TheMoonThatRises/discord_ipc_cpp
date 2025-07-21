/*
  Copyright 2025 Peter Duanmu

  You should have received a copy of the GNU General Public License along
  with discord_ipc_cpp. If not, see <https://www.gnu.org/licenses/>.
*/

#include <map>
#include <string>

#include "discord_ipc_cpp/json.hpp"

#include "include/internal_ipc_types.hpp"
#include "include/parser.hpp"
#include "include/utils.hpp"

namespace discord_ipc_cpp::internal_ipc_types {
typedef CommandRequest::CommandType CommandType;
typedef CommandRequest::EventType EventType;

using ipc_types::RichPresence;

using json::JSON;
using json::JSONObject;
using json::Parser;

using discord_ipc_cpp::utils::reverse_map_search;

JSON AuthorizationRequest::to_json() const {
  return JSON({
    { "v", JSON(version) },
    { "client_id", JSON(client_id) }
  });
}

const std::map<CommandType, std::string> CommandRequest::_cmd_str_map = {
  { dispatch, "DISPATCH" },
  { authorize, "AUTHORIZE" },
  { subscribe, "SUBSCRIBE" },
  { setActivity, "SET_ACTIVITY" },
  { sendActivityJoinInvite, "SEND_ACTIVITY_JOIN_INVITE" },
  { closeActivityJoinRequest, "CLOSE_ACTIVITY_JOIN_REQUEST" }
};

const std::map<EventType, std::string> CommandRequest::_evt_str_map = {
  { error, "ERROR" },
  { join, "ACTIVITY_JOIN" },
  { joinRequest, "ACTIVITY_JOIN_REQUEST" },
  { ready, "READY" },
  { spectate, "SPECTATE" }
};

JSON CommandRequest::to_json() const {
  JSON base({
    { "cmd", JSON(_cmd_str_map.at(cmd)) },
    { "nonce", JSON(nonce) },
    { "evt", JSON(_evt_str_map.at(evt)) },
    { "args", JSON(JSONObject {}) }
  });

  if (args.has_value()) {
    auto args_val = args.value();

    for (const auto& [key, value] : args_val) {
      if (std::holds_alternative<int>(value)) {
        base["args"][key] = JSON(std::get<int>(value));
      } else if (std::holds_alternative<std::string>(value)) {
        base["args"][key] = JSON(std::get<std::string>(value));
      } else {
        base["args"][key] = std::get<RichPresence>(value).to_json();
      }
    }
  }

  return base;
}

CommandRequest CommandRequest::from_string(const std::string& data) {
  JSON json_data = Parser::parse(data);

  std::optional<JSON> res_data;
  std::optional<std::map<std::string, RequestArgs>> args;

  if (json_data.has("data")) {
    res_data = json_data["data"];
  }

  if (json_data.has("args")) {
    auto& out_args = args.emplace();

    for (const auto& [key, value] : json_data["args"].as<JSONObject>()) {
      out_args[key] = value.to_string();
    }
  }

  return {
    .cmd = *reverse_map_search(
      _cmd_str_map, json_data["cmd"].as<std::string>()),
    .nonce = json_data["nonce"].as<std::string>(),
    .args = args,
    .data = res_data,
    .evt = *reverse_map_search(
      _evt_str_map, json_data["evt"].as<std::string>()),
  };
}

PartialUser PartialUser::from_string(const std::string& data) {
  JSON json_data = Parser::parse(data);

  return {
    .avatar = json_data["avatar"].as<std::string>(),
    .discriminator = json_data["discriminator"].as<std::string>(),
    .user_id = json_data["user_id"].as<std::string>(),
    .username = json_data["username"].as<std::string>()
  };
}
}  // namespace discord_ipc_cpp::internal_ipc_types
