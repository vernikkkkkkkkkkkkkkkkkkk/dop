
#pragma once

#include "../json/json.hpp"
#include "fridge_item.hpp"

#include <string>
#include <vector>

struct Fridge {
  std::vector<FridgeItem> items;
};

void to_json(nlohmann::json &j, const Fridge &f) {
  j["items"] = f.items;
};

void from_json(const nlohmann::json &j, Fridge &f) {
  j.at("items").get_to(f.items);
};
