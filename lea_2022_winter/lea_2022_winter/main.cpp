#include"lea.h"
#include<iostream>

int main() {
	cbc c;
	/*
	const char* CBC_input_file1 = "C:\\Users\\82103\\source\\repos\\lea_2022_winter\\lea_2022_winter\\LEA128(CBC)KAT.txt";
	const char* CBC_output_file1 = "CBC cypertext.bin";
	const char* CBC_output_file1_1 = "CBC pt_KAT.bin";

	c.CBC_ENC_kat(CBC_input_file1, CBC_output_file1);
	c.CBC_DEC_kat(CBC_input_file1, CBC_output_file1_1);
	*/
	
	const char* CBC_input_file2 = "C:\\Users\\82103\\source\\repos\\lea_2022_winter\\lea_2022_winter\\LEA128(CBC)MCT.txt";
	const char* CBC_output_file2 = "CBC cypertext_mct.bin";
	const char* CBC_output_file2_1 = "CBC cypertext_dec_mct.bin";
	c.CBC_ENC_mct(CBC_input_file2, CBC_output_file2);
	//c.CBC_DEC_mct(CBC_input_file2, CBC_output_file2_1);
	

	/*
	const char* CBC_input_file3 = "C:\\Users\\82103\\source\\repos\\lea_2022_winter\\lea_2022_winter\\LEA128(CBC)MMT.txt";
	const char* CBC_output_file3 = "CBC cypertext_mmt.bin";
	const char* CBC_output_file3_1 = "CBC cypertext_dec_mmt.bin";
	c.CBC_ENC_mmt(CBC_input_file3, CBC_output_file3);
	c.CBC_DEC_mmt(CBC_input_file3, CBC_output_file3_1);
	*/
}