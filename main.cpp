#include <QCoreApplication>
#include <QDebug>
#include "FilmDB.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    FilmDB db;

    qDebug() << "Films with rating >= 7 and genre 'Action':";
    QList<QString> goodActionFilms = db.getGoodFilmsOfGenre(7, "Action");
    for (const QString& title : goodActionFilms) {
        qDebug() << title;
    }

    qDebug() << "Films of genre 'Comedy' with duration <= 110 minutes:";
    QList<QString> shortComedies = db.getFilmsOfGenreLessThan(110, "Comedy");
    for (const QString& title : shortComedies) {
        qDebug() << title;
    }

    qDebug() << "Films with duration <= 120 minutes:";
    QList<QString> HoursFilms = db.getFilmsLessThan(120);
    for (const QString& title : HoursFilms) {
        qDebug()<< title;
    }

    qDebug() << "Total number of 'Drama' films:";
    qDebug() << db.countGenre("Drama");

    return a.exec();
}
