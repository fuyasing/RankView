#include "nodedata.h"

NodeData::NodeData()
{
    this->m_examName="";
    this->m_rank=0;
    this->m_subjectTrend = QHash<QString,int>();
}

NodeData::NodeData(QString exam_name, int rank, QHash<QString, int> subject_trend)
{
    this->m_examName = exam_name;
    this->m_rank = rank;
    this->m_subjectTrend = subject_trend;
}

QString NodeData::examName() const
{
    return this->m_examName;
}

void NodeData::setExamName(QString name)
{
    this->m_examName = name;
}

int NodeData::rank() const
{
    return this->m_rank;
}

void NodeData::setRank(int rank)
{
    this->m_rank = rank;
}

QHash<QString,int> NodeData::subjectTrend() const
{
    return this->m_subjectTrend;
}

void NodeData::setSubjectTrend(QHash<QString, int> subject_trend)
{
    this->m_subjectTrend = subject_trend;
}
