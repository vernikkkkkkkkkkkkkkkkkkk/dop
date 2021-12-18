
#pragma once

#include "json.hpp"
#include "../kitchen/product.hpp"
#include "../kitchen/products.hpp"
#include "../kitchen/fridge_item.hpp"
#include "../kitchen/fridge.hpp"
#include "../kitchen/recipe_step.hpp"
#include "../kitchen/recipe.hpp"
#include "../kitchen/cook_book.hpp"

#include <iostream>
#include <fstream>
#include <iomanip>

bool file_exists(const std::string& name) {
  std::ifstream f(name.c_str());
  return f.good();
}

void json_products_generator(const std::string& product_filename) {
  if (!file_exists(product_filename)) {
    Product p1, p2, p3, p4, p5, p6;
    p1.name = "prod1";
    p2.name = "prod2";
    p3.name = "prod3";
    p4.name = "prod4";
    p5.name = "prod5";
    p6.name = "prod6";
    p1.synonyms = {p2.name, p3.name};
    p2.synonyms = {p1.name, p3.name};
    p3.synonyms = {p1.name, p2.name};
    p4.synonyms = {p5.name};
    p5.synonyms = {p4.name};
    p6.synonyms = {};
    Products prods;
    prods.products = {p1, p2, p3, p4, p5, p6};
    nlohmann::json j = prods;
    // write products to file
    std::ofstream out_prod(product_filename);
    out_prod << std::setw(2) << j << std::endl;
  }
}

void json_fridge_generator(const std::string& fridge_filename) {
  if (!file_exists(fridge_filename)) {
    FridgeItem item1 = {"prod1", 100};
    FridgeItem item2 = {"prod2", 100};
    FridgeItem item3 = {"prod3", 0};
    FridgeItem item4 = {"prod4", 100};
    FridgeItem item5 = {"prod5", 100};
    FridgeItem item6 = {"prod6", 100};
    Fridge fridge;
    fridge.items = {item1, item2, item3, item4, item5, item6};
    nlohmann::json j = fridge;
    // write fridge to file
    std::ofstream out_fridge(fridge_filename);
    out_fridge << std::setw(2) << j << std::endl;
  }
}

void json_cook_book_generator(const std::string& cook_book_filename) {
  if (!file_exists(cook_book_filename))
  {
    RecipeStep step1 = {{{"prod1", 10}, {"prod2", 20}, {"prod3", 30}}, "action1"};
    RecipeStep step2 = {{{"prod1", 10}, {"prod4", 40}, {"prod5", 50}}, "action2"};
    RecipeStep step3 = {{{"prod3", 30}}, "action3"};
    RecipeStep step4 = {{{"prod3", 30}, {"prod6", 60}}, "action4"};
    RecipeStep step5 = {{{"prod1", 10}, {"prod2", 20}, {"prod3", 30}, {"prod6", 60}}, "action5"};
    Recipe recipe1 = {"recipe1", "tasty", {step1}, {}};
    Recipe recipe2 = {"recipe2", "very tasty", {step2}, {}};
    Recipe recipe3 = {"recipe3", "great", {step3}, {"recipe1"}};
    Recipe recipe4 = {"recipe4", "so-so", {step1, step2, step3}, {}};
    Recipe recipe5 = {"recipe5", "perfect", {step4}, {"recipe1", "recipe3"}};
    CookBook cook_book;
    cook_book.recipes = {recipe1, recipe2, recipe3, recipe4, recipe5};
    nlohmann::json j = cook_book;
    // write cook book to file
    std::ofstream out_cook_book(cook_book_filename);
    out_cook_book << std::setw(2) << j << std::endl;
  }
}

