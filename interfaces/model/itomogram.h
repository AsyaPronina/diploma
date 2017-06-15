#ifndef ITOMOGRAM_H
#define ITOMOGRAM_H

#include <cstdlib>
#include <QVariant>

class ITomogram
{
public:
    virtual size_t getRowsCount() const = 0;
    virtual size_t getColumnsCount() const = 0;
    virtual size_t getPlanesCount() const = 0;
    virtual int getColorDepth() const = 0;
    virtual void *getValue(int i) const = 0;
    virtual void *getValue(int i, int j, int k) const = 0;
    virtual const void *getData() const = 0;
};

Q_DECLARE_METATYPE(ITomogram *)
#endif // ITOMOGRAM_H
