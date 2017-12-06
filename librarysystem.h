#ifndef LIBRARYSYSTEM_H
#define LIBRARYSYSTEM_H

#include <QWidget>

namespace Ui {
class LibrarySystem;
}

class LibrarySystem : public QWidget
{
    Q_OBJECT

public:
    explicit LibrarySystem(QWidget *parent = 0);
    ~LibrarySystem();

private slots:
    void on_userwindowinformation_clicked();

    void on_userRegister_clicked();

private:
    Ui::LibrarySystem *ui;
};

#endif // LIBRARYSYSTEM_H
