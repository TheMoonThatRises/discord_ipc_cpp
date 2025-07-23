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

JSON RichPresence::ActivityEmoji::to_json() const {
  JSON base(JSONObject {
    { "name", JSON(name) }
  });

  if (snowflake.has_value()) {
    base["snowflake"] = JSON(snowflake.value());
  }

  if (animated.has_value()) {
    base["animated"] = JSON(animated.value());
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

JSON RichPresence::Assets::to_json() const {
  JSON base(JSONObject {});

  if (large_image.has_value()) {
    base["large_image"] = JSON(large_image.value());
  }

  if (large_text.has_value()) {
    base["large_text"] = JSON(large_text.value());
  }

  if (large_url.has_value()) {
    base["large_url"] = JSON(large_url.value());
  }

  if (small_image.has_value()) {
    base["small_image"] = JSON(small_image.value());
  }

  if (small_text.has_value()) {
    base["small_text"] = JSON(small_text.value());
  }

  if (small_url.has_value()) {
    base["small_url"] = JSON(small_url.value());
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
    { "name", JSON(name) },
    { "type", JSON(type) }
  });

  if (url.has_value()) {
    base["url"] = JSON(url.value());
  }

  if (created_at.has_value()) {
    base["created_at"] = JSON(created_at.value());
  }

  if (timestamps.has_value()) {
    base["timestamps"] = timestamps.value().to_json();
  }

  if (application_id.has_value()) {
    base["application_id"] = JSON(application_id.value());
  }

  if (status_display_type.has_value()) {
    base["status_display_type"] = JSON(status_display_type.value());
  }

  if (details.has_value()) {
    base["details"] = JSON(details.value());
  }

  if (details_url.has_value()) {
    base["details_url"] = JSON(details_url.value());
  }

  if (state.has_value()) {
    base["state"] = JSON(state.value());
  }

  if (state_url.has_value()) {
    base["state_url"] = JSON(state_url.value());
  }

  if (emoji.has_value()) {
    base["emoji"] = emoji.value().to_json();
  }

  if (party.has_value()) {
    base["party"] = party.value().to_json();
  }

  if (assets.has_value()) {
    base["assets"] = assets.value().to_json();
  }

  if (secrets.has_value()) {
    base["secrets"] = secrets.value().to_json();
  }

  if (instance.has_value()) {
    base["instance"] = JSON(instance.value());
  }

  if (flags.has_value()) {
    base["flags"] = JSON(flags.value());
  }

  if (buttons.has_value()) {
    auto buttons_val = buttons.value();

    base["buttons"] = JSON(JSONArray {});

    for (const auto& button : buttons_val) {
      base["buttons"].push_back(button.to_json());
    }
  }

  return base;
}
}  // namespace discord_ipc_cpp::ipc_types
