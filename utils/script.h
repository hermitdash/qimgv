#ifndef SCRIPT_H
#define SCRIPT_H

#include <QMetaType>
#include <QString>

class Script {
public:
    Script();
    Script(QString _path, bool _blocking);
    QString command;
    bool blocking;
};

Q_DECLARE_METATYPE(Script)

#endif // SCRIPT_H
