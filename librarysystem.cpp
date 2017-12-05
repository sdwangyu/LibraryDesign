#include "librarysystem.h"
#include "ui_librarysystem.h"

LibrarySystem::LibrarySystem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LibrarySystem)
{
    ui->setupUi(this);
}

LibrarySystem::~LibrarySystem()
{
    delete ui;
}
