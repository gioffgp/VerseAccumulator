#include "verse.h"

Verse::Verse(EBookNames argBook, unsigned short argChapter,
             unsigned short argVerse, QString argText) :
    book{argBook},
    chapterNo{argChapter},
    verseNo{argVerse},
    text{argText}
{
}
