#include "dataProcessing.hpp"

bool DataProcessing()
{
	std::vector<std::string> vTemperatures;

	// Загрузка данных из файла
	if (!ReadData(vTemperatures))
		return false;

	DataParsing(vTemperatures);

	return true;
}

bool ReadData(std::vector<std::string>& vTemperatures)
{
	std::streampos stPosBeg = 0;
	std::string str;
    __int64 llLinesCount = 0;
    int iIndex = 0;
    // Открывем файл для чтения
    std::fstream file; //("Average annual temperature 2008.data", std::ifstream::in);
    file.open("Average annual temperature 2008.data", std::ifstream::in);
    // Проверяем открыт ли файл
    if (!file.is_open())
    {
        std::cout << "Ошибка открытия файла данных!" << std::endl;
        return false;
    }

    // Получаем количество строк в файле.
    llLinesCount = std::count(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>(), '\n');
    //std::cout << "llLinesCount: " << llLinesCount << std::endl;
    if (llLinesCount < 1)
    {   
        std::cout << "Файл данных пуст!" << std::endl;
        return false;
    }

	// Перенести каретку в начало файла.
	file.seekg(stPosBeg);
    // Изменяем размер вектору.
    vTemperatures.resize(llLinesCount);   
    while(iIndex < llLinesCount && !file.eof())
    {
        std::getline(file, vTemperatures[iIndex]);
		//std::cout << vTemperatures[iIndex].c_str() << std::endl;
        iIndex++;
    }

    // Закрываем файл
    file.close();

    return true;
}

bool DataParsing(std::vector<std::string>& vTemperatures)
{
	// Расчёт среднегодовой температуры
	float fAverageAnnualTemperature = CalculateAverageAnnualTemperature(vTemperatures);
	std::cout << "Среднегодовая температура: " << fAverageAnnualTemperature << std::endl;
	// Расчёт температур с минимальным отклонением от среднегодовой
	CalculateTemperatureDeviation(vTemperatures, fAverageAnnualTemperature);

	return true;
}

float CalculateAverageAnnualTemperature(const std::vector<std::string>& vTemperatures)
{
	size_t szTemperaturesSize = vTemperatures.size();
	float fTemperature = 0.0f;

	for (int iIndex = 0; iIndex < szTemperaturesSize; iIndex++)
	{
		std::string strData = vTemperatures[iIndex];
		std::string stTemp;
		size_t szPosOfStart = strData.find(" ", 0) + 1;
		size_t szPosOfEnd = strData.length();

		while (strData[szPosOfEnd] == '\n' || strData[szPosOfEnd] == '\r')
			szPosOfEnd--;

		stTemp = strData.substr(szPosOfStart, szPosOfEnd - szPosOfStart);
		fTemperature += atof(stTemp.c_str());
	}

	return fTemperature /= szTemperaturesSize;
}

bool CalculateTemperatureDeviation(const std::vector<std::string>& vTemperatures, const float& fAverageAnnualTemperatureOfYear)
{
	// Константа отклонения температуры
	const float fDeviation = 5.0f;
	const size_t szMonthCount = 12;
	float fArraySumTemperatureOfMonthArray[szMonthCount] = {}; // Month, temperature
	int fArrayDaysInMonth[szMonthCount] = {}; // Month, countDays
	size_t szTemperaturesSize = vTemperatures.size();

	for (int iIndex = 0; iIndex < szTemperaturesSize; iIndex++)
	{
		std::string strData = vTemperatures[iIndex];
		int iMonth = static_cast<int>(GetDataValue(eDataType::Month, strData)) - 1;
		float fTemperature = GetDataValue(eDataType::Temperature, strData);
		
		fArraySumTemperatureOfMonthArray[iMonth] += fTemperature;
		fArrayDaysInMonth[iMonth]++;
	}
	
	std::cout << "Месяцы, температура которых наименее отклоняется от среднегодовой:" << std::endl;
	for (int iMonth = 0; iMonth < szMonthCount; iMonth++)
	{
		float fAverageAnnualTemperatureOfMonth = fArraySumTemperatureOfMonthArray[iMonth] / fArrayDaysInMonth[iMonth];
		if ((fAverageAnnualTemperatureOfMonth <= fAverageAnnualTemperatureOfYear + fDeviation) && (fAverageAnnualTemperatureOfMonth >= fAverageAnnualTemperatureOfYear - fDeviation))
		{
			float fDeviationTemperatureOfMonth = fAverageAnnualTemperatureOfMonth < fAverageAnnualTemperatureOfYear ? fAverageAnnualTemperatureOfYear - fAverageAnnualTemperatureOfMonth : fAverageAnnualTemperatureOfMonth - fAverageAnnualTemperatureOfYear;
			std::cout << std::setw(2) << std::setfill('0') << iMonth + 1 << ", " << fAverageAnnualTemperatureOfMonth << ", " << fDeviationTemperatureOfMonth << std::endl;
		}
	}

	return true;
}

float GetDataValue(const eDataType& eType, const std::string& strData)
{
	size_t szPosOfStart,
		szPosOfEnd;
	std::string stTemp;

	if (eType == eDataType::Month)
	{
		// Месяц
		szPosOfStart = strData.find(".", 0) + 1;
		szPosOfEnd = strData.find(" ", 0);
	}
	else if (eType == eDataType::Temperature)
	{
		// Температура
		szPosOfStart = strData.find(" ", 0) + 1;
		szPosOfEnd = strData.length();
		while (strData[szPosOfEnd] == '\n' || strData[szPosOfEnd] == '\r')
			szPosOfEnd--;
	}

	stTemp = strData.substr(szPosOfStart, szPosOfEnd - szPosOfStart);
	return atof(stTemp.c_str());
}