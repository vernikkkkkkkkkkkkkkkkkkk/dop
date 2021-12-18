
#pragma once

#include "../json/json.hpp"
#include "recipe_step.hpp"

#include <string>
#include <vector>


struct Recipe {
  std::string name;
  std::string description;
  std::vector<RecipeStep> steps;
  std::vector<std::string> dependencies;
};

void to_json(nlohmann::json &j, const Recipe &r) {
  j["name"] = r.name;
  j["description"] = r.description;
  j["steps"] = r.steps;
  j["dependencies"] = r.dependencies;
};

void from_json(const nlohmann::json &j, Recipe &r) {
  j.at("name").get_to(r.name);
  j.at("description").get_to(r.description);
  j.at("steps").get_to(r.steps);
  j.at("dependencies").get_to(r.dependencies);
};
