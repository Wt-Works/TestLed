#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qttestledmodifydialog.h"

#include <boost/make_shared.hpp>

#include <QGridLayout>

#include "led.h"
#include "qtled.h"
#include "qtleddialog.h"
#include "testtimer.h"
#include "ui_qttestledmodifydialog.h"
#pragma GCC diagnostic pop

ribi::QtTestLedModifyDialog::QtTestLedModifyDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtTestLedModifyDialog),
    m_qtleddialog(new QtLedDialog(this)),
    m_qtled(new QtLed(0.0,255,0,0,this))
{
  #ifndef NDEBUG
  Test();
  #endif

  ui->setupUi(this);

  {
    assert(!ui->widget_left->layout());
    QGridLayout * const my_layout = new QGridLayout;
    assert(my_layout);
    ui->widget_left->setLayout(my_layout);
    assert(ui->widget_left->layout());
    my_layout->addWidget(m_qtled);
  }
  {
    assert(!ui->widget_right->layout());
    QGridLayout * const my_layout = new QGridLayout;
    assert(my_layout);
    ui->widget_right->setLayout(my_layout);
    assert(ui->widget_right->layout());
    ui->widget_right->layout()->addWidget(m_qtleddialog);
  }

  const Led led;
  m_qtleddialog->SetLed(led);
  m_qtled->SetLed(led);

  QObject::connect(
    m_qtleddialog,SIGNAL(on_led_changed(Led)),
    m_qtled,SLOT(SetLed(Led))
  );
}

ribi::QtTestLedModifyDialog::~QtTestLedModifyDialog() noexcept
{
  delete ui;
}

#ifndef NDEBUG
void ribi::QtTestLedModifyDialog::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  {
    QtLed();
    Led();
  }
  const TestTimer test_timer(__func__,__FILE__,1.0);
  QtTestLedModifyDialog d;
  #ifdef FIX_ISSUE_1
  //Dialog must change the LED
  {
    const Led led;
    d.GetQtDialog()->SetLed(led);
    assert(d.GetQtLed()->GetLed() == led);
  }
  {
    const Led led(0.5,128,128,128);
    d.GetQtDialog()->SetLed(led);
    assert(d.GetQtLed()->GetLed() == led);
  }
  #endif // FIX_ISSUE_1
}
#endif
