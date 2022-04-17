#include <iostream>
#include <QFile>
#include <QTextStream>
#include "model.h"

void checkFile(){
    QFile file(":/database/database/database.txt");
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Cannot find the database file";
    }
}

void loadResidence(Model& model, int load) {
  QFile file(":/database/database/database.txt");
  if (file.open(QIODevice::ReadOnly)) {
    QTextStream in (&file);
    while (!in.atEnd()) {
      QString str = in.readLine();
      if (str.toStdString()[0] == '#' || str.toStdString()[0] == ' ')
        continue;
      QStringList line = str.split(' ');

      periodo stagione = periodo::alta;
      switch (line[7].toInt()) {
      case 0:
        stagione = periodo::bassa;
        break;

      case 1:
        stagione = periodo::media;
        break;

      case 2:
        stagione = periodo::alta;
        break;

      default:
        stagione = periodo::bassa;
      }

      status stato = status::libero;
      switch (line[8].toInt()) {
      case 0:
        stato = status::libero;
        break;
      case 1:
        stato = status::occupato;
        break;
      case 2:
        stato = status::lavori;
        break;
      default:
        stato = status::libero;
      }

      //pensione{colazione, mezza, completa};
      pensione _pensione = pensione::colazione;
      if (line[0].toInt() == 2 || line[0].toInt() == 3) {
        switch (line[10].toInt()) {
        case 0:
          _pensione = pensione::colazione;
          break;
        case 1:
          _pensione = pensione::mezza;
          break;
        case 2:
          _pensione = pensione::completa;
          break;
        default:
          _pensione = pensione::colazione;
        }
      }
      fornelli fornelli = fornelli::gas;

      if(line[0].toInt() == load){
          switch (line[0].toInt()) {
      case 1:
        switch (line[12].toInt()) {
        case 0:
          fornelli = fornelli::gas;
          break;
        case 1:
          fornelli = fornelli::induzione;
          break;
        }
        model.aggiungiStruttura(new Appartamento(line[1].toInt(), line[2].toInt(), line[3].toInt(), line[4].toInt(),
          line[5].toDouble(), line[6].toInt(), stagione, stato, line[9].toInt(), line[10].toInt(), line[11].toInt(),
          line[12].toInt(), fornelli, line[14].toInt()));
        break;

      case 2:
        model.aggiungiStruttura(new Camera(line[1].toInt(), line[2].toInt(), line[3].toInt(),
          line[4].toDouble(), line[5].toInt(), stagione, stato, line[6].toInt(), line[9].toInt(), line[10].toInt(),
          _pensione));
        break;

      case 3:
        model.aggiungiStruttura(new Suite(line[1].toInt(), line[2].toInt(), line[3].toInt(), line[4].toInt(),
          line[5].toDouble(), line[6].toInt(), stagione, stato, line[9].toInt(), line[10].toInt(), line[11].toInt(),
          _pensione, line[13].toInt(), line[14].toInt(), line[15].toInt()));
        break;

      case 4:
        model.aggiungiStruttura(new Camper(line[1].toInt(), line[2].toDouble(), line[3].toInt(), line[4].toInt(), line[5].toInt(),
          stagione, stato, line[6].toInt(), line[9].toInt(), line[10].toInt(),
          line[11].toInt(), line[12].toInt()));
        break;
      }
     }

    }
  } else
    std::cout << "file not found\n";

  file.close();

}
