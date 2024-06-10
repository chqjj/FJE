#pragma once
#include <memory>
#include<map>
#include<unordered_map>
#include<functional>
#include"Product.h"

class JsonFactory {
public:
    virtual~JsonFactory() {}
    virtual std::shared_ptr<Product> createStyle(const std::string& style) = 0;
    virtual std::shared_ptr<Product> createIcon(std::string type) = 0;
};

class FactoryRegistrar {
public:
	using CreateProductFunc = std::function<std::shared_ptr<Product>()>;
	static std::unordered_map<std::string, JsonFactory*> factories;

	static void Register(const std::string& type, JsonFactory* factoryFunc) {
		factories[type] = factoryFunc;
	}

	/*static std::shared_ptr<Product> CreateProduct(const std::string& type) {
		auto it = factories.find(type);
		if (it != factories.end()) {
			return it->second(); 
		}
		return nullptr;
	}*/
    static JsonFactory* CreateFactory(const std::string& type) {
        auto it = factories.find(type);
        if (it != factories.end()) {
            return it->second;
        }
        return nullptr;
    }
};

std::unordered_map<std::string, JsonFactory*> FactoryRegistrar::factories;



/*class JsonIconFactory :public JsonFactory {
public:
	std::shared_ptr<Product> createIcon(std::string type) override {
		return std::make_shared<Icon>(type);
	}
};*/

class RectangleStyleFactory : public JsonFactory {
public:
    static RectangleStyleFactory* Instance() {
        //static RectangleStyleFactory* factory;
        return new RectangleStyleFactory();
    }

    RectangleStyleFactory() {
        //FactoryRegistrar::Register("rectangle", [this]() { return this->CreateRectangleStyle(); });
    }

    std::shared_ptr<Product> createStyle(const std::string& style) override {
        return this->CreateRectangleStyle();
    }
    std::shared_ptr<Product> createIcon(std::string type) override {
        return std::make_shared<Icon>(type);
    }

private:
    std::shared_ptr<Product> CreateRectangleStyle() const {
        return std::make_shared<RectangleStyle>();
    }
};

class TreeStyleFactory : public JsonFactory {
public:
   static TreeStyleFactory* Instance() {
        
        return new TreeStyleFactory();
    }

    TreeStyleFactory() {
        //FactoryRegistrar::Register("tree", [this]() { return this->CreateTreeStyle(); });
    }

    std::shared_ptr<Product> createStyle(const std::string& style) override {
        return this->CreateTreeStyle();
    }
    std::shared_ptr<Product> createIcon(std::string type) override {
        return std::make_shared<Icon>(type);
    }

private:
    std::shared_ptr<Product> CreateTreeStyle() const {
        return std::make_shared<TreeStyle>();
    }
};


