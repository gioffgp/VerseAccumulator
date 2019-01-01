#ifndef VERSE_H
#define VERSE_H

#include <QString>

class Verse
{
public:
    enum EBookNames {
        GEN,
        EX,
        LEV,
        NUM,
        DEUT,
        JOSH,
        JUDG,
        RUTH,
        FRST_SAM,
        SCND_SAM,
        FRST_KINGS,
        SCND_KINGS,
        FRST_CHRON,
        SCND_CHRON,
        EZRA,
        NEH,
        EST,
        JOB,
        PS,
        PROV,
        ECCLES,
        SONG,
        ISA,
        JER,
        LAM,
        EZEK,
        DAN,
        HOS,
        JOEL,
        AMOS,
        OBAD,
        JONAH,
        MIC,
        NAH,
        HAB,
        ZEPH,
        HAG,
        ZECH,
        MAL,
        MATT,
        MARK,
        LUKE,
        JOHN,
        ACTS,
        ROM,
        FRST_COR,
        SCND_COR,
        GAL,
        EPH,
        PHIL,
        COL,
        FRST_THESS,
        SCND_THESS,
        FRST_TIM,
        SCND_TIM,
        TITUS,
        PHILEM,
        HEB,
        JAMES,
        FRST_PET,
        SCND_PET,
        FRST_JOHN,
        SCND_JOHN,
        THRD_JOHN,
        JUDE,
        REV,

        ZZZ_BIBLE_BOOK_QTY,
    };

    Verse() = default;
    Verse(EBookNames argBook, unsigned short argChapter,
          unsigned short argVerse, QString argText);

private:
    const EBookNames book = ZZZ_BIBLE_BOOK_QTY;
    const unsigned short chapterNo = 0;
    const unsigned short verseNo = 0;
    const QString text;
};

#endif // VERSE_H
