#include "heightmaptablemodel.h"

HeightMapTableModel::HeightMapTableModel(QObject *parent) : QAbstractTableModel(parent)
{
    m_data.append(QList<double>());
}

void HeightMapTableModel::resize(int cols, int rows)
{
    foreach (QList<double> row, m_data) row.clear();

    m_data.clear();

    for (int i = 0; i < rows; i++) {
        QList<double> row;
        for (int j = 0; j < cols; j++) {
            row.append(std::numeric_limits<double>::quiet_NaN());
        }
        m_data.append(row);
    }
}

QVariant HeightMapTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) return QVariant();

    if (index.row() >= m_data.count() || index.column() >= m_data[0].count()) return QVariant();

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        return QString::number(m_data[index.row()][index.column()], 'f', 3);
    }

    if (role == Qt::TextAlignmentRole) {
        return Qt::AlignCenter;
    }

    return QVariant();
}

bool HeightMapTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    m_data[index.row()][index.column()] = value.toDouble();
}

bool HeightMapTableModel::insertRow(int row, const QModelIndex &parent)
{
    m_data.insert(row, QList<double>());
}

bool HeightMapTableModel::removeRow(int row, const QModelIndex &parent)
{
    m_data.removeAt(row);
}

void HeightMapTableModel::clear()
{
    m_data.clear();
}

int HeightMapTableModel::rowCount(const QModelIndex &parent) const
{
    return m_data.count();
}

int HeightMapTableModel::columnCount(const QModelIndex &parent) const
{
    return m_data[0].count();
}

QVariant HeightMapTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) return QVariant();
    return QString::number(section + 1);
}

Qt::ItemFlags HeightMapTableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid()) return NULL;
    return QAbstractTableModel::flags(index);
}

