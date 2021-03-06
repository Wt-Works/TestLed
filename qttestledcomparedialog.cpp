//---------------------------------------------------------------------------
/*
TestLed, tool to test the Led class
Copyright (C) 2011-2015 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ToolTestLed.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qttestledcomparedialog.h"

#include <QGridLayout>

#include "led.h"
#include "qtled.h"
#include "trace.h"
#include "testtimer.h"

#include "ui_qttestledcomparedialog.h"
#pragma GCC diagnostic pop

ribi::QtTestLedCompareDialog::QtTestLedCompareDialog(QWidget *parent) noexcept
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtTestLedCompareDialog)
{
  #ifndef NDEBUG
  Test();
  #endif
  ui->setupUi(this);

  assert(!this->layout());
  QGridLayout * const my_layout = new QGridLayout;
  this->setLayout(my_layout);
  for (int i=0; i!=9; ++i)
  {
    Led led;
    led.SetIntensity(1.0);
    led.SetRed(  (i / 3) * (255 / 3));
    led.SetGreen((i % 3) * (255 / 3));
    led.SetBlue(0);
    QtLed * const qtled{new QtLed(0.0,255,0,0,this)};
    qtled->SetLed(led);
    my_layout->addWidget(qtled,i/3,i%3,1,1);
  }
}

ribi::QtTestLedCompareDialog::~QtTestLedCompareDialog() noexcept
{
  delete ui;
}


void ribi::QtTestLedCompareDialog::on_slider_valueChanged(int /* value */) noexcept
{
  /*
  const double intensity = boost::numeric_cast<double>(value)
    / boost::numeric_cast<double>(ui->slider->maximum());

  const std::vector<QtLedWidget*   > leds  { ui->led_left , ui->led_mid , ui->led_right  };
  const std::vector<QPlainTextEdit*> texts { ui->text_left, ui->text_mid, ui->text_right };
  assert(leds.size() == texts.size());
  const int n = leds.size();
  for (int i=0; i!=n; ++i)
  {
    leds[i]->GetWidget()->GetLed()->SetIntensity(intensity);
    std::string s;
    for (const std::string& t: leds[i]->GetWidget()->ToCanvas(5)->ToStrings())
    {
      s += (t + '\n');
    }
    texts[i]->setPlainText(s.c_str());
  }
  */
}

#ifndef NDEBUG
void ribi::QtTestLedCompareDialog::Test() noexcept
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
  QtTestLedCompareDialog();
}
#endif
