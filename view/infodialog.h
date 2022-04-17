#ifndef INFODIALOG_H
#define INFODIALOG_H
#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QDebug>

class InfoDialog : public QDialog
{
    Q_OBJECT
public:
    InfoDialog();
    ~InfoDialog();

private:
    QGridLayout* mainLayout;
    QLabel* disabile;
    QLabel* disabileText;
    QLabel* greenButton;
    QLabel* greenButtonText;
    QLabel* redButton;
    QLabel* redButtonText;
    QLabel* lavatrice;
    QLabel* lavatriceText;
    QLabel* letto;
    QLabel* lettoText;
    QLabel* lavori;
    QLabel* lavoriText;
};

#endif // INFODIALOG_H
