#include "FilmDB.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

FilmDB::FilmDB() {
    if (openDatabase()) {
        initializeDatabase();
    }
}

FilmDB::~FilmDB() {
    if (db.isOpen()) {
        db.close();
    }
}

bool FilmDB::openDatabase() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(DB_FILENAME);
    if (!db.open()) {
        qDebug() << "Failed to open database:" << db.lastError().text();
        return false;
    }
    return true;
}

void FilmDB::initializeDatabase() {
    QSqlQuery query(db);

    // Создание таблицы, если её нет
    query.exec("CREATE TABLE IF NOT EXISTS films ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "title TEXT NOT NULL, "
               "genre TEXT NOT NULL, "
               "rating INTEGER NOT NULL, "
               "duration INTEGER NOT NULL)");

    // Проверка, есть ли данные
    query.exec("SELECT COUNT(*) FROM films");
    if (query.next() && query.value(0).toInt() == 0) {
        // Вставка данных, если таблица пуста
        query.exec("INSERT INTO films (title, genre, rating, duration) VALUES "
                   "('Inception', 'Sci-Fi', 9, 148),"
                   "('The Dark Knight', 'Action', 9, 152),"
                   "('Mad Max: Fury Road', 'Action', 8, 120),"
                   "('The Hangover', 'Comedy', 7, 100),"
                   "('Superbad', 'Comedy', 7, 113),"
                   "('The Godfather', 'Drama', 9, 175),"
                   "('Schindler''s List', 'Drama', 9, 195),"
                   "('Joker', 'Drama', 8, 122),"
                   "('Parasite', 'Thriller', 9, 132),"
                   "('Get Out', 'Horror', 8, 104)");

        if (query.lastError().isValid()) {
            qDebug() << "Failed to insert data:" << query.lastError().text();
        } else {
            qDebug() << "Data inserted successfully";
        }
    } else {
        qDebug() << "Data already exists in the database.";
    }
}

QList<FilmDB::Film> FilmDB::queryFilms(const QString& condition) {
    QList<Film> films;
    QSqlQuery query(db);

    QString queryString = "SELECT title, genre, rating, duration FROM films WHERE " + condition;
    if (query.exec(queryString)) {
        while (query.next()) {
            Film film;
            film.title = query.value(0).toString();
            film.genre = query.value(1).toString();
            film.rating = query.value(2).toInt();
            film.duration = query.value(3).toInt();
            films.append(film);
        }
    } else {
        qDebug() << "Query failed:" << query.lastError().text();
    }
    return films;
}

QList<QString> FilmDB::getGoodFilmsOfGenre(int rating, const QString& genre) {
    QString condition = QString("genre = '%1' AND rating >= %2").arg(genre).arg(rating);
    QList<Film> films = queryFilms(condition);

    QList<QString> titles;
    for (const Film& film : films) {
        titles.append(film.title);
    }
    return titles;
}

QList<QString> FilmDB::getFilmsOfGenreLessThan(int time, const QString& genre) {
    QString condition = QString("genre = '%1' AND duration <= %2").arg(genre).arg(time);
    QList<Film> films = queryFilms(condition);

    QList<QString> titles;
    for (const Film& film : films) {
        titles.append(film.title);
    }
    return titles;
}

QList<QString> FilmDB::getFilmsLessThan(int time) {
    QString condition = QString("duration <= %1").arg(time);
    QList<Film> films = queryFilms(condition);

    QList<QString> titles;
    for (const Film& film : films) {
        titles.append(film.title);
    }
    return titles;
}

int FilmDB::countGenre(const QString& genre) {
    QString condition = QString("genre = '%1'").arg(genre);
    QList<Film> films = queryFilms(condition);
    return films.size();
}
