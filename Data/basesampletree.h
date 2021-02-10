#ifndef BASESAMPLETREE_H
#define BASESAMPLETREE_H

#include "QString"
#include "QVariant"

class BaseSampleTree{
public:
    const virtual QString GetName() const;
    const virtual QVariant ShowInfo(const int &chosenInfo) const;
    virtual int RowSize() const;
    virtual void *GetChild(const int &childId);
    virtual int GetSampleType() const;
};

#endif // BASESAMPLETREE_H
