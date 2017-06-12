#include "tomogram.h"

Tomogram::Tomogram() : m_data(nullptr),
                       m_rows(0),
                       m_columns(0),
                       m_planes(0),
                       m_colorDepth(-1)
                       { }

Tomogram::Tomogram(unsigned char* data, size_t m_rows, size_t columns, size_t planes, ColorDepth colorDepth)
                  : m_data(data),
                  m_rows(m_rows),
                  m_columns(columns),
                  m_planes(planes),
                  m_colorDepth(static_cast<int>(colorDepth))
                  { }

Tomogram::Tomogram(const Tomogram& tomogram)
{
    this->m_rows = tomogram.m_rows;
    this->m_columns = tomogram.m_columns;
    this->m_planes = tomogram.m_planes;

    int size = this->m_rows * this->m_columns * this->m_planes;
    this->m_data = new unsigned char[size];

    for (int i = 0; i < size; i++)
    {
        this->m_data[i] = tomogram.m_data[i];
    }
}

Tomogram &Tomogram::operator= (const Tomogram& tomogram)
{
    this->m_rows = tomogram.m_rows;
    this->m_columns = tomogram.m_columns;
    this->m_planes = tomogram.m_planes;

    int size = this->m_rows * this->m_columns * this->m_planes;

    delete[] this->m_data;

    this->m_data = new unsigned char[size];

    for (int i = 0; i < size; i++)
    {
        this->m_data[i] = tomogram.m_data[i];
    }

    return *this;
}

Tomogram::~Tomogram()
{
    delete[] m_data;
}

size_t Tomogram::getRowsCount() const
{
    return m_rows;
}

size_t Tomogram::getColumnsCount() const
{
    return m_columns;
}

size_t Tomogram::getPlanesCount() const
{
    return m_planes;
}

int Tomogram::getColorDepth() const
{
    return static_cast<int>(m_colorDepth);
}

void Tomogram::setRowsCount(size_t count)
{
    m_rows = count;
}

void Tomogram::setColumnsCount(size_t count)
{
    m_columns = count;
}

void Tomogram::setPlanesCount(size_t count)
{
    m_planes = count;
}

void Tomogram::setColorDepth(ColorDepth bitsCount)
{
    m_colorDepth = static_cast<int>(bitsCount);
}

void Tomogram::setData(unsigned char *data)
{
    this->m_data = data;
}

void *Tomogram::getValue(int i) const
{
    return &m_data[i * m_colorDepth];
}

void *Tomogram::getValue(int i, int j, int k) const
{
    return &m_data[(k * m_rows * m_columns + i * m_columns + j) * m_colorDepth];
}
