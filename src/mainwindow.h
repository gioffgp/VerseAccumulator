/*
 * Copyright 2018 Christoph Prasser
 *
 * This file is part of VerseAccumulator.
 *
 *  VerseAccumulator is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  VerseAccumulator is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with VerseAccumulator.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "verse.h"

#include <QFile>
#include <QMainWindow>
#include <QMap>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_PBAddVerse_clicked();
    void SaveData();

private:
    using VerseVec = QVector<Verse>;
    using BookMap = QMap<Verse::EBookNames, VerseVec>;

    QFile *out;
    Ui::MainWindow *ui;
    BookMap verses;
};

#endif // MAINWINDOW_H
