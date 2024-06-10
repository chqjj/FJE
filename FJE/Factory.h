#pragma once
#include <memory>
#include<map>
#include<unordered_map>
#include<functional>
#include"Product.h"



class FactoryRegistrar {
public:
	using CreateProductFunc = std::function<std::shared_ptr<Product>()>;
	static std::unordered_map<std::string, CreateProductFunc> factories;

	static void Register(const std::string& type, CreateProductFunc factoryFunc) {
		factories[type] = factoryFunc;
	}

	static std::shared_ptr<Product> CreateProduct(const std::string& type) {
		auto it = factories.find(type);
		if (it != factories.end()) {
			return it->second(); // ע����������˺���  
		}
		return nullptr;
	}
};

std::unordered_map<std::string, FactoryRegistrar::CreateProductFunc> FactoryRegistrar::factories;
class JsonFactory {
public:
	virtual~JsonFactory(){}
    virtual std::shared_ptr<Product> createStyle(const std::string& style) { return FactoryRegistrar::CreateProduct(style);};
	virtual std::shared_ptr<Product> createIcon(std::string type) { return std::make_shared<Icon>(type); }
};


class JsonIconFactory :public JsonFactory {
public:
	std::shared_ptr<Product> createIcon(std::string type) override {
		return std::make_shared<Icon>(type);
	}
};

class RectangleStyleFactory : public JsonFactory {
public:
    static RectangleStyleFactory& Instance() {
        static RectangleStyleFactory factory;
        return factory;
    }

    RectangleStyleFactory() {
        FactoryRegistrar::Register("rectangle", [this]() { return this->CreateRectangleStyle(); });
    }

    std::shared_ptr<Product> createStyle(const std::string& style) override {
        // ����������һЩ�߼�����style�������ز�ͬ�Ĳ�Ʒ����������������������Ƿ���RectangleStyle  
        return this->CreateRectangleStyle();
    }

private:
    std::shared_ptr<Product> CreateRectangleStyle() const {
        return std::make_shared<RectangleStyle>();
    }
};

class TreeStyleFactory : public JsonFactory {
public:
    static TreeStyleFactory& Instance() {
        static TreeStyleFactory factory;
        return factory;
    }

    TreeStyleFactory() {
        FactoryRegistrar::Register("tree", [this]() { return this->CreateTreeStyle(); });
    }

    std::shared_ptr<Product> createStyle(const std::string& style) override {
        // ͬ�ϣ������������Ƿ���TreeStyle  
        return this->CreateTreeStyle();
    }

private:
    std::shared_ptr<Product> CreateTreeStyle() const {
        return std::make_shared<TreeStyle>();
    }
};


