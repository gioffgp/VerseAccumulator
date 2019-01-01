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

static const QVector<QString> bookNames {
    "Genesis",          // GEN
    "Exodus",           // EX
    "Leviticus",        // LEV
    "Numbers",          // NUM
    "Deutoronomy",      // DEUT
    "Joshua",           // JOSH
    "Judges",           // JUDG
    "Ruth",             // RUTH
    "1 Samuel",         // FRST_SAM
    "2 Samuel",         // SCND_SAM
    "1 Kings",          // FRST_KINGS
    "2 Kings",          // SCND_KINGS
    "1 Chronicles",     // FRST_CHRON
    "2 Chronicles",     // SCND_CHRON
    "Ezra",             // EZRA
    "Nehemiah",         // NEH
    "Esther",           // EST
    "Job",              // JOB
    "Psalms",           // PS
    "Proverbs",         // PROV
    "Ecclesiastes",     // ECCLES
    "Song of Solomon",  // SONG
    "Isaiah",           // ISA
    "Jeremiah",         // JER
    "Lamentations",     // LAM
    "Ezekiel",          // EZEK
    "Daniel",           // DAN
    "Hosea",            // HOS
    "Joel",             // JOEL
    "Amos",             // AMOS
    "Obadiah",          // OBAD
    "Jonah",            // JONAH
    "Micah",            // MIC
    "Nahum",            // NAH
    "Habakkuk",         // HAB
    "Zephaniah",        // ZEPH
    "Haggai",           // HAG
    "Zechariah",        // ZECH
    "Malachi",          // MAL
    "Matthew",          // MATT
    "Mark",             // MARK
    "Luke",             // LUKE
    "John",             // JOHN
    "Acts",             // ACTS
    "Romans",           // ROM
    "1 Corinthians",    // FRST_COR
    "2 Corinthians",    // SCND_COR
    "Galatians",        // GAL
    "Ephesians",        // EPH
    "Philippians",      // PHIL
    "Colossians",       // COL
    "1 Thessalonians",  // FRST_THESS
    "2 Thessalonians",  // SCND_THESS
    "1 Timothy",        // FRST_TIM
    "2 Timothy",        // SCND_TIM
    "Titus",            // TITUS
    "Philemon",         // PHILEM
    "Hebrews",          // HEB
    "James",            // JAMES
    "1 Peter",          // FRST_PET
    "2 Peter",          // SCND_PET
    "1 John",           // FRST_JOHN
    "2 John",           // SCND_JOHN
    "3 John",           // THRD_JOHN
    "Jude",             // JUDE
    "Revelation",       // REV
};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    for (int i = 0; i < Verse::ZZZ_BIBLE_BOOK_QTY; ++i) {
        ui->CBBibleBook->addItem(bookNames.at(i), i);
        verses.insert(static_cast<Verse::EBookNames>(i), VerseVec());
    }

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
    const int book
            = static_cast<int>(ui->CBBibleBook->currentData().toInt());
    const unsigned short chapterNo
            = static_cast<unsigned short>(ui->SBChapter->value());
    const unsigned short verseNo
            = static_cast<unsigned short>(ui->SBVerse->value());
    const QString verseText(ui->LEVerseEntry->text());

    verses[static_cast<Verse::EBookNames>(book)].push_back(
                Verse(static_cast<Verse::EBookNames>(book), chapterNo,
                      verseNo, verseText));

    ui->LEVerseEntry->clear();
    ui->PTEAllVerses->appendPlainText(ui->CBBibleBook->currentText()
                                      + ' ' + QString::number(chapterNo)
                                      + ' ' + QString::number(verseNo)
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
