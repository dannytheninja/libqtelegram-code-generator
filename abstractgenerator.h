#ifndef ABSTRACTGENERATOR_H
#define ABSTRACTGENERATOR_H

#include <QStringList>
#include <QRegExp>
#include <QMap>
#include <QSet>

#define GENERATOR_SIGNATURE(COMMENT_SIGN) \
    COMMENT_SIGN " This file generated by libqtelegram-code-generator.\n" \
    COMMENT_SIGN " You can download it from: https://github.com/Aseman-Land/libqtelegram-code-generator\n" \
    COMMENT_SIGN " DO NOT EDIT THIS FILE BY HAND -- YOUR CHANGES WILL BE OVERWRITTEN\n\n"

namespace GeneratorTypes
{
    class QtTypeStruct
    {
    public:
        QtTypeStruct(): constRefrence(false), qtgType(false), isList(false), innerType(0){}
//        virtual ~QtTypeStruct() { if(innerType) delete innerType; }
        QString name;
        QString html;
        QStringList includes;
        bool constRefrence;
        bool qtgType;
        bool isList;
        QString defaultValue;
        QString originalType;
        QtTypeStruct *innerType;

        bool operator ==(const QtTypeStruct &b) {
            return name == b.name &&
                   includes == b.includes &&
                   constRefrence == b.constRefrence &&
                   defaultValue == b.defaultValue &&
                   originalType == b.originalType &&
                   isList == b.isList;
        }
    };

    class ArgStruct
    {
    public:
        ArgStruct() : flagValue(0), flagDedicated(false), isFlag(false) {}
        QString flagName;
        int flagValue;
        bool flagDedicated;
        bool isFlag;
        GeneratorTypes::QtTypeStruct type;
        QString argName;

        bool operator ==(const ArgStruct &b) {
            return flagName == b.flagName &&
                   type == b.type &&
                   flagValue == b.flagValue &&
                   argName == b.argName &&
                   flagDedicated == b.flagDedicated &&
                   isFlag == b.isFlag;
        }
    };

    class TypeStruct
    {
    public:
        QString typeName;
        QString typeCode;
        QList<ArgStruct> args;
        QString code;
    };

    class FunctionStruct
    {
    public:
        TypeStruct type;
        QString functionName;
        QString className;
        QtTypeStruct returnType;
        QString code;
    };
}

class AbstractGenerator
{
protected:
    QString shiftSpace(const QString &str, int level);
    QString fixDeniedNames(const QString &str);
    QString fixTypeName(const QString &str);
    QString cammelCaseType(const QString &str);
    QString usCaseType(const QString &str);
    QString undoCase(const QString &str);
    QString classCaseType(const QString &str);
    QString unclassCaseType(const QString &str);
    GeneratorTypes::QtTypeStruct translateType(const QString &type, bool addNameSpace = false, const QString &prePath = QString(), const QString &postPath = QString(), const QString &classPreName = QString());
    QMap<QString, QList<GeneratorTypes::TypeStruct> > extractTypes(const QString &data, QString objectsPostPath = QString(), const QString &objectsPrePath = QString(), const QString &customHeader = QString(), const QString &classPreName = QString());
    QMap<QString, QList<GeneratorTypes::FunctionStruct> > extractFunctions(const QString &data);
};

#endif // ABSTRACTGENERATOR_H
