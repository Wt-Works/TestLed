#include <Wt/WApplication>
#include <Wt/WEnvironment>
#include "wtautoconfig.h"
#include "wttestledmenudialog.h"

struct WtApplication : public Wt::WApplication
{
  WtApplication(const Wt::WEnvironment& env)
    : Wt::WApplication(env)
  {
    this->setTitle("TestLed");
    this->useStyleSheet("wt.css");
    root()->addWidget(new WtTestLedMenuDialog);
  }
};

Wt::WApplication *createApplication(
  const Wt::WEnvironment& env)
{
  return new WtApplication(env);
}

int main(int argc, char **argv)
{
  WtAutoConfig::SaveDefaultStylesheet();
  WtAutoConfig a(argc,argv,createApplication);
  return a.Run();
}
