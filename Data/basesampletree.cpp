#include "Data/basesampletree.h"



const QString BaseSampleTree::GetName() const {return QString();}

const QVariant BaseSampleTree::ShowInfo(const int &chosenInfo) const {return QVariant();}

int BaseSampleTree::RowSize() const {return 0;}

void *BaseSampleTree::GetChild(const int &childId){return 0;}

int BaseSampleTree::GetSampleType() const{return -1;}
