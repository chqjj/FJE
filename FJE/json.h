#pragma once
#include"Component.h"
#include<fstream>
#include<direct.h>

// ȥ���հ׷�
std::string trim(std::string s) {
	if (!s.empty()) {
		s.erase(0, s.find_first_not_of(" "));
		s.erase(s.find_last_not_of(" ") + 1);
	}
	return s;
}
// ȥ������
std::string deleteQuote(std::string s) {
	if (s[0] == '\"' && s[s.size() - 1] == '\"') {
		s.erase(0, 1);
		s.erase(s.size() - 1, 1);
	}
	return s;
}

std::shared_ptr<JsonNode> process(std::string line, int& depth) {
	line = trim(line);

	// ����:�ж��Ƿ��ǽڵ�
	auto pos = line.find(':');
	if (pos == std::string::npos) {
		if (line[0] == '}') depth -= 1;
		return nullptr;
	}

	std::string key = deleteQuote(trim(line.substr(0, pos)));
	std::string value = deleteQuote(trim(line.substr(pos + 1)));
	// û�С�{��˵����Ҷ��
	if (value != "{") {
		auto node = std::make_shared<JsonNode>(key + ':' + value, depth, true);    //new JsonNode(key + ':' + value, depth, true);
		return node;
	}
	else {
		auto node = std::make_shared<JsonNode>(key, depth, false);
		depth += 1;
		return node;
	}
	return nullptr;

}



JsonContainer readJson(std::string rount) {
	std::ifstream ifs;
	
	ifs.open(rount, std::ios::in);
	JsonContainer json;
	int depth = 0;
	if (ifs.is_open())
	{
		std::string buf;
		while (getline(ifs, buf))
		{
			auto node = process(buf, depth);
			if (node) {
				json.addChild(node);
			}
		}
	}
	
	//�ر��ļ�   
	ifs.close();
	return json;
}

