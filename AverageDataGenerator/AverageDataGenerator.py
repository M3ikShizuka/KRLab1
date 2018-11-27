import random
#//////////////////////////////////////////////////////////////////////////////////////////////////
#///////////////////////////////////// Variables: /////////////////////////////////////////////////
#//////////////////////////////////////////////////////////////////////////////////////////////////
out_file_name = "Average annual temperature 2008.data"
#//////////////////////////////////////////////////////////////////////////////////////////////////
#///////////////////////////////////// Classes: ///////////////////////////////////////////////////
#//////////////////////////////////////////////////////////////////////////////////////////////////
class CYear:
    months = []

class CMonth:
    name = ""
    number = 0
    days_count = 0
    days = []

    def __init__(self, name, number, days_count, temperature_max, temperature_min):
        self.name = name
        self.number = number
        self.days_count = days_count
        self.days = [CDay() for _ in range(self.days_count)]
        iStep = 0
        for day_index, day in enumerate(self.days):
            day.number = day_index
            day.month = self.number
            random.seed(iStep * 31 / 2 + 13)
            day.temperature = toFixed(random.uniform(temperature_max, temperature_min), 1)
            iStep += 1

class CDay:
    number = 0
    month = 0
    temperature = 0.0
#//////////////////////////////////////////////////////////////////////////////////////////////////
#//////////////////////////////////////// Funcs: //////////////////////////////////////////////////
#//////////////////////////////////////////////////////////////////////////////////////////////////
def main():
    year_2008 = CYear()
    init_year_2008(year_2008)
    save_data(year_2008)

def init_year_2008(year_2008):
    year_2008.months.append(CMonth("Январь", 1, 31, -31.0, -25.0))
    year_2008.months.append(CMonth("Февраль", 2, 29, -31.0, -15.0))
    year_2008.months.append(CMonth("Март", 3, 31, 10.0, -5.0))
    year_2008.months.append(CMonth("Апрель", 4, 30, 10.0, 0.0))
    year_2008.months.append(CMonth("Май", 5, 31, 15.0, 5.0))
    year_2008.months.append(CMonth("Июнь", 6, 30, 25.0, 15.0))
    year_2008.months.append(CMonth("Июль", 7, 31, 31.0, 15.0))
    year_2008.months.append(CMonth("Август", 8, 31, 25.0, 10.0))
    year_2008.months.append(CMonth("Сентябрь", 9, 30, -10.0, 0.0))
    year_2008.months.append(CMonth("Октябрь", 10, 31, -15.0, -5.0))
    year_2008.months.append(CMonth("Ноябрь", 11, 30, -25.0, -15.0))
    year_2008.months.append(CMonth("Декабрь", 12, 31, -31.0, -20.0))

def save_data(year_2008):
    buffer = ""

    all_days = []
    for month_index, month in enumerate(year_2008.months):
        for day_index, day in enumerate(month.days):
            all_days.append(day)
    
    days_count_in_year = 0
    for month in year_2008.months:
        days_count_in_year += month.days_count

    m = 0
    while m < days_count_in_year:
        n = 0
        while n < days_count_in_year:
            if all_days[m].temperature < all_days[n].temperature:
                tmp = all_days[m]
                all_days[m] = all_days[n]
                all_days[n] = tmp
            n += 1
        m += 1

    for day in all_days:
        buffer += "{0:0>2}".format(day.number) + "." + "{0:0>2}".format(day.month) + " " + format(day.temperature, ".1f") + "\n"

    write_file = open(out_file_name, "w")
    write_file.write(buffer)
    write_file.close()

def toFixed(numObj, digits=0):
    return float(f"{numObj:.{digits}f}")
#//////////////////////////////////////////////////////////////////////////////////////////////////
#//////////////////////////////////////// Code: ///////////////////////////////////////////////////
#//////////////////////////////////////////////////////////////////////////////////////////////////
main()