/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pc <pc@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 06:23:36 by pc                #+#    #+#             */
/*   Updated: 2025/03/28 07:35:45 by pc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main (int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Error: could not open file." << std::endl;
        return (1);
    }
    std::map<std::string, double> csv;
    std::map<size_t, std::string> txt_date;
    std::map<size_t, std::string> txt_value;
    std::ifstream data_file (argv[1]);
    std::string line;
    size_t i = 0;
    if (!data_file.is_open())
    {
        std::cerr << "Error: could not open file." << std::endl;
        return (1);
    }
    while (std::getline(data_file, line))
    {
        // std::cout << line << std::endl;
        size_t pos = line.find(" | ");
        if (pos != std::string::npos)
        {
            std::string first_part = line.substr(0, pos);
            
            // Extract the last part (after " | ")
            std::string last_part = line.substr(pos + 3);
            
            // Add to the map
            txt_date[i] = first_part;
            txt_value[i] = last_part;
        }        
        else
        {
            txt_date[i] = line;
            txt_value[i] = ""; 
        }
        i++;
    }
    for (size_t j = 0; j < i; j++)
    {
        std::cout << txt_date[j] << " " << txt_value[j] << std::endl;
    }
    
}