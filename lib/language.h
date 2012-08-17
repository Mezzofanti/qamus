#ifndef LANGUAGE_H
#define LANGUAGE_H

#include <QString>

#ifdef ENABLE_ICU
#include <unicode/translit.h>
#endif

class Language
{
public:
    Language();
    Language(const Language& that);
    Language& operator=(const Language& that);
    Language(Language&& that);
    Language& operator=(Language&& that);

    ~Language();
    const QString getDescription() const;
    const QString getId() const;
    const QString getIso15924() const;
    const QString getIso639_2() const;
    const QString getName() const;
    const QString getScript() const;
    void setId(const QString& id);
    void setIso15924(const QString& iso15924);
    void setIso639_2(const QString& iso639_2);
    void setDescription(const QString& description);
    void clear();
#ifdef ENABLE_ICU
    bool showTransliteration() const;
    void setTransliterator(Transliterator* const transliterator);
    const Transliterator *getTransliterator() const;
#endif

private:
    QString _id;
    QString _iso15924;
    QString _iso639_2;
#ifdef ENABLE_ICU
    QString _iso639_2string; // language name computed from _iso639_2 code
    Transliterator* _transliterator;
    bool _showTransliteration;
#endif
    QString _description;
};

#endif // LANGUAGE_H
