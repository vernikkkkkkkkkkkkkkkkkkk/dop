
#pragma once

#include "kitchen/products.hpp"
#include "kitchen/fridge.hpp"
#include "utils.hpp"

#include <map>
#include <vector>

// 2.	Система при выборе нового рецепта задает дополнительный вопрос:
//    на скольких человек готовим. Ответ учитывается при приготовлении

void use_case_2(const Fridge &fridge, const Products &products, const std::string& selected_prod,
                const std::map<std::string, std::map<std::string, int> > &recipes, std::vector<std::string> &skip_recipes,
                std::vector<std::string> &orig_recipes, std::vector<ModifiedRecipe> &modified_recipes) {
  std::cout << "На скольких человек готовим? ";
  int N;
  std::cin >> N;
  if (N <= 0) {
    std::cout << "Sorry. Negative number of people." << std::endl;
    return ;
  }

  // берем из холодильника продукты
  std::map<std::string, int> prods_from_fridge;
  for (const auto &prod: products.products) {
    prods_from_fridge[prod.name] = 0;
  }
  for (const auto &item: fridge.items) {
    prods_from_fridge[item.product_name] = item.amount;
  }
  // берем заменители
  std::map<std::string, std::vector<std::string> > prods_synonyms;
  for (const auto &item: products.products) {
    prods_synonyms[item.name] = item.synonyms;
  }

  enum Status {
    OK, HALF, NO
  };

  // сравниваем продукты из холодилька и рецепттов
  for (const auto &recipe: recipes) {
    if (!selected_prod.empty()) {
      if (recipe.second.find(selected_prod) == recipe.second.end()) {
        skip_recipes.push_back(recipe.first);
        continue;
      }
    }
    Status status = OK;
    std::vector<Replacement> replacements;
    for (auto prod: recipe.second) {
      auto it = prods_from_fridge.find(prod.first);
      if ((it == prods_from_fridge.end()) || (it->second < N*prod.second)) {
        // нет продукта в холодильнике или его недостаточно - смотрим заменители
        status = NO;
        for (auto syn_product: prods_synonyms[prod.first]) {
          auto syn_it = prods_from_fridge.find(syn_product);
          if ((syn_it != prods_from_fridge.end()) && (syn_it->second > N*prod.second)) {
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

void
show_use_case_2(const std::vector<std::string>& skip_recipes,
                const std::vector<std::string> &orig_recipes, const std::vector<ModifiedRecipe> &modified_recipes) {
  std::cout << "  The best recipes:" << std::endl;
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

  std::cout << "  Skipped recipes so as they do NOT have the selected product:" << std::endl;
  if (skip_recipes.empty()) {
    std::cout << "    No " << std::endl;
  } else {
    for (auto recipe: skip_recipes) {
      std::cout << "    " << recipe << std::endl;
    }
  }
}
