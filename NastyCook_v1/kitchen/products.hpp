
#pragma once

#include "../json/json.hpp"
#include "product.hpp"

#include <string>
#include <vector>

struct Products {
  std::vector<Product> products;
};

void to_json(nlohmann::json &j, const Products &p) {
  j["products"] = p.products;
};

void from_json(const nlohmann::json &j, Products &p) {
  j.at("products").get_to(p.products);
};
