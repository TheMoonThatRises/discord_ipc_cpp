/*
  Copyright 2025 Peter Duanmu

  You should have received a copy of the GNU General Public License along
  with discord_ipc_cpp. If not, see <https://www.gnu.org/licenses/>.
*/

#include <string>
#include <variant>

#include "discord_ipc_cpp/ipc_types.hpp"
#include "discord_ipc_cpp/json.hpp"

namespace discord_ipc_cpp::ipc_types {
using discord_ipc_cpp::json::JSON;
using discord_ipc_cpp::json::JSONObject;
using discord_ipc_cpp::json::JSONArray;

JSON RichPresence::Timestamps::to_json() const {
  JSON base(JSONObject {});

  if (start.has_value()) {
    base["start"] = JSON(start.value());
  }

  if (end.has_value()) {
    base["end"] = JSON(end.value());
  }

  return base;
}

JSON RichPresence::Assets::to_json() const {
  JSON base(JSONObject {});

  if (large_image.has_value()) {
    base["large_image"] = JSON(large_image.value());
  }

  if (large_text.has_value()) {
    base["large_text"] = JSON(large_text.value());
  }

  if (small_image.has_value()) {
    base["small_image"] = JSON(small_image.value());
  }

  if (small_text.has_value()) {
    base["small_text"] = JSON(small_text.value());
  }

  return base;
}

JSON RichPresence::Party::to_json() const {
  JSON base(JSONObject {});

  if (id.has_value()) {
    base["id"] = JSON(id.value());
  }

  if (max.has_value()) {
    base["max"] = JSON(max.value());
  }

  if (size.has_value()) {
    base["size"] = JSON(size.value());
  }

  return base;
}

JSON RichPresence::Secrets::to_json() const {
  JSON base(JSONObject {});

  if (join.has_value()) {
    base["join"] = JSON(join.value());
  }

  if (match.has_value()) {
    base["match"] = JSON(match.value());
  }

  if (join.has_value()) {
    base["spectate"] = JSON(spectate.value());
  }

  return base;
}

JSON RichPresence::Button::to_json() const {
  return JSON(JSONObject {
    { "label", JSON(label) },
    { "url", JSON(url) }
  });
}

JSON RichPresence::to_json() const {
  JSON base(JSONObject {
    { "assets", assets.to_json() },
    { "details", JSON(details) },
    { "instance", JSON(instance) },
    { "party", party.to_json() },
    { "timestamps", timestamps.to_json() }
  });

  if (secrets.has_value()) {
    base["secrets"] = secrets.value().to_json();
  }

  if (buttons.has_value()) {
    auto buttons_val = buttons.value();

    base["buttons"] = JSON(JSONArray {});

    for (const auto& button : buttons_val) {
      base["buttons"].push_back(button.to_json());
    }
  }

  if (type.has_value()) {
    base["type"] = JSON(type.value());
  }

  return base;
}
}  // namespace discord_ipc_cpp::ipc_types
