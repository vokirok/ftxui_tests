#include <iostream>
#include <fstream>
#include <format>

#include <windows.h>

#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>

ftxui::Component LoginForm() {
	class Impl : public ftxui::ComponentBase {
	private:
		std::string loginname{};
		std::string password{};

		void OnLogin() {
			return;
		}

	public:
		Impl() {
			//auto doc = ftxui::vbox({
			//  ftxui::vbox({
			//	  ftxui::text("separatorDouble"),
			//	  ftxui::separatorDouble(),
			//	  ftxui::hbox(ftxui::text("left"), ftxui::separatorDouble(), ftxui::text("right")),
			//  }) | ftxui::borderDouble,
			//});

			Add(ftxui::Container::Vertical({
				ftxui::Input(&loginname, "", ftxui::InputOption { .multiline = false }),
				ftxui::Input(&password, "", ftxui::InputOption { .password = true, .multiline = false }),
				ftxui::Button("Sign in", std::bind(&Impl::OnLogin, this)),
				ftxui::Button("Sign in", [this]() {this->OnLogin(); }),
			}));

			//auto content = ftxui::Renderer([=] {
			//	return doc;
			//});

			//Add(content);
		}
	};

	return ftxui::Make<Impl>();
}


void TestInput()
{
	using namespace std;
	using namespace ftxui;
	
	auto screen = ScreenInteractive::Fullscreen();

	int window_1_left = 20;
	int window_1_top = 10;
	int window_1_width = 40;
	int window_1_height = 20;

	auto window_1 = Window({
		.inner = LoginForm(),
		.title = "First window",
		.left = &window_1_left,
		.top = &window_1_top,
		.width = &window_1_width,
		.height = &window_1_height,
		});

	auto window_5 = Window({});

	auto window_container = Container::Stacked({
		window_1,
		window_5,
		});

	auto display_win_1 = Renderer([&] {
		return text("window_1: " +  //
			std::to_string(window_1_width) + "x" +
			std::to_string(window_1_height) + " + " +
			std::to_string(window_1_left) + "," +
			std::to_string(window_1_top));
		});

	auto layout = Container::Vertical({
		display_win_1,
		window_container,
		});

	screen.Loop(layout);

}


int main() {
	setlocale(LC_ALL, "ru-RU.UTF8");

	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	std::string title{ "Приве́т नमस्ते! 你好, 世界! 🎂👨‍👩‍👧‍👦!" };
	SetConsoleTitleA(title.c_str());
    std::cout << title << std::endl;


	std::ofstream out;
	out.open(title, std::ios::app);
	out << title << std::endl;

	std::cout << "Введите заголовок: ";
	std::getline(std::cin, title);
	SetConsoleTitleA(title.c_str());
	std::cout << std::format("Заменили заголовок на: {}", title) << std::endl;

	out << title << std::endl;
	out.close();

	std::cin >> title;
	std::cout << title;

	TestInput();

	return 0;
}
