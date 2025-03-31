/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pc <pc@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 06:26:45 by pc                #+#    #+#             */
/*   Updated: 2025/03/31 05:37:38 by pc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

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

void error_exit(const char *flag);
void check_arg (char *argv);
int is_oper(char c);
std::vector<std::string> split(char *argv);
void check_syntax (std::vector<std::string> &args);
void apply_oper (std::vector<int> &vector, char oper);
void fill_vector (std::vector<int> &vector, char *argv);
#endif