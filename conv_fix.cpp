#include "conv_fix.h"
#include "stdlib.h"
#include <time.h>
using namespace std;

fix_16_13 Conv_3x3 (fix_8_6 input[9], fix_8_6 weight[9])
{
	int x, y;
	fix_16_13 result = 0;
	for (y = 0; y < 9;)
	{
#pragma HLS PIPELINE
		for (x = 0; x < 3; x++)
		{
#pragma HLS UNROLL
			result += input[x + y] * weight[x + y];
		}
		y = y + 3;
	}
	return result;
}
void Conv_fix(fix_8_6 input[25], fix_8_6 weights[9],fix_16_13 out[9])
{
#pragma HLS INTERFACE m_axi depth=25 port=input bundle=DATA
#pragma HLS INTERFACE m_axi depth=9 port=weight bundle=DATA
#pragma HLS INTERFACE m_axi depth=9 port=out bundle=DATA



#pragma HLS INTERFACE s_axilite register port=input bundle=CTRL
#pragma HLS INTERFACE s_axilite register port=weight bundle=CTRL
#pragma HLS INTERFACE s_axilite register port=out bundle=CTRL



#pragma HLS INTERFACE s_axilite register port=return bundle=CTRL
	int i_y, i_x, matrix_y, matrix_x;
	int k_num, mat_i = 0;
	fix_8_6 matrix_2[9]; // weight kernel
	fix_8_6 matrix[9];  // photo
	int matrix_index;
    int input_value_index;
	int out_pic_index;
	int pic_value_index;
top_loop:
	for (int k_num = 0; k_num < 1; k_num += 1)
	{
		for (mat_i = 0; mat_i < 9; mat_i++)// upgrade to certain kernel
		{
			matrix_2[mat_i] = weights[mat_i + k_num*9];
		}
	i_y_loop:
		for (i_y = 0; i_y < 3; i_y++)
		{
			for (i_x = 0; i_x < 3; i_x++)
			{
#pragma HLS PIPELINE
				pic_value_index = i_x + i_y * 5;
			matrix_loop:
				for (matrix_y = 0; matrix_y < 3; matrix_y++)
				{
				caculate:
					for (matrix_x = 0; matrix_x < 3; matrix_x++)
					{
						//						图片索引  0 ~ 24
					    matrix_index = matrix_x + matrix_y * 3;
						//						图片像素索引 0 ~ 1024,与matrix_x,matrix_y相关,x、y=32
						input_value_index = pic_value_index + matrix_x + matrix_y * 5;

						matrix[matrix_index] = input[input_value_index];
//						printf("matrix[%d] = %d",matrix_index,matrix[matrix_index]);
					}
				}
			    out_pic_index = i_x + i_y * 3 + k_num * 25;
				out[out_pic_index] = Conv_3x3(matrix, matrix_2);
			}
		}
	}
}
