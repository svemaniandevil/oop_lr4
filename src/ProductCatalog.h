#ifndef PRODUCT_CATALOG_H_
#define PRODUCT_CATALOG_H_

#include <cstdint>
#include <string>
#include <vector>

class Client;

// 4.	Додатковий клас №3 для множинного наслідування - Каталог продукції (засоби для догляду за волоссям).
// 1.	Визначити ієрархію класів відповідно до варіанта (не менше 8 полів на клас).
class ProductCatalog
{
public:
    std::string catalog_name_;
    std::string supplier_;

protected:
    std::vector<std::string> product_names_;
    std::vector<double> product_prices_;
    std::vector<int> product_stock_;

private:
    uint16_t total_sold_;
    double sales_revenue_;
    std::string currency_;

    int FindProduct(const std::string& product_name) const;

public:
    // 5.	Продемонструвати передачу параметрів конструктору базового класу (не менше 5-ти аргументів);
    // побудувати відповідні об’єкти, а також побудувати конструктор похідного класу, який використовує
    // всі параметри, які вказані в його оголошенні (передача параметрів конструктору базового класу
    // відбувається всередині похідного класу).
    ProductCatalog(const std::string& catalog_name, const std::string& supplier,
        const std::string& currency = "грн");
    ProductCatalog(const ProductCatalog& other);
    // 8.	Визначити в класі деструктор з метою відслідковування входження у блоки програми та виходу з них,
    // для якого визначений об'єкт цього класу.
    ~ProductCatalog();

    void AddProduct(const std::string& product_name, double price, int stock);
    bool SellProduct(const std::string& product_name, Client& client);

    uint16_t GetTotalSold() const;
    double GetSalesRevenue() const;

    void DisplayInfo() const;
};

#endif  // PRODUCT_CATALOG_H_
