#include <iostream>
#include"lea.h"

void lea::byte2state(uint32* state, byte* b) {
	
	state[0] = *(uint32_t*)(b + 0);
	state[1] = *(uint32_t*)(b + 4);
	state[2] = *(uint32_t*)(b + 8);
	state[3] = *(uint32_t*)(b + 12);
	
}
void lea::state2byte(uint32 state[4], byte b[16]) {
	/*
	PUTU32(b, state[0]);
	PUTU32(b + 4, state[1]);
	PUTU32(b + 8, state[2]);
	PUTU32(b + 12, state[3]);
	*/
	*(uint32_t*)(b + 0) = state[0];
	*(uint32_t*)(b + 4) = state[1];
	*(uint32_t*)(b + 8) = state[2];
	*(uint32_t*)(b + 12) = state[3];
}
uint32 lea::rotLeft(uint32 u,int k) {
	u = (u << k) | (u >> (32 - k));
	return u;
}
uint32 lea::rotRight(uint32 u, int k) {
	u = (u >> k) | (u << (32 - k));
	return u;
}

void lea::leaEnc(byte pt[16],byte firkey[16])
{
	//uint32 state[4] = { 0x00, };
	keyExpension(firkey);
	//std::cout << std::endl; std::cout << std::endl; std::cout << std::endl;
	//std::cout <<"암호화 시작" << std::endl;
	uint32 temp = 0x00;
    /*
	std::cout << "초기 평문 출력" << std::endl;
	for (int i = 0; i < 16; i++) {
		printf("%02x, ", pt[i]);
	}*/
	//std::cout << std::endl; std::cout << std::endl; std::cout << std::endl;

	byte2state(state, pt);
	for (int i = 0; i < 24; i++) {
		temp = state[0];
		state[0] = rotLeft((state[0] ^ roundKey[i * 6]) + ((state[1] ^ roundKey[i * 6 + 1])), 9);
		state[1] = rotRight((state[1] ^ roundKey[i * 6+2]) + ((state[2] ^ roundKey[i * 6 + 3])), 5);
		state[2] = rotRight((state[2] ^ roundKey[i * 6+4]) + ((state[3] ^ roundKey[i * 6 + 5])), 3);
		state[3] = temp;
		//printf("암호화 %d번째 라운드 결과 :   %08x,   %08x,   %08x,   %08x", i, state[0], state[1], state[2], state[3]);
		//std::cout << std::endl;
	}
	//std::cout << std::endl; std::cout << std::endl; std::cout << std::endl;

	state2byte(state, ct);
	state2byte(state, pt);
	/*
	std::cout << "최종암호문" << std::endl;
	for (int i = 0; i < 16; i++) {
		printf("%02x,  ",ct[i]);
	}
	std::cout << std::endl; std::cout << std::endl; std::cout << std::endl;
	*/
}

void lea::leaDec(byte ct[16],byte firkey[16])
{
	keyExpension(firkey);
	//std::cout << std::endl; std::cout << std::endl; std::cout << std::endl;
	//std::cout << "복호화 시작" << std::endl;
	uint32 temp[4] = { 0x00, };
	uint32 state[4] = { 0x00 };
	byte2state(state, ct);
	
	for (int i = 0; i < 24; i++) {//24-i로 할 생각
		temp[0] = state[0];
		temp[1] = state[1];
		temp[2] = state[2];
		temp[3] = state[3];
		state[0] = temp[3];//ct의 3번째 32 블록이 state[0]에 들어감
		state[1] = (rotRight(temp[0], 9) - (state[0] ^ roundKey[(23 - i) * 6])) ^ roundKey[(23 - i) * 6 + 1];
		state[2] = (rotLeft(temp[1], 5) - (state[1] ^ roundKey[(23 - i) * 6 + 2]) ^ roundKey[(23 - i) * 6 + 3]);
		state[3] = (rotLeft(temp[2], 3) - (state[2] ^ roundKey[(23 - i) * 6 + 4]) ^ roundKey[(23 - i) * 6 + 5]);

		//printf("복호화 %d번째 라운드 결과 :   %08x,   %08x,   %08x,   %08x", i, state[0], state[1], state[2], state[3]);
		//std::cout << std::endl;
	}
	//std::cout << std::endl; std::cout << std::endl; std::cout << std::endl;

	state2byte(state, pt);
	state2byte(state, ct);
	/*
	std::cout << "최종복화화된 평문" << std::endl;
	for (int i = 0; i < 16; i++) {
		printf("%02x,  ", pt[i]);
	}*/
	//std::cout << std::endl; std::cout << std::endl; std::cout << std::endl;

}

void lea::keyExpension(byte firkey[16])//24*4개의 키 한 라운드에 4개
{
	uint32 k[96] = {0x00};
	uint32 sk[4] = { 0x00 };
	//make byte plaintext to uint32
	byte2state(sk, firkey);
	//printf("\nfirkey = %08X, %08X, %08X, %08X\n", sk[0], sk[1], sk[2], sk[3]);
	/*
	for (int i = 0; i < 8; i++) {
		printf("****%02x", keyNum[i]);
	}*/
	/*
	for (int i = 0; i < 4; i++) {
		printf("****%02x", sk[i]);
	}*/
	//std::cout << "키 전체 출력 " << std::endl;
	for (int i = 0; i < 24; i++) {
		sk[0] = rotLeft((uint32)(sk[0] + rotLeft(keyNum[i % 4], i)), 1);
		sk[1]= rotLeft((uint32)(sk[1] + rotLeft(keyNum[i % 4], i+1)) ,3);
		sk[2] = rotLeft((uint32)(sk[2] + rotLeft(keyNum[i % 4], i+2)), 6);
		sk[3] = rotLeft((uint32)(sk[3] + rotLeft(keyNum[i % 4], i+3)), 11);
		roundKey[6*i] = sk[0];
		roundKey[6*i+1] = sk[1];
		roundKey[6*i+2] = sk[2];
		roundKey[6*i+3] = sk[1];
		roundKey[6*i+4] = sk[3];
		roundKey[6*i+5] = sk[1];
		//printf("%d번째 키 :   %08x,   %08x,   %08x,   %08x,   %08x,   %08x ",i, roundKey[6*i], roundKey[6*i+1], roundKey[6*i+2], roundKey[6*i+3], roundKey[6*i + 4], roundKey[6*i + 5]);
		//std::cout << std::endl;
	}	
}

