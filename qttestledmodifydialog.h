#ifndef QTTESTLEDMODIFYDIALOG_H
#define QTTESTLEDMODIFYDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wunused-but-set-parameter"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtTestLedModifyDialog;
}

namespace ribi {

struct QtLed;
struct QtLedDialog;

class QtTestLedModifyDialog : public ribi::QtHideAndShowDialog
{
  Q_OBJECT

public:
  explicit QtTestLedModifyDialog(QWidget *parent = 0);
  QtTestLedModifyDialog(const QtTestLedModifyDialog&) = delete;
  QtTestLedModifyDialog& operator=(const QtTestLedModifyDialog&) = delete;
  ~QtTestLedModifyDialog() noexcept;

  QtLedDialog * GetQtDialog() const noexcept { return m_qtleddialog; }
  QtLed * GetQtLed() const noexcept { return m_qtled; }

private:
  Ui::QtTestLedModifyDialog *ui;

  QtLedDialog * const m_qtleddialog;
  QtLed * const m_qtled;

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif

};

} //~namespace ribi

#endif // QTTESTLEDMODIFYDIALOG_H
