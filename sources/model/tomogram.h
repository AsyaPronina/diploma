#ifndef TOMOGRAM_H
#define TOMOGRAM_H

#include "interfaces/model/itomogram.h"

class Tomogram : public ITomogram
{
public:
    enum class ColorDepth: int
    {
        UNDEFINED = -1,
        _8_BIT = 1,
        _16_BIT = 2
    };

    Tomogram();
    Tomogram(unsigned char* data, size_t m_rows, size_t cols, size_t planes, ColorDepth colorDepth);
    Tomogram(const Tomogram&);
    Tomogram& operator=(const Tomogram&);
    virtual ~Tomogram();

    size_t getRowsCount() const Q_DECL_OVERRIDE;
    size_t getColumnsCount() const Q_DECL_OVERRIDE;
    size_t getPlanesCount() const Q_DECL_OVERRIDE;
    int getColorDepth() const Q_DECL_OVERRIDE;
    void *getValue(int i) const Q_DECL_OVERRIDE;
    void *getValue(int i, int j, int k) const Q_DECL_OVERRIDE;

    void setRowsCount(size_t count);
    void setColumnsCount(size_t count);
    void setPlanesCount(size_t count);
    void setColorDepth(ColorDepth bitsCount);
    void setData(unsigned char *data);
private:
    unsigned char *m_data;
    size_t m_rows, m_columns, m_planes;
    int m_colorDepth;

};

#endif //TOMOGRAM_H
