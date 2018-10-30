#pragma once
#include "head.hpp"

enum eDataType
{
	Month = 0,
	Temperature
};

bool DataProcessing();
bool ReadData(std::vector<std::string>& vTemperatures);
bool DataParsing(std::vector<std::string>& vTemperatures);
float CalculateAverageAnnualTemperature(const std::vector<std::string>& vTemperatures);
bool CalculateTemperatureDeviation(const std::vector<std::string>& vTemperatures, const float& fAverageAnnualTemperatureOfYear);
float GetDataValue(const eDataType& eType, const std::string& strData);