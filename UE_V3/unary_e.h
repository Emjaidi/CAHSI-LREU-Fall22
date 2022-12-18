/*************************************************************
 * 
 * Unary encoding implementation file 
 * AUTHOR: MJ ASUNCION
 * DATE: 12-2-2022
 * 
*************************************************************/
#include "Data_Point.h"

#ifndef UNARY_E_H
#define UNARY_E_H

void encode(std::vector<bool>&,int,int);

double coins_flip();

bool perturb_bit();

void perturb(std::vector<bool>&);

float estimate(const int& );

void populate_sum(const std::vector<Data_Point>&, std::vector<int>&);

void populate_perturbed_sum(const std::vector<Data_Point>&, std::vector<int>&);

std::vector<Data_Point> generate_est_map(std::vector<int>, VECTWODUB);

VECTWOBOOL transpose_response(const VECTWOBOOL&);
#endif