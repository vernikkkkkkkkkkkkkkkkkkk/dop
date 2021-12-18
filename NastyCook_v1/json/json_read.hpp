
#pragma once

#include "json.hpp"
#include "../kitchen/products.hpp"
#include "../kitchen/fridge.hpp"
#include "../kitchen/cook_book.hpp"

#include <fstream>

void json_read(Products &prods, Fridge &fridge, CookBook &cook_book) {
  nlohmann::json j;

  std::ifstream in_prod("products.json");
  in_prod >> j;
  prods = j.get<Products>();

  std::ifstream in_fridge("fridge.json");
  in_fridge >> j;
  fridge = j.get<Fridge>();

  std::ifstream in_cook_book("cook_book.json");
  in_cook_book >> j;
  cook_book = j.get<CookBook>();
}
