#include <memory>

#include <wonky/app.h>
#include <wonky/screen.h>
#include <wonky/terminal.h>

int main(int argc, char** argv) {
  wonky::app a;

  // a.set_root(main_widget);

  //
  a.mutable_loop()->post(5s, [&] { a.stop(); });
  //

  a.run();
  return 0;
}
