#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "./ui_mainwindow.h"
#include <QPixmap>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // Add this declaration
    void clearAll();
    double TotalNiveauAlcool();
    int ConvertClToGramme(QString);
    double CalculTauxAlcoolemieDansLeSang(int, int, int, double);
    double FacteurWidmark();
    void DisplayResult();
    void updateValiderEtatBouton();
    void initUI();
    int ExtractNumericLabelPartie(QLabel*);
    int convertClToGramme(int);
    QList<QLineEdit*> listEdit();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
