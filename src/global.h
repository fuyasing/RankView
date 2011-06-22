#ifndef GLOBAL_H
#define GLOBAL_H

namespace Global
{
	const int MaxRecentDBs = 5;	
	enum StudentTableCols
	{
		Student_Id = 0,
		Student_Num = 1,
		Student_Name = 2
	};
	enum ScoreTableCols
	{
		Score_Id = 0,
		Score_StudentId = 1,
		Score_ExamId = 2,
		Score_Chinese = 3,
		Score_Maths = 4,
		Score_ForeignLanguage = 5,
		Score_Physics = 6,
		Score_Chemistry = 7,
		Score_Biology = 8,
		Score_Politics = 9,
		Score_History = 10,
		Score_Geography = 11
	};
	enum ExamTableCols
	{
		Exam_Id = 0,
		Exam_Name = 1,
	};
	enum ImportDataCols
	{
		Data_StudentNum = 0,
		Data_StudentName = 1,
		Data_Chinese = 2,
		Data_Maths = 3,
		Data_ForeignLanguage = 4,
		Data_Physics = 5,
		Data_Chemistry = 6,
		Data_Biology = 7,
		Data_Politics = 8,
		Data_History = 9,
		Data_Geography = 10
	};
}

#endif
