#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include<stack>
#include "Factory.h"

// 抽象组件类
class JsonComponent {
public:
    virtual ~JsonComponent() {}
    virtual void print(std::shared_ptr<Style> style, std::shared_ptr<Icon> icon, bool bottom, bool top, std::vector<bool> has_next) = 0;
    
};

// 叶子节点类
class JsonNode : public JsonComponent {
private:
    std::string value;

    bool is_leaf;
    int depth;

public:
    JsonNode(const std::string& val, int depth, bool is_leaf) : 
        value(val), depth(depth), is_leaf(is_leaf) {
       

    }
    int getDepth() { return depth; }
    void print(std::shared_ptr<Style> style, std::shared_ptr<Icon> icon, bool top, bool bottom, std::vector<bool> has_next) override{
        std::string result = style->getPre(top, bottom, has_next);
        value += icon->getIcon(is_leaf);
        auto suff = style->getSuff(result, value);
        result += value + suff;
        std::cout << result << std::endl;
    }
};

// 容器节点类
class JsonContainer : public JsonComponent {
private:
    std::vector<std::shared_ptr<JsonNode>> children;
    
public:
    void addChild(const std::shared_ptr<JsonNode>& child) {
        children.push_back(child);
    }
    // 判断节点有没有下一个兄弟节点，并找到父节点
    void getNext(std::stack<std::pair<int, int>>& depth_stack, std::vector<bool>& depth_list, std::vector<int>& parent)
    {
        for (int i = 0; i < children.size(); ++i) {
            if (depth_stack.empty()) {
                depth_stack.push(std::make_pair(children[i]->getDepth(), i));
            }
            else if (depth_stack.top().first < children[i]->getDepth()) {
                parent[i] = depth_stack.top().second;
                depth_stack.push(std::make_pair(children[i]->getDepth(), i));
            }
            else {
                while (!depth_stack.empty() && depth_stack.top().first >= children[i]->getDepth()) {
                    if (depth_stack.top().first == children[i]->getDepth()) {
                        int index = depth_stack.top().second;
                        depth_list[index] = true;
                        depth_stack.pop();
                    }
                    else {
                        depth_stack.pop();
                    }
                }
                if (!depth_stack.empty()) parent[i] = depth_stack.top().second;
                depth_stack.push(std::make_pair(children[i]->getDepth(), i));
            }
        }
    }
    void print(std::shared_ptr<Style> style, std::shared_ptr<Icon> icon, bool top = false,
        bool bottom = false, std::vector<bool> has_next=std::vector<bool>()) override {
        if (children.empty()) return;
        // 深度列表，用来判断有没有下一个兄弟节点
        std::vector<bool> depth_list(children.size(), false);
        std::stack<std::pair<int, int>> depth_stack;
        depth_stack.push(std::make_pair(children[0]->getDepth(), 0));
        std::vector<int> parent(children.size(), -1);
 
        getNext(depth_stack, depth_list, parent);
            
       
        for (size_t i = 0; i < children.size(); ++i) {
            std::vector<bool> curDepth;
            getCurDepth(i, parent, curDepth, depth_list);
            bool top = i == 0 ? true : false;
            bool bottom = i == (children.size() - 1) ? true : false;
            children[i]->print(style, icon, top, bottom, curDepth);

            
        }
    }
    void getCurDepth(const size_t& i, std::vector<int>& parent, std::vector<bool>& curDepth, std::vector<bool>& depth_list)
    {
        int index = i;
        while (parent[index] != -1) {
            curDepth.insert(curDepth.begin(), depth_list[index]);
            index = parent[index];
        }
        curDepth.insert(curDepth.begin(), depth_list[index]);
    }
};



