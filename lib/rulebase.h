#ifndef RULEBASE_H
#define RULEBASE_H

#include <list>
#include <QString>

class RuleBase
{
protected:
    enum TriState
    {
        _true,
        _false,
        _partial
    };

public:
    RuleBase();
    virtual ~RuleBase();

    virtual bool isActive() const { return _active; }
    virtual TriState getState() const;

    virtual bool applyRule(QString& word) = 0;

protected:
    bool _active;
};

typedef std::list<RuleBase*> RuleList;

#endif // RULEBASE_H
