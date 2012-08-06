/****************************************************************************
 *  Qamus http://trigona.ca/qamus                                           *
 *  Copyright (C) 2010-2011 Benjamin Trigona-Harany                         *
 *                                                                          *
 *  This program is free software: you can redistribute it and/or modify    *
 *  it under the terms of the GNU General Public License as published by    *
 *  the Free Software Foundation, either version 3 of the License, or       *
 *  (at your option) any later version.                                     *
 *                                                                          *
 *  This program is distributed in the hope that it will be useful,         *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the            *
 *  GNU General Public License for more details.                            *
 *                                                                          *
 *  You should have received a copy of the GNU General Public License       *
 *  along with this program. If not, see <http://www.gnu.org/licenses/>.    *
 *                                                                          *
 ****************************************************************************/

#ifndef QLXXMLHANDLER_H
#define QLXXMLHANDLER_H


#include "dictxmlhandler.h"

class Lexicon;

class QlxXmlHandler: public DictXmlHandler
{
public:
    QlxXmlHandler();
    virtual ~QlxXmlHandler();

private:
    bool startDocument();
    bool startElement(const QString&, const QString&, const QString& tagString, const QXmlAttributes&);
    bool characters(const QString& str);
    bool endElement(const QString&, const QString&, const QString& tagString);
    bool endDocument();

    QString _metaId;
    QString _languageId;
    Lexeme _lexeme;
    Language _language;
    std::map<QString, Lexeme> _entry;
    std::map<QString, QString> _metadata;
    std::map<QString, QString> _transcriptionLanguages;
};

#endif // QLXXMLHANDLER_H
