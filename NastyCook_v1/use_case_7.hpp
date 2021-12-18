
#pragma once

#include "kitchen/products.hpp"
#include "kitchen/fridge.hpp"
#include "utils.hpp"

#include <map>
#include <vector>

// 7.	При выборе рецептов учитывается на что есть аллергия у пользователя

void use_case_7(const Fridge &fridge, const Products &products, const std::vector<std::string> &allergic_products,
                const std::map<std::string, std::map<std::string, int> > &recipes,
                std::vector<std::string> &orig_recipes, std::vector<ModifiedRecipe> &modified_recipes) {
  // берем из холодильника продукты
  std::map<std::string, int> prods_from_fridge;
  for (const auto &prod: products.products) {
    prods_from_fridge[prod.name] = 0;
  }
  for (const auto &item: fridge.items) {
    if (!do_exclude(item.product_name, allergic_products)) {
      prods_from_fridge[item.product_name] += item.amount;
    }
  }
  // берем заменители исключая аллергенные продукты
  std::map<std::string, std::vector<std::string> > prods_synonyms;
  for (const auto &item: products.products) {
    std::vector<std::string> synonyms_without_allergic;
    exclude_filter(item.synonyms, allergic_products, synonyms_without_allergic);
    prods_synonyms[item.name] = synonyms_without_allergic;
  }

  enum Status {
    OK, HALF, NO
  };

  // сравниваем продукты из холодилька и рецепттов
  for (const auto &recipe: recipes) {
    Status status = OK;
    std::vector<Replacement> replacements;
    for (auto prod: recipe.second) {
      auto it = prods_from_fridge.find(prod.first);
      if ((it == prods_from_fridge.end()) || (it->second < prod.second)) {
        // нет продукта в холодильнике или его недостаточно - смотрим заменители
        status = NO;
        for (auto syn_product: prods_synonyms[prod.first]) {
          auto syn_it = prods_from_fridge.find(syn_product);
          if ((syn_it != prods_from_fridge.end()) && (syn_it->second > prod.second)) {
            // нашли подходящий заменитель
            status = HALF;
            replacements.push_back({prod.first, syn_it->first});
            break;
          }
        }
      }
    }
    switch (status) {
      case OK :
        orig_recipes.push_back(recipe.first);
        break;
      case HALF :
        modified_recipes.push_back({recipe.first, replacements});
        break;
      case NO :
        break;
    }
  }
}

void show_use_case_7(const std::vector<std::string> &allergic_products,
                     const std::vector<std::string> &orig_recipes,
                     const std::vector<ModifiedRecipe> &modified_recipes) {
  std::cout << "  Allergic products:  " << std::endl;
  if (!allergic_products.empty()) {
    for (auto prod: allergic_products) {
      std::cout << "    " << prod << std::endl;
    }
  }
  else {
    std::cout << "    No" << std::endl;
  }
  std::cout << "  Original recipes:" << std::endl;
  if (orig_recipes.empty()) {
    std::cout << "    No " << std::endl;
  } else {
    for (auto recipe: orig_recipes) {
      std::cout << "    " << recipe << std::endl;
    }
  }

  std::cout << "  Modified recipes:" << std::endl;
  if (modified_recipes.empty()) {
    std::cout << "    No " << std::endl;
  } else {
    for (auto modified_recipe: modified_recipes) {
      std::cout << "    " << modified_recipe.recipe_name << " - replacements:" << std::endl;
      for (auto replacement: modified_recipe.replacements) {
        std::cout << "                " << replacement.orig_product << " on " << replacement.select_product
                  << std::endl;
      }
    }
  }
}
