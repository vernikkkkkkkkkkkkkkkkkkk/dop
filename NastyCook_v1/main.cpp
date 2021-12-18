#include "json/json.hpp"
#include "kitchen/product.hpp"
#include "kitchen/products.hpp"
#include "kitchen/fridge_item.hpp"
#include "kitchen/fridge.hpp"
#include "kitchen/recipe_step.hpp"
#include "kitchen/recipe.hpp"
#include "kitchen/cook_book.hpp"
#include "json/json_generator.hpp"
#include "json/json_read.hpp"
#include "utils.hpp"

#include "use_case_1.hpp"
#include "use_case_2.hpp"
#include "use_case_4.hpp"
#include "use_case_7.hpp"

int main() {
  // записываем json файлы если их НЕ существует
  // в текущей папке появится три файла:
  // products.json - в нем содержаться все продукты и заменмтели для каждого из них
  // fridge.json   - холодильник - содержит продукты которые есть в наличии и их кол-во
  // cook_book.json - кулинарная книга с рецептами. Рецепты могут зависеть от других рецептов.
  json_products_generator("products.json");
  json_fridge_generator("fridge.json");
  json_cook_book_generator("cook_book.json");

  // читаем json файлы
  Products prods;
  Fridge fridge;
  CookBook cook_book;
  json_read(prods, fridge, cook_book);

  std::cout << "Hello. We have the following products: " << std::endl;
  int counter = 0;
  for (auto prod: prods.products) {
    std::cout << "  " << ++counter << " " << prod.name << std::endl;
  }

  std::cout << "What product do you like today? (Please type number or 0 if any product is ok) ";
  int id;
  std::cin >> id;

  if ( (id < 0) || (id > counter)) {
    std::cout << "Sorry we have NOT got this product. Bye-bye." << std::endl;
    return 1;
  }
  std::string selected_prod;
  if (id != 0) {
    selected_prod = prods.products[--id].name;
    std::cout << "Thanks, you chose " << selected_prod << std::endl << std::endl;
  }
  else {
    std::cout << "Great, you like any product" << std::endl << std::endl;
  }

  // трасформируем кулинарную книгу для быстрого поиска рецептов
  std::map<std::string, std::map<std::string, int> > recipes;
  transform(cook_book, recipes);

  // варианты развития 1
  {
    std::cout << "********************************************" << std::endl;
    std::cout << "Use case 1:" << std::endl;
    std::vector<std::string> skip_recipes;
    std::vector<std::string> orig_recipes;
    std::vector<ModifiedRecipe> modified_recipes;
    use_case_1(fridge, prods, selected_prod, recipes, skip_recipes, orig_recipes, modified_recipes);
    show_use_case_1(skip_recipes, orig_recipes, modified_recipes);
  }

  // варианты развития 2
  {
    std::cout << std::endl << "********************************************" << std::endl;
    std::cout << "Use case 2:" << std::endl;
    std::vector<std::string> skip_recipes;
    std::vector<std::string> orig_recipes;
    std::vector<ModifiedRecipe> modified_recipes;
    use_case_2(fridge, prods, selected_prod, recipes, skip_recipes, orig_recipes, modified_recipes);
    show_use_case_2(skip_recipes, orig_recipes, modified_recipes);
  }

  // варианты развития 4
  {
    std::cout << std::endl << "********************************************" << std::endl;
    std::cout << "Use case 4:" << std::endl;
    std::vector<std::string> skip_recipes;
    std::vector<std::string> orig_recipes;
    std::vector<ModifiedRecipe> modified_recipes;
    use_case_4(fridge, prods, selected_prod, recipes, skip_recipes, orig_recipes, modified_recipes);
    show_use_case_4(skip_recipes, orig_recipes, modified_recipes, cook_book);
  }

  // варианты развития 7
  {
    std::cout << std::endl << "********************************************" << std::endl;
    std::cout << "Use case 7:" << std::endl;
    int counter = 0;
    for (auto prod: prods.products) {
      std::cout << "  " << ++counter << " " << prod.name << std::endl;
    }
    std::cout << "What product do you have allergy? (Please type number or 0 if no ones) ";
    int id;
    std::cin >> id;
    if ( (id < 0) || (id > counter)) {
      std::cout << "Sorry we have NOT got this product. Bye-bye." << std::endl;
      return 1;
    }
    std::vector<std::string> allergic_products;
    if (id != 0) {
      allergic_products.push_back(prods.products[--id].name);
    }
    std::vector<std::string> orig_recipes;
    std::vector<ModifiedRecipe> modified_recipes;
    use_case_7(fridge, prods, allergic_products, recipes, orig_recipes, modified_recipes);
    show_use_case_7(allergic_products, orig_recipes, modified_recipes);
  }
  return 0;
}
