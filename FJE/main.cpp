
#include"json.h"
// ����ע��ĸ�����  
class FactoryRegistrarInitializer {
public:
	FactoryRegistrarInitializer() {
		// ע�����й���  
		FactoryRegistrar::Register("rectangle", RectangleStyleFactory::Instance());
		FactoryRegistrar::Register("tree", TreeStyleFactory::Instance());
		     
	}
};

static FactoryRegistrarInitializer g_factoryRegistrarInitializer;



int main(int argc, char* argv[]) {
	
	
	std::string jsonFile = "json1.json";
	std::string styleName = "rectangle";
	std::string iconFamily = "";
	for (int i = 1; i < argc; ++i) {
		std::string arg = argv[i];
		if (arg == "-f" && i + 1 < argc) {
			jsonFile = argv[++i];
		}
		else if (arg == "-s" && i + 1 < argc) {
			styleName = argv[++i];
		}
		else if (arg == "-i" && i + 1 < argc) {
			iconFamily = argv[++i];
		}
	}
	auto jsonContainer = readJson("../../../../"+jsonFile);
	JsonFactory* factory = FactoryRegistrar::CreateFactory(styleName);
	//std::cout<< FactoryRegistrar::CreateFactory(styleName);
	auto style = factory->createStyle(styleName);
	auto icon = factory->createIcon(iconFamily);
	
	jsonContainer.print(std::dynamic_pointer_cast<Style>(style), std::dynamic_pointer_cast<Icon>(icon));

}