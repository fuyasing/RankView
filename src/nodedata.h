#ifndef NODEDATA_H
#define NODEDATA_H

#include <QHash>
#include <QString>

class NodeData
{
public:
    explicit NodeData();
    explicit NodeData(QString exam_name, int rank, QHash<QString,int> subject_trend);

    QString examName() const;
    void setExamName(QString name);
    int rank() const;
    void setRank(int rank);
    QHash<QString,int> subjectTrend() const;
    void setSubjectTrend(QHash<QString,int> subject_trend);

private:
    QString m_examName;
    int m_rank;
    QHash<QString,int> m_subjectTrend;
};

#endif // NODEDATA_H
