/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pc <pc@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 05:35:41 by pc                #+#    #+#             */
/*   Updated: 2025/03/31 05:35:52 by pc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

void error_exit(const char *flag)
{
    std::cout << flag << std::endl;
    exit (1);
}

void check_arg (char *argv)
{
    for (size_t i = 0; argv[i]; i++)
    {
        if (!isdigit(argv[i]) && argv[i] != '+' && argv[i] != '-' && argv[i] != '/' && argv[i] != '*' && argv[i] != ' ') 
            error_exit("Error: Invalid character(s) in input");
    }
}

int is_oper(char c)
{
    if (c == '+' || c == '-' || c == '*' || c == '/')
        return 1;
    return 0;
}

std::vector<std::string> split(char *argv)
{
    std::vector<std::string> tokens;
    std::stringstream ss(argv);
    std::string line;

    while (std::getline(ss, line, ' ')) {
        if (!line.empty()) {
            tokens.push_back(line);
        }
    }
    return tokens;
}

void check_syntax (std::vector<std::string> &args)
{
    std::vector<std::string>::iterator it = args.begin();
    while (it != args.end())
    {
        if (it == args.begin() && is_oper((*it)[0]))
                error_exit ("Error: Expression cannot start with an operator");
        for (size_t i = 0; (*it)[i]; i++)
        {
            if (is_oper((*it)[i]) && (*it).length() > 1)
                error_exit("Error: Invalid input");
        }
        it++;
    }
}

void apply_oper (std::vector<int> &vector, char oper)
{
    std::vector<int>::iterator it = vector.end() - 2;
    int tmp = *it;
    it++;
    if (oper == '+')
        tmp += *it;
    else if (oper == '-')
        tmp -= *it;
    else if (oper == '*')
        tmp *= *it;
    else
    {
        if (*it == 0)
            error_exit ("Error: Division by zero");
        tmp /= *it;
    }
    vector.pop_back();
    vector.pop_back();
    vector.push_back(tmp);
}

void fill_vector (std::vector<int> &vector, char *argv)
{
    std::vector<std::string> args = split(argv);
    check_syntax(args);
    std::vector<std::string>::iterator it = args.begin();
    
    while (it != args.end())
    {
        if (is_oper((*it)[0]) && vector.size() < 2)
            error_exit("Error: Not enough numbers for the operator");
        else if (is_oper((*it)[0]) && vector.size() >= 2)
            apply_oper (vector, (*it)[0]);
        else if (std::strtol((*it).c_str(), NULL, 10) >= 10)
            error_exit("Error: Operand must be a number less than 10");
        else
            vector.push_back(std::strtol((*it).c_str(), NULL, 10));
        it++;
    }
}