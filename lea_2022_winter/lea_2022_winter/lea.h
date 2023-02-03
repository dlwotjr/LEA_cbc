#pragma once
typedef unsigned char byte;
typedef unsigned int uint32;

#define GETU32(p)(((uint32)p[0]<<24)^((uint32)p[1]<<16)^((uint32)p[2]<<8)^((uint32)p[3]))
#define PUTU32(b, x) { \
(b)[0] = (byte)((x) >> 24); \
(b)[1] = (byte)((x) >> 16); \
(b)[2] = (byte)((x) >> 8); \
(b)[3] = (byte)(x); }

class lea {
private:
	uint32 state[4]={0x00,};
	uint32 roundKey[6 * 24];
	byte pt[16] = {0x00,};
	//byte firkey[16] = { 0x0f, 0x1e, 0x2d, 0x3c, 0x4b, 0x5a, 0x69, 0x78, 0x87, 0x96, 0xa5, 0xb4, 0xc3, 0xd2, 0xe1, 0xf0 };
	uint32 keyNum[8] = {  0xc3efe9db, 0x44626b02, 0x79e27c8a, 0x78df30ec, 0x715ea49e, 0xc785da0a, 0xe04ef22a, 0xe5c40957 };
	byte ct[16]={0x00};

public:
	void byte2state(uint32* state, byte* b);
	void state2byte(uint32 state[4], byte b[16]);
	uint32 rotLeft(uint32 u, int k);
	uint32 rotRight(uint32 u, int k);
	void leaEnc(byte sstate[16], byte firkey[16]);

	void leaDec(byte sstate[16], byte firkey[16]);


	void keyExpension(byte firkey[16]);
	
};



class cbc {
private:

public:
	void print_this_Block_Result(byte* this_block);
	void CBC_ENC_kat(const char* input_file, const char* output_file);

	void CBC_ENC_mct(const char* input_file, const char* output_file);

	void CBC_ENC_mmt(const char* input_file, const char* output_file);

	void CBC_DEC_kat(const char* input_file, const char* output_file);

	void CBC_DEC_mct(const char* input_file, const char* output_file);

	void CBC_DEC_mmt(const char* input_file, const char* output_file);

	void CBC_DEC(byte** ct, byte** initalVec, byte** key, byte** pt);



};