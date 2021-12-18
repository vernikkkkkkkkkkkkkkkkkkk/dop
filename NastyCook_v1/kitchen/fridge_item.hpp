
#pragma once

#include "../json/json.hpp"
#include <string>

struct FridgeItem {
  std::string product_name;
  int amount;
};

void to_json(nlohmann::json &j, const FridgeItem &item) {
  j["product_name"] = item.product_name;
  j["amount"] = item.amount;
};

void from_json(const nlohmann::json &j, FridgeItem &item) {
  j.at("product_name").get_to(item.product_name);
  j.at("amount").get_to(item.amount);
};
