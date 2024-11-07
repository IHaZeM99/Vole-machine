#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Vole.h"
using namespace std;

string SCR_Next = "";
string LASTHEX_Next = "";
Machine machine;
Memory* memory1 = machine.getmem();
CPU* cpu = machine.getcpu();
Register* register1= cpu->getreg();
CU* cu = cpu->getcu();
ALU* alu = cpu->getAlu();

void MainWindow::print_mem(Ui::MainWindow* ui){
    // Iterate over the rows to populate the QTableWidget
    for (int row = 0; row < 255; ++row) {
        string address = Memory::intToHex(row);

        string cellData = memory1->getCell(address);
        string binValue = memory1->hexatoBinary(cellData);
        int intVlaue = cpu->hexStringToInt(cellData);
        double floatValue = alu->floatextract(cellData);

        qDebug() << "after creating loop"<<row;


        ui->Memory_T->setItem(row, 0,new QTableWidgetItem(QString::fromStdString(binValue))); // Binary data
        ui->Memory_T->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(cellData))); // Hex data
        ui->Memory_T->setItem(row, 2, new QTableWidgetItem(QString::number(intVlaue))); // int data
        ui->Memory_T->setItem(row, 3, new QTableWidgetItem(QString::number(floatValue,'f', 6))); // float data

    }
}

void MainWindow::print_reg(Ui::MainWindow* ui){
    for (int row = 0; row < 16; ++row) {
        string address = register1->getHexadecimalRange(row);
        string cellData = register1->getCell(address);
        string binValue = register1->hexatoBinary(cellData);
        int intVlaue = cpu->hexStringToInt(cellData);
        double floatValue = alu->floatextract(cellData);
        //string bin = ALU::;
        qDebug() << "after creating loop"<<row;


        ui->Register_T->setItem(row, 0,new QTableWidgetItem(QString::fromStdString(binValue))); // Binary data
        ui->Register_T->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(cellData))); // Hex data
        ui->Register_T->setItem(row, 2, new QTableWidgetItem(QString::number(intVlaue))); // int data
        ui->Register_T->setItem(row, 3, new QTableWidgetItem(QString::number(floatValue,'f', 6))); // float data
    }
}

void MainWindow::print_scr(Ui::MainWindow* ui,string hex){

    if(hex == "00" || hex == LASTHEX_Next){
        return;
    }
    LASTHEX_Next = hex;
    string ascii = "";
    for (size_t i = 0; i < hex.length(); i += 2) {
        string part = hex.substr(i, 2);
        char ch = stoul(part, nullptr, 16);
        ascii += ch;
    }
    SCR_Next += "ascii = "+ascii + ", hex = " + hex + "\n";
    ui->textEdit->setText(QString::fromStdString(SCR_Next));
    qDebug() << "Memory content at address '00': " << QString::fromStdString(hex); // Debugging line

}

void MainWindow::showTemporaryText() {
    // Set the text on the label
    ui->done->show();

    // Create a QTimer to clear the text after 3 seconds (3000 ms)
    QTimer::singleShot(3000, this, [=]() {
        ui->done->hide();  // Hide the label text
    });
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qDebug() << "Before creating memory1";
    // Ensure tableWidget is already initialized and set up with rows and columns
    print_mem(ui);
    print_reg(ui);
    print_scr(ui,memory1->getCell("00"));
    ui->done->hide();

    machine.setPC("0A");
    ui->start_line->setText("0A");

    ui->Memory_T->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->Memory_T->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->Memory_T->setColumnWidth(0, 125);
    ui->Memory_T->setRowHeight(0, 24);

    ui->Register_T->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->Register_T->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->Register_T->setColumnWidth(0, 125);
    ui->Register_T->setRowHeight(0, 24);



    qDebug() << "after creating memory1";


    //cpu->setPC("0A");
    string pc_str = cpu->getPC();
    string pc_str2 = "                    "+pc_str;
    ui->pc_line->setText(QString::fromStdString(pc_str2));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_store_btn_clicked()
{
    QString instruction = ui->inst_kine->text();
    string inst_str = instruction.toStdString();
    if(inst_str.length()<4){
        QMessageBox::critical(this,"Error","Please enter a valid instruction");
    }
    else if(!alu->isValid(inst_str)){
        QMessageBox::critical(this,"Error","Please enter a valid instruction");
    }else{
        machine.loadProgramNormalWay(inst_str);
        print_mem(ui);
        print_reg(ui);
        print_scr(ui,memory1->getCell("00"));
        showTemporaryText();

        string pc_str = cpu->getPC();
        string pc_str2 = "                    "+pc_str;
        ui->pc_line->setText(QString::fromStdString(pc_str2));
    }
    ui->inst_kine->clear();
}

void MainWindow::on_Add_btn_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(this,tr("Select text file"),QCoreApplication::applicationDirPath(),tr("Text file(*.txt)"));
    qDebug() << file_name;
    if(file_name.isEmpty() || file_name.isNull()){
        QMessageBox::critical(this,"Error","Please enter a valid file");
    }else{
        on_C_M_btn_clicked();
        machine.clearInstructions();
        string file_str = file_name.toStdString();
        machine.loadProgramFile(file_str);
        machine.sendInstructionsToMemory();
        //machine.sendInstructionsToCPU();
        print_mem(ui);
        print_reg(ui);
        print_scr(ui,memory1->getCell("00"));

        string pc_str = cpu->getPC();
        string address = (ui->start_line->text()).toStdString();
        if(address != pc_str){
            string pc_str2 = "                    "+address;
            ui->pc_line->setText(QString::fromStdString(pc_str2));
            machine.setPC(address);
        }else{
            string pc_str2 = "                    "+pc_str;
            ui->pc_line->setText(QString::fromStdString(pc_str2));
        }
    }
}


