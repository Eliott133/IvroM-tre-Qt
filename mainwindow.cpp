#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QIntValidator>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setFixedSize(size()); // permet de fixer la fenêtre (pour cacher le fait que c'est pas responsive)

    initUI();

    connect(ui->buttonDeleteAll, &QPushButton::clicked, this, &MainWindow::clearAll);
    connect(ui->poidInput, &QLineEdit::textChanged, this, &MainWindow::updateValiderEtatBouton);
    connect(ui->validerButton, &QPushButton::clicked, this, &MainWindow::DisplayResult);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clearAll()
{
    for (QLineEdit* lineEdit : listEdit()) {
        lineEdit->clear();
    }


    ui->labelResult->clear();
    ui->labelResult->setStyleSheet("");
    ui->imageLabel->clear();
    ui->imageLabel->setPixmap(QPixmap());
}

double MainWindow::TotalNiveauAlcool(){
    QString poidValue = ui->poidInput->text().trimmed();

    double biere = CalculTauxAlcoolemieDansLeSang(ui->quantiterClBiere->text().toInt(), ExtractNumericLabelPartie(ui->degreBiere), poidValue.toInt(), FacteurWidmark());
    double vin = CalculTauxAlcoolemieDansLeSang(ui->quantiterClVin->text().toInt(), ExtractNumericLabelPartie(ui->degreVin), poidValue.toInt(), FacteurWidmark());
    double aperitif = CalculTauxAlcoolemieDansLeSang(ui->quantiterClAperitif->text().toInt(), ExtractNumericLabelPartie(ui->degreAperitif), poidValue.toInt(), FacteurWidmark());
    double customAlcool = CalculTauxAlcoolemieDansLeSang(ui->quantiterClCustom->text().toInt(), ui->degreCustom->text().toInt(), poidValue.toInt(), FacteurWidmark());

    return biere + vin + aperitif + customAlcool;
}


double MainWindow::CalculTauxAlcoolemieDansLeSang(int quantiteAlcool, int degre, int masse, double sexeValue){
    return (convertClToGramme(quantiteAlcool) * (degre / 100.0) * 0.789) / (masse * sexeValue);
}

double MainWindow::FacteurWidmark() {
    return ui->radioButtonSexeHomme->isChecked() ? 0.7 : 0.6;
}

void MainWindow::DisplayResult() {
    double tauxAlcool = TotalNiveauAlcool();
    QString formattedTaux = QString::number(tauxAlcool, 'f', 2);  // Format avec deux chiffres après la virgule
    ui->labelResult->setText(QString("Taux d'alcool : %1 g/L").arg(formattedTaux));

    if (tauxAlcool >= 0.5) {
        ui->labelResult->setStyleSheet("background-color: red; color: white;");
        QString cheminImage = "./face1.png";

        QPixmap image(cheminImage);
        QSize tailleRedimensionnee(200, 200);
        image = image.scaled(tailleRedimensionnee, Qt::KeepAspectRatio);
        if (!image.isNull()){
            ui->imageLabel->setPixmap(image);
        }
        else{
            qDebug() << "Échec du chargement de l'image depuis :";
        }

    } else {
        ui->labelResult->setStyleSheet("background-color: green; color: white;");

        QString cheminImage = "./face2.png";

        QPixmap image(cheminImage);
        QSize tailleRedimensionnee(200, 200);
        image = image.scaled(tailleRedimensionnee, Qt::KeepAspectRatio);
        if (!image.isNull()){
            ui->imageLabel->setPixmap(image);
        }
        else{
            qDebug() << "Échec du chargement de l'image depuis :";
        }
    }
}


void MainWindow::updateValiderEtatBouton() {
    QString poidsSelect = ui->poidInput->text().trimmed();
    int poids = poidsSelect.toInt();

    // Désactiver le bouton si le poids est égal à zéro ou si la saisie est vide
    ui->validerButton->setEnabled(poids != 0 && !poidsSelect.isEmpty());
}

void MainWindow::initUI(){
    ui->radioButtonSexeHomme->setChecked(true);


    QIntValidator* intValidator = new QIntValidator(this);

    for (QLineEdit* lineEdit : listEdit()) {
        lineEdit->setValidator(intValidator);
    }

    ui->validerButton->setDisabled(true);

    ui->labelResult->setText("");
    //ui->imageLabel->setText("");

    ui->imageLabel->clear();
    ui->imageLabel->setPixmap(QPixmap());  // Effacer l'image actuelle
}

int MainWindow::ExtractNumericLabelPartie(QLabel* label){

    QRegularExpression re("\\d+");
    QRegularExpressionMatch match = re.match(label->text());
    int numericPart = match.captured().toInt();
    return numericPart;
}

int MainWindow::convertClToGramme(int cl){
    return 10 * cl;
}

QList<QLineEdit*> MainWindow::listEdit(){
    QList<QLineEdit*> lineEditList;
    lineEditList.append(ui->poidInput);
    lineEditList.append(ui->quantiterClBiere);
    lineEditList.append(ui->quantiterClVin);
    lineEditList.append(ui->quantiterClAperitif);
    lineEditList.append(ui->degreCustom);
    lineEditList.append(ui->quantiterClCustom);
    return lineEditList;
}


