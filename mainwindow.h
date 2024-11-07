#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QTimer>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void showTemporaryText();
    void print_scr(Ui::MainWindow* ui,std::string hex);
    void print_reg(Ui::MainWindow* ui);
    void print_mem(Ui::MainWindow* ui);


private slots:
    void on_store_btn_clicked();

    void on_C_M_btn_clicked();

    void on_C_R_btn_clicked();

    void on_run_halt_btn_clicked();

    void on_run_next_btn_clicked();

    void on_Add_btn_clicked();

    void on_C_S_btn_clicked();

    void on_Fetch_btn_clicked();


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