void MainWindow::on_C_M_btn_clicked()
{
    memory1->clearMemory();
    machine.clearInstructions();
    qDebug() << "done";
    print_mem(ui);
    cpu->setend();
    cpu->setPC("0A");
    memory1->setStart("0A");
    string pc_str = cpu->getPC();
    string pc_str2 = "                    "+pc_str;
    ui->pc_line->setText(QString::fromStdString(pc_str2));
}


void MainWindow::on_C_R_btn_clicked()
{
    register1->clearRegister();
    qDebug() << "done";
    print_reg(ui);
}


void MainWindow::on_run_halt_btn_clicked()
{
    on_C_S_btn_clicked();
    machine.resetExecutionState();
    machine.runTillHalt(ui);
    print_mem(ui);
    print_reg(ui);
    cpu->display_screen(ui);

    //print_scr(ui,memory1->getCell("00"));

    QMessageBox::information(this,"Execution","The Execution has reached C000");
    cpu->setend();
    cpu->setPC("0A");
    memory1->setStart("0A");
    string pc_str = cpu->getPC();
    string pc_str2 = "                    "+pc_str;
    ui->pc_line->setText(QString::fromStdString(pc_str2));
}

void MainWindow::on_run_next_btn_clicked()
{
    machine.runNextStep();
    print_mem(ui);
    print_reg(ui);
    print_scr(ui,memory1->getCell("00"));
    qDebug () << "screen -----------------------------------------\n";


    if(cpu->getend()){
        QMessageBox::information(this,"Execution","The Execution has reached the end of the memory");
        cpu->setend();
        cpu->setPC("0A");
        memory1->setStart("0A");
    }
    //machine.setPC("0A");
    string pc_str = cpu->getPC();
    string pc_str2 = "                    "+pc_str;
    ui->pc_line->setText(QString::fromStdString(pc_str2));
}


void MainWindow::on_C_S_btn_clicked()
{
    ui->textEdit->clear();
    memory1->setCell("00","00");
    SCR_Next = "";
    LASTHEX_Next = "";
    cpu->clear_screen();
}


void MainWindow::on_Fetch_btn_clicked()
{
    string address = (ui->start_line->text()).toStdString();
    if(address == "00"){
        QMessageBox::critical(this,"Error","You can't start from 00 address");
        return;
    }
    if(address.size() != 2 || address == ""){
        QMessageBox::critical(this,"Error","Please enter a valid address");
        return;
    }
    else if(address[0] < '0' && address[0] > '9' && address[0] < 'A' && address[0] > 'F'){
        QMessageBox::critical(this,"Error","Please enter a valid address");
        return;
    }
    else if(address[1] < '0' && address[1] > '9' && address[1] < 'A' && address[1] > 'F'){
        QMessageBox::critical(this,"Error","Please enter a valid address");
        return;
    }

    machine.setPC(address);
    string pc_str2 = "                    "+address;
    ui->pc_line->setText(QString::fromStdString(pc_str2));

}



