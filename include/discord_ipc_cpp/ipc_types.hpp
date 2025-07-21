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
  handshake = 0,
  frame = 1,
  close = 2,
  ping = 3,
  pong = 4
};

struct Payload {
  const Opcode opcode;
  const json::JSON payload;
};

struct RichPresence {
 public:
  struct Timestamps {
    std::optional<long> start;
    std::optional<long> end;

   private:
      json::JSON to_json() const;

      friend struct RichPresence;
  };

  struct Assets {
    std::optional<std::string> large_image;
    std::optional<std::string> large_text;
    std::optional<std::string> small_image;
    std::optional<std::string> small_text;

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

  enum ActivityType : int {
    game = 0,
    streaming = 1,
    listening = 2,
    watching = 3,
    custom = 4,
    competing = 5
  };

 public:
  Assets assets {};
  std::string details {};
  bool instance { true };
  Party party {};
  std::optional<Secrets> secrets { std::nullopt };
  std::string state {};
  Timestamps timestamps {};
  std::optional<std::vector<Button>> buttons { std::nullopt };
  std::optional<ActivityType> type { std::nullopt };

 public:
  json::JSON to_json() const;
};
}  // namespace discord_ipc_cpp::ipc_types

#endif  // DISCORD_IPC_CPP_INCLUDE_DISCORD_IPC_CPP_IPC_TYPES_HPP_
