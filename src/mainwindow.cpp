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

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QPushButton>
#include <QStandardPaths>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->CBBibleBook->addItems(QStringList(QStringList() << "Gen" << "Ex" << "Lev"));

    connect(ui->PBSave, SIGNAL(clicked(bool)),
            this, SLOT(SaveData()));

    QDir dataDir(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation));
    if (dataDir.exists() == false) {
        if (dataDir.mkpath(dataDir.path()) == false) {
            qWarning() << "Path for verse saving could not be created";
            ui->PBSave->setEnabled(false);
            return;
        }
    }

    out = new QFile(dataDir.path() + "/verses.txt", this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_PBAddVerse_clicked()
{
    const QString verseText(ui->LEVerseEntry->text());
    ui->LEVerseEntry->clear();
    ui->PTEAllVerses->appendPlainText(ui->CBBibleBook->currentText()
                                      + ' ' + ui->SBChapter->text()
                                      + ' ' + ui->SBVerse->text()
                                      + ' ' + verseText);
}

void MainWindow::SaveData()
{
    if (out->open(QIODevice::Text | QIODevice::WriteOnly) == false) {
        qWarning() << "Failed to open file";
        return;
    }
    if (out->write(ui->PTEAllVerses->toPlainText().toUtf8()) == -1) {
        qWarning() << "Failed to write data";
        out->close();
        return;
    }
    out->close();
}
