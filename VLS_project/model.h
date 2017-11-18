#ifndef MODEL_H
#define MODEL_H

#include <QAbstractListModel>
#include <QStringList>

class VlsStation
{
    public:
        VlsStation(const float &longitude, const float &latitude, const QString &describtion);

        float longitude() const;
        float latitude() const;
        QString describtion() const;
        void setPos(float lng, float lat) { m_longitude = lng; m_latitude = lat; }
        void setDescribtion(QString new_describtion);

    private:
        float m_longitude;
        float m_latitude;
        QString m_describtion;
};

class VlsStationModel : public QAbstractListModel
{
    Q_OBJECT
    public:
        enum VlsStationRoles {
            LongitudeRole = Qt::UserRole + 1,
            LatitudeRole,
            DescribtionRole
        };

        VlsStationModel(QObject *parent = 0);

        void addVlsStation(const VlsStation &vls_station);

        int rowCount(const QModelIndex & parent = QModelIndex()) const;

        QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

        QList<VlsStation> getVlsStations() { return m_vls_stations; }

        void setNewStations(const QList<VlsStation> new_vls_stations);
        void operationToRemoveItemAtRow(int row);

    protected:
        QHash<int, QByteArray> roleNames() const;
    private:
        QList<VlsStation> m_vls_stations;
};

#endif // MODEL_H
