#include "ProductCatalog.h"

#include <iostream>

#include "Client.h"

// 5.	Продемонструвати передачу параметрів конструктору базового класу (не менше 5-ти аргументів); побудувати
// відповідні об’єкти, а також побудувати конструктор похідного класу, який використовує всі параметри,
// які вказані в його оголошенні (передача параметрів конструктору базового класу відбувається всередині
// похідного класу).
// 7.	Продемонструвати для усіх класів порядок виклику конструкторів та деструкторів як для простого
// наслідування, так і для множинного.
ProductCatalog::ProductCatalog(const std::string& catalog_name,
    const std::string& supplier, const std::string& currency)
    : catalog_name_(catalog_name),
    supplier_(supplier),
    total_sold_(0),
    sales_revenue_(0.0),
    currency_(currency)
{
    std::cout << "[Конструктор] ProductCatalog (з параметрами) \""
        << catalog_name_ << "\", постачальник: " << supplier_ << std::endl;
}

// 7.	Продемонструвати для усіх класів порядок виклику конструкторів та деструкторів як для простого
// наслідування, так і для множинного.
ProductCatalog::ProductCatalog(const ProductCatalog& other)
    : catalog_name_(other.catalog_name_),
    supplier_(other.supplier_),
    product_names_(other.product_names_),
    product_prices_(other.product_prices_),
    product_stock_(other.product_stock_),
    total_sold_(other.total_sold_),
    sales_revenue_(other.sales_revenue_),
    currency_(other.currency_)
{
    std::cout << "[Конструктор копіювання] ProductCatalog \""
        << catalog_name_ << "\"" << std::endl;
}

// 7.	Продемонструвати для усіх класів порядок виклику конструкторів та деструкторів як для простого
// наслідування, так і для множинного.
// 8.	Визначити в класі деструктор з метою відслідковування входження у блоки програми та виходу з них, для
// якого визначений об'єкт цього класу.
ProductCatalog::~ProductCatalog()
{
    std::cout << "[Деструктор] ProductCatalog \"" << catalog_name_
        << "\" виходить з блоку програми." << std::endl;
}

int ProductCatalog::FindProduct(const std::string& product_name) const
{
    for (size_t i = 0; i < product_names_.size(); ++i)
        if (product_names_[i] == product_name)
            return static_cast<int>(i);
    return -1;
}

void ProductCatalog::AddProduct(const std::string& product_name, double price,
    int stock)
{
    int index = FindProduct(product_name);
    if (index != -1)
    {
        product_stock_[index] += stock;
        return;
    }
    product_names_.push_back(product_name);
    product_prices_.push_back(price);
    product_stock_.push_back(stock);
}

bool ProductCatalog::SellProduct(const std::string& product_name,
    Client& client)
{
    int index = FindProduct(product_name);
    if (index == -1)
    {
        std::cout << "  Товару \"" << product_name
            << "\" немає в каталозі." << std::endl;
        return false;
    }
    if (product_stock_[index] <= 0)
    {
        std::cout << "  Товар \"" << product_name
            << "\" закінчився на складі." << std::endl;
        return false;
    }
    --product_stock_[index];
    ++total_sold_;
    sales_revenue_ += product_prices_[index];
    client.AddToOrder(product_names_[index], product_prices_[index]);
    return true;
}

uint16_t ProductCatalog::GetTotalSold() const { return total_sold_; }
double ProductCatalog::GetSalesRevenue() const { return sales_revenue_; }

void ProductCatalog::DisplayInfo() const
{
    std::cout << "Каталог продукції \"" << catalog_name_
        << "\" (постачальник: " << supplier_ << "), продано: "
        << total_sold_ << ", виручка: " << sales_revenue_ << " "
        << currency_ << std::endl;
    for (size_t i = 0; i < product_names_.size(); ++i)
        std::cout << "  - " << product_names_[i] << ": " << product_prices_[i]
        << " " << currency_ << ", на складі: " << product_stock_[i]
            << std::endl;
}
