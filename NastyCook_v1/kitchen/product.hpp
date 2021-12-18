
#pragma once

#include "../json/json.hpp"

#include <string>
#include <vector>


struct Product {
  std::string name;
  std::vector<std::string> synonyms;
};

void to_json(nlohmann::json &j, const Product &p) {
  j["name"] = p.name;
  j["synonyms"] = p.synonyms;
};

void from_json(const nlohmann::json &j, Product &p) {
  j.at("name").get_to(p.name);
  j.at("synonyms").get_to(p.synonyms);
};
