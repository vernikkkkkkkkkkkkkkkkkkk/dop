
#pragma once

#include "../json/json.hpp"
#include "fridge_item.hpp"

#include <string>
#include <vector>

struct RecipeStep {
  std::vector<FridgeItem> items;
  std::string action;
};

void to_json(nlohmann::json &j, const RecipeStep &s) {
  j["items"] = s.items;
  j["action"] = s.action;
};

void from_json(const nlohmann::json &j, RecipeStep &s) {
  j.at("items").get_to(s.items);
  j.at("action").get_to(s.action);
};
