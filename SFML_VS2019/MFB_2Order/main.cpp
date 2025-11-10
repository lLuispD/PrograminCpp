#include "SFML_MFB.hpp"


int main() {
	Application::Instance = new Application();

	Application::Instance->Run();

	delete Application::Instance;

	return 0;
}