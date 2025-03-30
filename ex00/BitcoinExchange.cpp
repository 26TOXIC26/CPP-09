/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pc <pc@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 06:23:52 by pc                #+#    #+#             */
/*   Updated: 2025/03/30 05:45:26 by pc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int check_date(std::string date)
{
    std::string year;
    std::string month;
    std::string day;
    char *end_y;
    char *end_m;
    char *end_d;

    size_t pos = date.find('-');
    if (pos == std::string::npos)
        return 0;
    year = date.substr(0, pos);
    date = date.substr (pos + 1);
    pos = date.find('-');
    if (pos == std::string::npos)
        return 0;
    month = date.substr(0, pos);
    day = date.substr(pos + 1);
    long y = std::strtol(year.c_str(), &end_y, 10);
    long m = std::strtol(month.c_str(), &end_m, 10);
    long d = std::strtol(day.c_str(), &end_d, 10);
    if (y > 2025 || y < 2009 || *end_y || m > 12 || m < 1 || *end_m || d > 31 || d < 1 || *end_d)
        return 0;
    return 1;
}

int check_value (std::string value)
{
    if (value == "")
    {
        std::cerr << "Error: not a number." << std::endl;
        return 0;        
    }
    char *end;
    double num = std::strtod(value.c_str(), &end);
    if (*end || num < 0 || num > 1000)
    {
        if (*end)
            std::cerr << "Error: not a number." << std::endl;
        else if (num < 0)
            std::cerr << "Error: not a positive number." << std::endl;
        else if (num > 1000)
            std::cerr << "Error: too large a number." << std::endl;
        return 0;
    }
    return 1;
}

std::string find_closest (std::map<std::string, double> csv, std::string date)
{
    std::string year;
    std::string month;
    std::string day;
    size_t pos = date.find('-');
    year = date.substr(0, pos);
    date = date.substr(pos + 1);
    pos = date.find('-');
    month = date.substr(0, pos);
    day = date.substr(pos + 1);
    date = year + "-" + month + "-" + day;
    int y = std::strtol(year.c_str(), NULL, 10);
    int m = std::strtol(month.c_str(), NULL, 10);
    int d = std::strtol(day.c_str(), NULL, 10);

    while (csv.find(date) == csv.end())
    {
        if (y <= 2009 && m == 1 && d == 1)
            break;
        d--;
        if (d < 1)
        {
            m--;
            d = 31;
            if (m < 1)
            {
                m = 12;
                y--;
            }
        }
        std::stringstream y_stream;
        std::stringstream m_stream;
        std::stringstream d_stream;
        y_stream << y;
        m_stream << m;
        d_stream << d;
        year = y_stream.str();
        if (m_stream.str().length() == 1)
            month = "0" + m_stream.str();
        else
            month = m_stream.str();
        if (d_stream.str().length() == 1)
            day = "0" + d_stream.str();
        else
            day = d_stream.str();
        date = year + "-" + month + "-" + day;
    }   
    return date;
}

void fill_maps(btc &btc, size_t &i, char **argv)
{
    std::ifstream data_file (argv[1]);
    std::ifstream csv_file ("data.csv");
    if (!data_file.is_open() || !csv_file.is_open())
    {
        std::cerr << "Error: could not open file." << std::endl;
        exit (1);
    }
    std::getline(data_file, btc.line);
    while (std::getline(data_file, btc.line))
    {
        size_t pos = btc.line.find(" | ");
        if (pos != std::string::npos)
        {
            btc.txt_date[i] = btc.line.substr(0, pos);
            btc.txt_value[i] = btc.line.substr(pos + 3);
        }        
        else
        {
            btc.txt_date[i] = btc.line;
            btc.txt_value[i] = ""; 
        }
        i++;
    }
    std::getline(csv_file, btc.line);
    while (std::getline(csv_file, btc.line))
    {
        size_t pos = btc.line.find(',');
        btc.csv[btc.line.substr(0, pos)] = std::strtod(btc.line.substr(pos + 1).c_str(), NULL);
    }
    data_file.close();
    csv_file.close();
}

void print_output (btc &btc, size_t &i)
{
    for (size_t j = 0; j < i; j++)
    {
        if (check_date(btc.txt_date[j]))
        {
            if (check_value(btc.txt_value[j]))
            {
                if (btc.csv.find(btc.txt_date[j]) != btc.csv.end())
                {
                    double result = std::strtod(btc.txt_value[j].c_str(), NULL) * btc.csv[btc.txt_date[j]];
                    std::cout << btc.txt_date[j] << " => " << btc.txt_value[j] << " = " << result << std::endl;
                }
                else
                {
                    btc.txt_date[j] = find_closest (btc.csv, btc.txt_date[j]);
                    if (btc.txt_date[j] == "2009-01-01")
                        std::cerr << "Error: bad input" << std::endl;
                    else
                    {
                        double result = std::strtod(btc.txt_value[j].c_str(), NULL) * btc.csv[btc.txt_date[j]];
                        std::cout << btc.txt_date[j] << " => " << btc.txt_value[j] << " = " << result << std::endl;
                    }
                }
            }
        }
        else
            std::cerr << "Error: bad input => " << btc.txt_date[j] << std::endl;
    }
}