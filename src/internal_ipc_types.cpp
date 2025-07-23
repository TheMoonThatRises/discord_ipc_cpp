/*
  Copyright 2025 Peter Duanmu

  You should have received a copy of the GNU General Public License along
  with discord_ipc_cpp. If not, see <https://www.gnu.org/licenses/>.
*/

#include <map>
#include <string>

#include "discord_ipc_cpp/json.hpp"
#include "discord_ipc_cpp/parser.hpp"

#include "include/internal_ipc_types.hpp"
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
  { ct_dispatch, "DISPATCH" },
  { ct_authorize, "AUTHORIZE" },
  { ct_subscribe, "SUBSCRIBE" },
  { ct_set_activity, "SET_ACTIVITY" },
  { ct_send_activity_join_invite, "SEND_ACTIVITY_JOIN_INVITE" },
  { ct_close_activity_join_request, "CLOSE_ACTIVITY_JOIN_REQUEST" }
};

const std::map<EventType, std::string> CommandRequest::_evt_str_map = {
  { et_error, "ERROR" },
  { et_join, "ACTIVITY_JOIN" },
  { et_joinRequest, "ACTIVITY_JOIN_REQUEST" },
  { et_ready, "READY" },
  { et_spectate, "SPECTATE" }
};

JSON CommandRequest::to_json() const {
  JSON base({
    { "cmd", JSON(_cmd_str_map.at(cmd)) },
    { "args", JSON(JSONObject {}) }
  });

  if (evt.has_value()) {
    base["evt"] = JSON(_evt_str_map.at(evt.value()));
  }

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

  if (nonce.has_value()) {
    base["nonce"] = JSON(nonce.value());
  } else {
    base["nonce"] = JSON(nullptr);
  }

  return base;
}

CommandRequest CommandRequest::from_json(const JSON& data) {
  std::optional<JSON> res_data;
  std::optional<std::map<std::string, RequestArgs>> args;
  std::optional<std::string> nonce;
  std::optional<EventType> evt;

  if (data.has("data")) {
    res_data = data["data"];
  }

  if (data.has("args")) {
    auto& out_args = args.emplace();

    for (const auto& [key, value] : data["args"].as<JSONObject>()) {
      out_args[key] = value.to_string();
    }
  }

  if (data.has("nonce") && data["nonce"].is<std::string>()) {
    nonce = data["nonce"].as<std::string>();
  }

  if (data.has("evt") && data["evt"].is<std::string>()) {
    evt = *reverse_map_search(_evt_str_map, data["evt"].as<std::string>());
  }

  return {
    .cmd = *reverse_map_search(_cmd_str_map, data["cmd"].as<std::string>()),
    .nonce = nonce,
    .args = args,
    .data = res_data,
    .evt = evt,
  };
}

PartialUser PartialUser::from_json(const JSON& data) {
  return {
    .avatar = data["avatar"].as<std::string>(),
    .discriminator = data["discriminator"].as<std::string>(),
    .user_id = data["user_id"].as<std::string>(),
    .username = data["username"].as<std::string>()
  };
}
}  // namespace discord_ipc_cpp::internal_ipc_types
