#include "model.h"
#include <iostream>

VlsStation::VlsStation(const float &longitude, const float &latitude, const QString &describtion)
    : m_longitude(longitude), m_latitude(latitude), m_describtion(describtion)
{

}

float VlsStation::longitude() const
{
    return m_longitude;
}

float VlsStation::latitude() const
{
    return m_latitude;
}

QString VlsStation::describtion() const
{
    return m_describtion;
}

void VlsStation::setDescribtion(QString new_describtion)
{

}

VlsStationModel::VlsStationModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

void VlsStationModel::addVlsStation(const VlsStation &vls_station)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_vls_stations << vls_station;
    endInsertRows();
}

void VlsStationModel::setNewStations(const QList<VlsStation> new_vls_stations) {
    beginResetModel();
    m_vls_stations = new_vls_stations;
    endResetModel();
}

void VlsStationModel::operationToRemoveItemAtRow(int row) {
    beginRemoveRows(QModelIndex(), row, row); // no parent, one row to remove
    m_vls_stations.removeAt(row);
    //std::cout << m_vls_stations.size() << std::endl;
    endRemoveRows();
}

int VlsStationModel::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return m_vls_stations.count();
}

QVariant VlsStationModel::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() >= m_vls_stations.count())
        return QVariant();

    const VlsStation &vls_station = m_vls_stations[index.row()];
    if (role == LongitudeRole)
        return vls_station.longitude();
    else if (role == LatitudeRole)
        return vls_station.latitude();
    else if (role == DescribtionRole)
        return vls_station.describtion();
    return QVariant();
}

QHash<int, QByteArray> VlsStationModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[LongitudeRole] = "longitude";
    roles[LatitudeRole] = "latitude";
    roles[DescribtionRole] = "describtion";
    return roles;
}
