/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pc <pc@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 06:23:40 by pc                #+#    #+#             */
/*   Updated: 2025/03/29 17:02:10 by pc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <new>
#include <exception>
#include <stdexcept>
#include <vector>
#include <list>
#include <map>
#include <stack>
#include <algorithm>
#include <iterator>
#include <limits>
#include <typeinfo>
#include <cctype>
#include <iomanip>
#include <sstream>

typedef struct btc
{
    std::map<std::string, double> csv;
    std::map<size_t, std::string> txt_date;
    std::map<size_t, std::string> txt_value;
    std::string line;
}   btc;

std::string find_closest (std::map<std::string, double> csv, std::string date);
int check_value (std::string value);
int check_date(std::string date);
void fill_maps(btc &btc, size_t &i, char **argv);
void print_output (btc &btc, size_t &i);


#endif