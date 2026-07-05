#include <AppCore/AppCore.h>

using namespace ultralight;

class MyWindowListener : public WindowListener {
private:
   RefPtr<Overlay> overlay_;
public:
   MyWindowListener(RefPtr<Overlay> overlay) : overlay_(overlay) {}
   
   void OnResize(Window* window, uint32_t width, uint32_t height) override {
      overlay_->Resize(width, height);
   }

   void OnClose(Window* window) override { 
      App::instance()->Quit();
   }
};

int main(int argc, char const *argv[])
{
   auto app = App::Create();

   auto window = Window::Create(app->main_monitor(), 800, 600, false, 
      kWindowFlags_Titled | kWindowFlags_Resizable);

   window->SetTitle("TicTacToe UI Test");

   auto overlay = Overlay::Create(window, window->width(), window->height(), 0, 0);

   overlay->view()->LoadURL("file:///index.html");

   window->set_listener(new MyWindowListener(overlay));

   app->Run();

   return 0;
}