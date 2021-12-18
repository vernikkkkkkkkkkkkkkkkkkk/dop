
#pragma once

#include "json/json.hpp"
#include "kitchen/cook_book.hpp"

#include <map>
#include <string>
#include <vector>

struct Replacement {
  std::string orig_product;
  std::string select_product;
};

struct ModifiedRecipe {
  std::string recipe_name;
  std::vector<Replacement> replacements;
};

void add_map(std::map<std::string, int> &orig, const std::map<std::string, int> &adder) {
  for (const auto &item: adder) {
    auto it = orig.find(item.first);
    if (it == orig.end())
      orig[item.first] = item.second;
    else
      it->second += item.second;
  }
}

void add_array(std::map<std::string, int> &orig, const std::vector<FridgeItem> &adder) {
  for (const auto &item: adder) {
    auto it = orig.find(item.product_name);
    if (it == orig.end())
      orig[item.product_name] = item.amount;
    else
      it->second += item.amount;
  }
}

bool do_exclude(const std::string &orig, const std::vector<std::string> &excludes) {
  bool do_exclude = false;
  for (const auto &exclude: excludes) {
    if (orig == exclude) {
      do_exclude = true;
      break;
    }
  }
  return do_exclude;
}

void exclude_filter(const std::vector<std::string> &origs, const std::vector<std::string> &excludes,
                    std::vector<std::string> &result) {
  for (const auto &orig: origs) {
    if (!do_exclude(orig, excludes))
      result.push_back(orig);
  }
}

void transform(const CookBook &cook_book, std::map<std::string, std::map<std::string, int> > &result) {
  // просматриваем рецепты без учета зависимостей
  for (const auto &recipe: cook_book.recipes) {
    std::map<std::string, int> prods_from_recipe;
    // просматриваем шаги в рецепте
    for (const auto &step: recipe.steps) {
      // добавляем продукты из шага
      add_array(prods_from_recipe, step.items);
    }
    result[recipe.name] = prods_from_recipe;
  }

  // просматриваем зависимые рецепты
  // Важно учитываются зависимости только первого уровня
  std::map<std::string, std::map<std::string, int> > dep_recipes;
  for (const auto &recipe: cook_book.recipes) {
    std::map<std::string, int> prods_from_dependence;
    for (const auto &depend: recipe.dependencies) {
      if (depend == recipe.name)
        throw std::runtime_error("Рецепт зависит от самого себя. Провертье " + recipe.name);
      // добавляем продукты из зависимости
      add_map(prods_from_dependence, result[depend]);
      dep_recipes[recipe.name] = prods_from_dependence;
    }
  }
  // суммируем продукты
  for (const auto &recipe: cook_book.recipes) {
    add_map(result[recipe.name], dep_recipes[recipe.name]);
  }
}
