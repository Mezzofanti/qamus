#include "rulebase.h"

RuleBase::RuleBase() :
    _active(true)
{
}

RuleBase::TriState RuleBase::getState() const
{
    if (_active)
    {
        return _true;
    }
    else
    {
        return _false;
    }
}
