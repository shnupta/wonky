#include "wonky/full_screen.h"
#include <memory>
#include <wonky/app.h>

int main(int argc, char** argv) {
	auto main_screen = std::make_shared<wonky::full_screen>();
	// auto main_screen = std::make_shared<wonky::screen>();
	wonky::app app;
	app.set_screen(main_screen);

	// todo: something like this?
	// main_screen->compose(wonky::container({
	// 		wonky::textbox() | wonky::border::rounded | wonky::flex,
	// 		wonky::button()
	// }));

	// todo: construct a full screen view
	// todo: build a widget tree that renders to the view

	// todo: set this view as the root view of the app
	// app.set_root_view();

	app.run();
	return 0;
}
