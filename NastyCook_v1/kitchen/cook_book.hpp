
#pragma once

#include "../json/json.hpp"
#include "recipe.hpp"

#include <vector>

struct CookBook {
  std::vector<Recipe> recipes;
};

void to_json(nlohmann::json &j, const CookBook &c) {
  j["recipes"] = c.recipes;
};

void from_json(const nlohmann::json &j, CookBook &c) {
  j.at("recipes").get_to(c.recipes);
};
