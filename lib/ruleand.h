#ifndef RULEAND_H
#define RULEAND_H

#include "rulebase.h"

class RuleAnd : public RuleBase
{
public:
    RuleAnd();
    ~RuleAnd();

    TriState getState() const;
protected:
    RuleList _rules;
};

#endif // RULEAND_H
