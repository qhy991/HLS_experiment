#include "iostream"
#include "ap_int.h"
#include "ap_fixed.h"
#include<stdio.h>
#include<istream>
#include <iomanip>
//#include<ap_fixed.h>
#include <ap_int.h>
using namespace std;
// define the weight and feature map size
#define FM_SIZE 8
#define WEIGHT_SIZE 8
#define BIAS_SIZE 16
#define FM_ACC_SMALL_SIZE 16
#define FM_ACC_BIG_SIZE 16
#define FM_ACC_MAX_SIZE 32

// define data type
typedef ap_fixed<32,16> fix_32_16;
typedef ap_fixed<16,11> fix_16_13;

typedef ap_fixed<8,6> fix_8_6;


void Conv_fix(fix_8_6 input[25],fix_8_6 weight[9],fix_16_13 out[9]);
