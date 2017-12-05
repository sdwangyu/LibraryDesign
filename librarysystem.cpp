#include "librarysystem.h"
#include "ui_librarysystem.h"

LibrarySystem::LibrarySystem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LibrarySystem)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
}

LibrarySystem::~LibrarySystem()
{
    delete ui;
}

void LibrarySystem::on_userwindowinformation_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(0);
}

void LibrarySystem::on_userRegister_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}
