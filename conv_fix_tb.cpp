#include"conv_fix.h"

int main(){
	fix_8_6 input[25];
	fix_8_6 weight[9];
	fix_16_13 out[9];
	int n = 0;
	for(n=0;n<25;n++){
		input[n]=n+0.5;
	}
	for(n=0;n<9;n++){
			weight[n]=n+0.5;
		}
	Conv_fix(input,weight,out);
	for(n=0;n<9;n++){
		cout << "The value of out:\t"<<out[n]<<'\n';
			}
}
