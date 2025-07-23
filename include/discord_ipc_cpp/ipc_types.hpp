/*
  Copyright 2025 Peter Duanmu

  You should have received a copy of the GNU General Public License along
  with discord_ipc_cpp. If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef DISCORD_IPC_CPP_INCLUDE_DISCORD_IPC_CPP_IPC_TYPES_HPP_
#define DISCORD_IPC_CPP_INCLUDE_DISCORD_IPC_CPP_IPC_TYPES_HPP_

#include <optional>
#include <string>
#include <vector>

#include "discord_ipc_cpp/json.hpp"

namespace discord_ipc_cpp::ipc_types {
enum Opcode : int {
  op_handshake = 0,
  op_frame = 1,
  op_close = 2,
  op_ping = 3,
  op_pong = 4
};

struct Payload {
  const Opcode opcode;
  const json::JSON payload;
};

struct RichPresence {
 public:
  struct Timestamps {
    std::optional<int> start;
    std::optional<int> end;

   private:
      json::JSON to_json() const;

      friend struct RichPresence;
  };

  struct ActivityEmoji {
    std::string name;
    std::optional<std::string> snowflake;
    std::optional<bool> animated;

   private:
    json::JSON to_json() const;

    friend struct RichPresence;
  };

  struct Party {
    std::optional<std::string> id;
    std::optional<int> max;
    std::optional<int> size;

   private:
      json::JSON to_json() const;

      friend struct RichPresence;
  };

  struct Assets {
    std::optional<std::string> large_image;
    std::optional<std::string> large_text;
    std::optional<std::string> large_url;
    std::optional<std::string> small_image;
    std::optional<std::string> small_text;
    std::optional<std::string> small_url;

   private:
      json::JSON to_json() const;

      friend struct RichPresence;
  };

  struct Secrets {
    std::optional<std::string> join;
    std::optional<std::string> match;
    std::optional<std::string> spectate;

   private:
      json::JSON to_json() const;

      friend struct RichPresence;
  };

  struct Button {
    std::string label;
    std::string url;

   private:
      json::JSON to_json() const;

      friend struct RichPresence;
  };

  enum StatusDisplayType : int {
    sdt_name = 0,
    sdt_state = 1,
    sdt_details = 2
  };

  enum ActivityType : int {
    at_game = 0,
    at_streaming = 1,
    at_listening = 2,
    at_watching = 3,
    at_custom = 4,
    at_competing = 5
  };

 public:
  std::string name {};
  ActivityType type {};
  std::optional<std::string> url { std::nullopt };
  std::optional<int64_t> created_at { std::nullopt };
  std::optional<Timestamps> timestamps { std::nullopt };
  std::optional<std::string> application_id { std::nullopt };
  std::optional<StatusDisplayType> status_display_type { std::nullopt };
  std::optional<std::string> details { std::nullopt };
  std::optional<std::string> details_url { std::nullopt };
  std::optional<std::string> state { std::nullopt };
  std::optional<std::string> state_url { std::nullopt };
  std::optional<ActivityEmoji> emoji { std::nullopt };
  std::optional<Party> party { std::nullopt };
  std::optional<Assets> assets { std::nullopt };
  std::optional<Secrets> secrets { std::nullopt };
  std::optional<bool> instance { std::nullopt };
  std::optional<int64_t> flags { std::nullopt };
  std::optional<std::vector<Button>> buttons { std::nullopt };

 public:
  json::JSON to_json() const;
};
}  // namespace discord_ipc_cpp::ipc_types

#endif  // DISCORD_IPC_CPP_INCLUDE_DISCORD_IPC_CPP_IPC_TYPES_HPP_
