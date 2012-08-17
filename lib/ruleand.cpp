#include "ruleand.h"

RuleAnd::RuleAnd():
    RuleBase()
{
}

RuleAnd::~RuleAnd()
{
    for (auto it = _rules.begin(); it != _rules.end(); ++it)
    {
        delete *it;
    }
}

RuleBase::TriState RuleAnd::getState() const
{
    if (!_active)
    {
        return _false;
    }

    bool hasActive = false;
    bool hasInactive = false;
    for (auto it = _rules.begin(); it != _rules.end(); ++it)
    {
        if ((*it)->isActive())
        {
            hasActive = true;
        }
        else
        {
            hasInactive = true;
        }

        if (hasActive && hasInactive)
        {
            return _partial;
        }
    }

    if (!hasActive)
    {
        return _false;
    }
    else
    {
        return _true;
    }
}
