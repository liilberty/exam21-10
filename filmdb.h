#ifndef FILMDB_H
#define FILMDB_H

#include <QString>
#include <QList>
#include <QSqlDatabase>

#define DB_FILENAME "films.db"

class FilmDB {
public:
    FilmDB();
    ~FilmDB();

    QList<QString> getGoodFilmsOfGenre(int rating, const QString& genre);
    QList<QString> getFilmsOfGenreLessThan(int time, const QString& genre);
    QList<QString> getFilmsLessThan(int time);
    int countGenre(const QString& genre);

private:
    struct Film {
        QString title;
        QString genre;
        int rating;
        int duration;
    };

    bool openDatabase();
    void initializeDatabase(); // Метод для инициализации и заполнения базы
    QList<Film> queryFilms(const QString& condition); // Вспомогательный метод для запросов

    QSqlDatabase db;
};

#endif // FILMDB_H
