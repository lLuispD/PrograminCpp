/*  SFML 3.0.0  */

#include "application.hpp"

int main() {
	Application::Instance = new Application();

	Application::Instance->Run();

	delete Application::Instance;

	return 0;
}