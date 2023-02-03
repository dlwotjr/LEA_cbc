#define _CRT_SECURE_NO_WARNINGS
#include"lea.h"
#include<fstream>
#include <iostream>
#include<string.h>
using namespace std;

bool isHex(char ch) {//(아래 해당값만 true(1))
    return ((ch >= '0') && (ch <= '9')) ||
        ((ch >= 'A') && (ch <= 'F')) ||
        ((ch >= 'a') && (ch <= 'f'))||
        ch=='0';
}
byte Hex2Digit(char ch) {
    if (!isHex(ch)) {
        cout << ch << " is not a hex value." << endl;
        return -1; //의미없는 출력
    }
    if ((ch >= '0') && (ch <= '9')) {
        return  ch - '0'; // 예: '7' - '4' = 3
    }
    else if ((ch >= 'A') && (ch <= 'F')) {
        return ch - 'A' + 10;
    }
    else if ((ch >= 'a') && (ch <= 'f')) {
        return ch - 'a' + 10;
    }
    cout << "Unknown error." << endl;
    return -1;
}
byte Hex2Byte(const char h[2]) {
    byte upper, lower;
    upper = h[0];
    lower = h[1];
    if ((!isHex(upper)) || (!isHex(lower))) {
        cout << "Hex Error" << endl;
        return -1;
    }
    return (byte)(Hex2Digit(upper) * 16 + Hex2Digit(lower));
}
void Hex2Array(const char* hex_str, int hex_len, byte barr[]) {
    char h[2];
    byte b_value;
    for (int i = 0; i < hex_len / 2; i++) {
        h[0] = hex_str[2 * i];
        h[1] = hex_str[2 * i + 1];
        b_value = Hex2Byte(h);
        barr[i] = b_value;
    }
}
void print_b_array(byte b_arr[], int len, const char* pStr) {
    if (pStr != nullptr) {
        printf("%s = ", pStr);
    }
    for (int i = 0; i < len; i++) {
        printf("%02x ", b_arr[i]);
    }
    printf("\n");
}
void cbc::print_this_Block_Result(byte* this_block)
{
    for (int i = 0; i < 16; i++) {
        printf("% 02x   ", this_block[i]);
    }
    cout << endl;
}

void getFileMem(FILE* fin,byte* key,byte* initalVec, byte* pt, byte* ct_check) {

    byte read_buf[100] = { 0 };
    byte read_tmp[100] = { 0 };

        fscanf(fin, "KEY = ", read_buf);
        for (int cnt_j = 0; cnt_j < 16; cnt_j++)
        {
            fscanf(fin, "%02X", &read_tmp[0]);
            key[cnt_j] = read_tmp[0];
        }
        fscanf(fin, "\n", read_buf);

        fscanf(fin, "IV = ", read_buf);
        for (int cnt_j = 0; cnt_j < 16; cnt_j++)
        {
            fscanf(fin, "%02X", &read_tmp[0]);
            initalVec[cnt_j] = read_tmp[0];
        }
        fscanf(fin, "\n", read_buf);

        fscanf(fin, "PT = ", read_buf);
        for (int cnt_j = 0; cnt_j < 16; cnt_j++)
        {
            fscanf(fin, "%02X", &read_tmp[0]);
            pt[cnt_j] = read_tmp[0];
        }
        fscanf(fin, "\n", read_buf);

        fscanf(fin, "CT = ", read_buf);
        cout << "cypher text answer" << endl;
        for (int cnt_j = 0; cnt_j < 16; cnt_j++)
        {
            fscanf(fin, "%02X", &read_tmp[0]);
            ct_check[cnt_j] = read_tmp[0];

            printf("%02X ,", ct_check[cnt_j]);

        }cout << endl;
        fscanf(fin, "\n\n", read_buf);
    


   // char* keybuf, * ivbuf, * ptbuf, * ctbuf, buf[4][100];
   // char keybuf2[STRSIZE + 1] = { 0, }, ivbuf2[STRSIZE + 1] = { 0, }, ptbuf2[STRSIZE + 1] = { 0, }, ctbuf2[STRSIZE + 1] = { 0, };
   // if ((keybuf = fgets(buf[0], 50, fin)) != NULL) cout << keybuf << endl;
   // else printf("key를 제대로 받아오지 못하고 있음\n");
   // memcpy(keybuf2, keybuf + KEY_OFFSET, STRSIZE);
   // //cout << keybuf2 << endl;
   // if ((ivbuf = fgets(buf[1], 50, fin)) != NULL) cout << ivbuf << endl;
   // else printf("iv를 제대로 받아오지 못하고 있음\n");
   // memcpy(ivbuf2, ivbuf + OTHER_OFFSET, STRSIZE);
   // if ((ptbuf = fgets(buf[2], 50, fin)) != NULL) cout << ptbuf << endl;
   // else printf("pt를 제대로 받아오지 못하고 있음\n");
   // memcpy(ptbuf2, ptbuf + OTHER_OFFSET, STRSIZE);
   // if ((ctbuf = fgets(buf[3], 50, fin)) != NULL) cout << ctbuf << endl;
   // else printf("ct를 제대로 받아오지 못하고 있음\n");
   // memcpy(ctbuf2, ctbuf + OTHER_OFFSET, STRSIZE);
   // char line[500];
   // printf("fgetc: %d\n", fgetc(fin));
   //// printf("fgetc: %d\n", fgetc(fin));

   // Hex2Array(keybuf2, STRSIZE, key);
   // Hex2Array(ivbuf2, STRSIZE, initalVec);
   // Hex2Array(ptbuf2, STRSIZE, pt);
   // Hex2Array(ctbuf2, STRSIZE, ct_check);
}

void getFileMem_mct(FILE* fin, byte key[16], byte initalVec[16], byte pt[16], byte ct_check[16], int count) {

    byte read_buf[100] = { 0 };
    byte read_tmp[100] = { 0 };

    //fscanf(fin, "COUNT = %d", count,read_buf);

    fscanf(fin, "COUNT = ", read_buf);
    fscanf(fin, "%d", &read_tmp[0]);
    fscanf(fin, "\n", read_buf);


    fscanf(fin, "KEY = ", read_buf);
    for (int cnt_j = 0; cnt_j < 16; cnt_j++)
    {
        fscanf(fin, "%02X", &read_tmp[0]);
        key[cnt_j] = read_tmp[0];
    }
    fscanf(fin, "\n", read_buf);

    fscanf(fin, "IV = ", read_buf);
    for (int cnt_j = 0; cnt_j < 16; cnt_j++)
    {
        fscanf(fin, "%02X", &read_tmp[0]);
        initalVec[cnt_j] = read_tmp[0];
    }
    fscanf(fin, "\n", read_buf);

    fscanf(fin, "PT = ", read_buf);
    for (int cnt_j = 0; cnt_j < 16; cnt_j++)
    {
        fscanf(fin, "%02X", &read_tmp[0]);
        pt[cnt_j] = read_tmp[0];
    }
    fscanf(fin, "\n", read_buf);

    fscanf(fin, "CT = ", read_buf);
    cout << "cypher text answer" << endl;
    for (int cnt_j = 0; cnt_j < 16; cnt_j++)
    {
        fscanf(fin, "%02X", &read_tmp[0]);
        ct_check[cnt_j] = read_tmp[0];

        printf("%02X ,", ct_check[cnt_j]);

    }cout << endl;
    fscanf(fin, "\n\n", read_buf);
}

void getFileMem_dec_kat(FILE* fin, byte* key, byte* initalVec, byte* pt, byte* ct_check) {

    byte read_buf[100] = { 0 };
    byte read_tmp[100] = { 0 };

    fscanf(fin, "KEY = ", read_buf);
    for (int cnt_j = 0; cnt_j < 16; cnt_j++)
    {
        fscanf(fin, "%02X", &read_tmp[0]);
        key[cnt_j] = read_tmp[0];
    }
    fscanf(fin, "\n", read_buf);

    fscanf(fin, "IV = ", read_buf);
    for (int cnt_j = 0; cnt_j < 16; cnt_j++)
    {
        fscanf(fin, "%02X", &read_tmp[0]);
        initalVec[cnt_j] = read_tmp[0];
    }
    fscanf(fin, "\n", read_buf);

    fscanf(fin, "PT = ", read_buf);
    cout << "decrypted text answer" << endl;
    for (int cnt_j = 0; cnt_j < 16; cnt_j++)
    {
        fscanf(fin, "%02X", &read_tmp[0]);
        pt[cnt_j] = read_tmp[0];
        printf("%02X ,", pt[cnt_j]);
    }
    fscanf(fin, "\n", read_buf);

    fscanf(fin, "CT = ", read_buf);
    
    for (int cnt_j = 0; cnt_j < 16; cnt_j++)
    {
        fscanf(fin, "%02X", &read_tmp[0]);
        ct_check[cnt_j] = read_tmp[0];

    }cout << endl;
    fscanf(fin, "\n\n", read_buf);

}

void getFileMem_dec_mct(FILE* fin, byte key[16], byte initalVec[16], byte pt[16], byte ct_check[16], int count) {

    byte read_buf[100] = { 0 };
    byte read_tmp[100] = { 0 };

    //fscanf(fin, "COUNT = %d", count,read_buf);

    fscanf(fin, "COUNT = ", read_buf);
    fscanf(fin, "%d", &read_tmp[0]);
    fscanf(fin, "\n", read_buf);


    fscanf(fin, "KEY = ", read_buf);
    for (int cnt_j = 0; cnt_j < 16; cnt_j++)
    {
        fscanf(fin, "%02X", &read_tmp[0]);
        key[cnt_j] = read_tmp[0];
    }
    fscanf(fin, "\n", read_buf);

    fscanf(fin, "IV = ", read_buf);
    for (int cnt_j = 0; cnt_j < 16; cnt_j++)
    {
        fscanf(fin, "%02X", &read_tmp[0]);
        initalVec[cnt_j] = read_tmp[0];
    }
    fscanf(fin, "\n", read_buf);

    fscanf(fin, "PT = ", read_buf);
    cout << "decrypted text answer" << endl;
    for (int cnt_j = 0; cnt_j < 16; cnt_j++)
    {
        fscanf(fin, "%02X", &read_tmp[0]);
        pt[cnt_j] = read_tmp[0];
        printf("%02X ,", pt[cnt_j]);
    }
    fscanf(fin, "\n", read_buf);

    fscanf(fin, "CT = ", read_buf);
   
    for (int cnt_j = 0; cnt_j < 16; cnt_j++)
    {
        fscanf(fin, "%02X", &read_tmp[0]);
        ct_check[cnt_j] = read_tmp[0];

    }cout << endl;
    fscanf(fin, "\n\n", read_buf);
}



void cbc::CBC_ENC_kat(const char* input_file, const char* output_file)
{
    int count = 1;
    byte key[16] = { 0x00 };
    byte initalVec[16] = { 0x00 };
    byte pt[16] = { 0x00, };
    byte ct_check[16] = { 0x00 };
    FILE* fin = NULL;
    ofstream fout(output_file, ios::binary);
    fin = fopen(input_file, "r");
    if (fin == NULL) {
        fprintf(stderr, "fopen failed\n");
        return;
    }
    /*
#define STRSIZE 32
#define KEY_OFFSET 6
#define OTHER_OFFSET 5
*/
    byte read_buf[100] = { 0 };
    byte read_tmp[100] = { 0 };
    //키 inVec pt ct순서
    while (!feof(fin)) {
       //key
        //fscanf_s(fin, "%s%s%s", line[0],line[1],line[2]);
        //if (line[2][0] == 0)printf("key를 제대로 받아오지 못하고 있음\n");
        //Hex2Array(line[2], sizeof(line[2]), key);
        ////iv
        //fscanf_s(fin, "%s%s%s", line[0], line[1], line[2]);
        //if (line[2] == "NULL")printf("iv를 제대로 받아오지 못하고 있음\n");
        //Hex2Array(line[2], sizeof(line[2]), initalVec);
        ////pt  
        //fscanf_s(fin, "%s%s%s", line[0], line[1], line[2]);
        //if (line[2] == "NULL")printf("pt를 제대로 받아오지 못하고 있음\n");
        //Hex2Array(line[2], sizeof(line[2]), pt);
        /*
        char* keybuf, * ivbuf, * ptbuf, *ctbuf, buf[4][100];
        char keybuf2[STRSIZE+1] = { 0, }, ivbuf2[STRSIZE+1] = { 0, }, ptbuf2[STRSIZE+1] = { 0, }, ctbuf2[STRSIZE + 1] = { 0, };
        if ((keybuf = fgets(buf[0], 50, fin)) != NULL) cout << keybuf << endl;
        else printf("key를 제대로 받아오지 못하고 있음\n");
        memcpy(keybuf2, keybuf + KEY_OFFSET, STRSIZE);
        cout << keybuf2 << endl;

        if ((ivbuf = fgets(buf[1], 50, fin)) != NULL) cout << ivbuf << endl;
        else printf("iv를 제대로 받아오지 못하고 있음\n");
        memcpy(ivbuf2, ivbuf + OTHER_OFFSET, STRSIZE);

        if ((ptbuf = fgets(buf[2], 50, fin)) != NULL) cout << ptbuf << endl;
        else printf("pt를 제대로 받아오지 못하고 있음\n");
        memcpy(ptbuf2, ptbuf + OTHER_OFFSET, STRSIZE);

        //
        cout << strlen((const char *)keybuf) << endl;
        cout << keybuf2 << endl;
        cout << ivbuf2 << endl;
        cout << ptbuf2 << endl;

        cout << endl;
       
        Hex2Array(keybuf2, STRSIZE, key);
        Hex2Array(ivbuf2, STRSIZE, initalVec);
        Hex2Array(ptbuf2, STRSIZE, pt);
        */
       getFileMem(fin, key, initalVec, pt, ct_check);
        /*

        fscanf(fin, "KEY = ", read_buf);
        for (int cnt_j = 0; cnt_j < 16; cnt_j++)
        {
            fscanf(fin, "%02X", &read_tmp[0]);
            key[cnt_j] = read_tmp[0];
            printf("\nKEY   %02X", key[cnt_j]);
        }
        fscanf(fin, "\n", read_buf);

        fscanf(fin, "IV = ", read_buf);
        for (int cnt_j = 0; cnt_j < 16; cnt_j++)
        {
            fscanf(fin, "%02X", &read_tmp[0]);
            initalVec[cnt_j] = read_tmp[0];
            printf("\nIV   %02X", initalVec[cnt_j]);
        }
        fscanf(fin, "\n", read_buf);

        fscanf(fin, "PT = ", read_buf);
        for (int cnt_j = 0; cnt_j < 16; cnt_j++)
        {
            fscanf(fin, "%02X", &pt[cnt_j]);
            //fscanf(fin, "%02X", &read_tmp[0]);
           // pt[cnt_j] = read_tmp[0];
            printf("\npt   %02X", pt[cnt_j]);
        }
        fscanf(fin, "\n", read_buf);

        fscanf(fin, "CT = ", read_buf);
        for (int cnt_j = 0; cnt_j < 16; cnt_j++)
        {
            fscanf(fin, "%02X", &read_tmp[0]);
            ct_check[cnt_j] = read_tmp[0];
            printf("\nct   %02X", ct_check[cnt_j]);

        }
        fscanf(fin, "\n\n", read_buf);

       */


        int block_Count = (sizeof(pt)) / 16 + 1;//pt의 길이를 받음
        byte** block = new byte * [block_Count];
        for (int i = 0; i < block_Count; i++) {
            block[i] = new byte[16];
        }

        for (int i = 0; i < sizeof(pt); i++) {
            block[i / 16][i % 16] = pt[i];
           // printf("*pt[%d]: %02x\n", i, pt[i]);
          // printf("**block[%d][%d]: %02x\n", i/16,i%16, block[i / 16][i % 16]);

        }
        //패딩
        int remainder = sizeof(pt)  - (block_Count - 1) * 16;
       // printf("sizeof(pt) : %d", sizeof(pt));
        //printf("remainder : %d",remainder );

        if (remainder == 0) {
            block[block_Count - 1][0] = 0x80;
            for (int i = 1; i < 16; i++) {
                block[block_Count - 1][i] = 0x00;
            }
        }
        else {
            block[block_Count - 1][remainder] = 0x80;
            for (int i = remainder + 1; i < 16; i++) {
                block[block_Count - 1][i] = 0x00;
            }
        }
        /*
        cout << "whole PlainText by block" << endl;
        for (int i = 0; i < block_Count; i++) {
            for (int j = 0; j < 16; j++) {
                printf("%02x    ", block[i][j]);
            }
            cout << endl;
        }cout << endl;
        */
   
        //처음엔 벡터와의 연산임
        for (int i = 0; i < 16; i++) {
            block[0][i] ^= initalVec[i];
            //printf("[*] %02x\n", block[0][i] ^ initalVec[i]);
        }
        /*
        cout << "첫 블록 initalVector와의 연산 결과" << endl;
        for (int i = 0; i < block_Count; i++) {
            for (int j = 0; j < 16; j++) {
                printf("%02x    ", block[i][j]);
            }
            cout << endl;
        }cout << endl;
        */

        lea a;
        a.leaEnc(block[0], key); //거친 결과 block[0]이 암호문됨
       
        //print_this_Block_Result(block[0]);
        //printf("[*] %d\n", block_Count);
        // if (block_Count == 2)return;
        for (int i = 1; i < block_Count; i++) {
            for (int j = 0; j < 16; j++) {
                block[i][j] ^= block[i - 1][j];
            }
            a.leaEnc(block[i], key);
           // cout << "CBC " << i << "번째 암호문" << endl;
           // print_this_Block_Result(block[i]);
        }
       
        
        cout << "Whole Cyper Text with 0x80padding" << endl;
        for (int i = 0; i < block_Count; i++) {
            for (int j = 0; j < 16; j++) {
                printf("%02x    ", block[i][j]);
            }cout << endl;
        }/*
        cout << "암호문 복사용" << endl;
        for (int i = 0; i < block_Count; i++) {
            for (int j = 0; j < 16; j++) {
                printf("%02x", block[i][j]);
            }
        }cout << endl;*/
        /*
        if ((ctbuf = fgets(buf[3], 50, fin)) != NULL) cout << ctbuf << endl;
        else printf("ct를 제대로 받아오지 못하고 있음\n");
        memcpy(ctbuf2, ctbuf + OTHER_OFFSET, STRSIZE);

        for (int i = 0; i < 16; i++) {
            if(block[i/16][i%16]==pt[i])printf("\n받아온 파일과 암호화 결과는 같습니다\n\n");
        }

        Hex2Array(ctbuf2, STRSIZE, ct_check);
        */
        /*
#define NULLSTRSIZE 2
        char* nullbuf, nbuf[1][100];
        char nullbuf2[NULLSTRSIZE ] = { 0, };
        if ((nullbuf = fgets(buf[0], 50, fin)) != NULL) cout << "************nullbuf : " << nullbuf << endl;
        else printf("NULL를 제대로 받아오지 못하고 있음\n");
        memcpy(nullbuf2, nullbuf , NULLSTRSIZE);
        cout << "************nullbuf2 : " << nullbuf2 << endl;
        
        char line[500];
        fgets(line, sizeof(line), fin);
       */
       
        int k = 0;
        while (1) {
            if (ct_check[k] == block[k / 16][k % 16]) {
                k++;
                //printf("test failed\n");
                if (k == 15) {
                    printf("%d번째****************** test successed*********************\n", count);
                    break;
                }
            }
            else {
                printf("%d, test failed\n", count);
                break;
            }
        }
        k = 0;
        count++;
           
        for (int i = 0; i < block_Count; i++) {
            for (int j = 0; j < 16; j++) {
                fout << block[i][j];
            }
        }

       
        cout << endl; cout << endl; cout << endl;
    }
    fout.close();
}
void cbc::CBC_ENC_mct(const char* input_file, const char* output_file)
{
    int count = 1;
    byte key[16] = { 0x00 };
    byte initalVec[16] = { 0x00 };
    byte pt[16] = { 0x00, };
    byte ct_check[16] = { 0x00 };
    FILE* fin = NULL;
    ofstream fout(output_file, ios::binary);
    fin = fopen(input_file, "r");
    if (fin == NULL) {
        fprintf(stderr, "fopen failed\n");
        return;
    }
    /*
#define STRSIZE 32
#define KEY_OFFSET 6
#define OTHER_OFFSET 5
*/

//키 inVec pt ct순서
    while (!feof(fin)) {
        //key
         //fscanf_s(fin, "%s%s%s", line[0],line[1],line[2]);
         //if (line[2][0] == 0)printf("key를 제대로 받아오지 못하고 있음\n");
         //Hex2Array(line[2], sizeof(line[2]), key);
         ////iv
         //fscanf_s(fin, "%s%s%s", line[0], line[1], line[2]);
         //if (line[2] == "NULL")printf("iv를 제대로 받아오지 못하고 있음\n");
         //Hex2Array(line[2], sizeof(line[2]), initalVec);
         ////pt  
         //fscanf_s(fin, "%s%s%s", line[0], line[1], line[2]);
         //if (line[2] == "NULL")printf("pt를 제대로 받아오지 못하고 있음\n");
         //Hex2Array(line[2], sizeof(line[2]), pt);
         /*
         char* keybuf, * ivbuf, * ptbuf, *ctbuf, buf[4][100];
         char keybuf2[STRSIZE+1] = { 0, }, ivbuf2[STRSIZE+1] = { 0, }, ptbuf2[STRSIZE+1] = { 0, }, ctbuf2[STRSIZE + 1] = { 0, };
         if ((keybuf = fgets(buf[0], 50, fin)) != NULL) cout << keybuf << endl;
         else printf("key를 제대로 받아오지 못하고 있음\n");
         memcpy(keybuf2, keybuf + KEY_OFFSET, STRSIZE);
         cout << keybuf2 << endl;

         if ((ivbuf = fgets(buf[1], 50, fin)) != NULL) cout << ivbuf << endl;
         else printf("iv를 제대로 받아오지 못하고 있음\n");
         memcpy(ivbuf2, ivbuf + OTHER_OFFSET, STRSIZE);

         if ((ptbuf = fgets(buf[2], 50, fin)) != NULL) cout << ptbuf << endl;
         else printf("pt를 제대로 받아오지 못하고 있음\n");
         memcpy(ptbuf2, ptbuf + OTHER_OFFSET, STRSIZE);

         //
         cout << strlen((const char *)keybuf) << endl;
         cout << keybuf2 << endl;
         cout << ivbuf2 << endl;
         cout << ptbuf2 << endl;

         cout << endl;

         Hex2Array(keybuf2, STRSIZE, key);
         Hex2Array(ivbuf2, STRSIZE, initalVec);
         Hex2Array(ptbuf2, STRSIZE, pt);
         */
         // getFileMem_mct(fin, key, initalVec, pt, ct_check,count);
        byte read_buf[100] = { 0 };
        byte read_tmp[100] = { 0 };

        //fscanf(fin, "COUNT = %d", count,read_buf);

        fscanf(fin, "COUNT = ", read_buf);
        fscanf(fin, "%d", &read_tmp[0]);
        fscanf(fin, "\n", read_buf);


        fscanf(fin, "KEY = ", read_buf);
        for (int cnt_j = 0; cnt_j < 16; cnt_j++)
        {
            fscanf(fin, "%02X", &read_tmp[0]);
            key[cnt_j] = read_tmp[0];
            //printf("\nkey : %02X ", key[cnt_j]);
        }
        fscanf(fin, "\n", read_buf);

        fscanf(fin, "IV = ", read_buf);
        for (int cnt_j = 0; cnt_j < 16; cnt_j++)
        {
            fscanf(fin, "%02X", &read_tmp[0]);
            initalVec[cnt_j] = read_tmp[0];
            //printf("\niv:  %02X ", initalVec[cnt_j]);
        }
        fscanf(fin, "\n", read_buf);

        fscanf(fin, "PT = ", read_buf);
        for (int cnt_j = 0; cnt_j < 16; cnt_j++)
        {
            fscanf(fin, "%02X", &read_tmp[0]);
            pt[cnt_j] = read_tmp[0];
            //printf("\npt : %02X ", pt[cnt_j]);

        }
        fscanf(fin, "\n", read_buf);

        fscanf(fin, "CT = ", read_buf);
        cout << "cypher text answer" << endl;
        for (int cnt_j = 0; cnt_j < 16; cnt_j++)
        {
            fscanf(fin, "%02X", &read_tmp[0]);
            ct_check[cnt_j] = read_tmp[0];

            printf("%02X   ", ct_check[cnt_j]);
            if (cnt_j % 16 == 15)cout << endl;

        }cout << endl;
        fscanf(fin, "\n\n", read_buf);


        int block_Count = (sizeof(pt)) / 16 + 1;//pt의 길이를 받음
        byte** block = new byte * [block_Count];
        for (int i = 0; i < block_Count; i++) {
            block[i] = new byte[16];
        }

        //  cout << endl << "평문아~~ 제대로 들어갔니?" << endl;
        for (int i = 0; i < sizeof(pt); i++) {
            block[i / 16][i % 16] = pt[i];
            

        }
        //패딩
        int remainder = sizeof(pt) - (block_Count - 1) * 16;
        // printf("sizeof(pt) : %d", sizeof(pt));
         //printf("remainder : %d",remainder );

        if (remainder == 0) {
            block[block_Count - 1][0] = 0x80;
            for (int i = 1; i < 16; i++) {
                block[block_Count - 1][i] = 0x00;
            }
        }
        else {
            block[block_Count - 1][remainder] = 0x80;
            for (int i = remainder + 1; i < 16; i++) {
                block[block_Count - 1][i] = 0x00;
            }
        }


        //처음엔 벡터와의 연산임
        
        /*
        cout << "첫 블록 initalVector와의 연산 결과" << endl;
        for (int i = 0; i < block_Count; i++) {
            for (int j = 0; j < 16; j++) {
                printf("%02x    ", block[i][j]);
            }
            cout << endl;
        }cout << endl;
        */
        int ccount = 1;
        //byte copy_block[1000][16]={0x00,};
        
        byte** copy_block = new byte * [1000];
        for (int i = 0; i < 1000; i++) {
            copy_block[i] = new byte[16];
        }
        lea a;
        for (int j = 0; j < 1000; j++) {
            if (j == 0) {
                for (int i = 0; i < 16; i++) {
                    block[0][i] ^= initalVec[i];
                    // printf("***[*] %02x\n", block[0][i] ^ initalVec[i]);
                }
            }
            else if (j == 1) {
                for (int i = 0; i < 16; i++) {
                    block[0][i] ^= initalVec[i];
                }
            }
            else {
                for (int i = 0; i < 16; i++) {
                     block[0][i] ^= copy_block[j-2][i];
                }
            }
            a.leaEnc(block[0], key); //거친 결과 block[0]이 암호문됨
            for (int i = 0; i < 16; i++) {
                //printf("%02X", copy_block[j][i]);
               copy_block[j][i] = block[0][i];
            }
            /*
            //printf("[*] %d\n", block_Count);
            // if (block_Count == 2)return;
            for (int i = 1; i < block_Count; i++) {
                for (int j = 0; j < 16; j++) {
                    block[i][j] ^= block[i - 1][j];
                }
                a.leaEnc(block[i], key);

                
            }
            */
            ccount++;
        }
            cout << "Whole Cyper Text with 0x80padding" << endl;
            for (int i = 0; i < block_Count; i++) {
                for (int j = 0; j < 16; j++) {
                    printf("%02x    ", block[i][j]);
                }cout << endl;
            }/*
            cout << "암호문 복사용" << endl;
            for (int i = 0; i < block_Count; i++) {
                for (int j = 0; j < 16; j++) {
                    printf("%02x", block[i][j]);
                }
            }cout << endl;*/
            /*
            if ((ctbuf = fgets(buf[3], 50, fin)) != NULL) cout << ctbuf << endl;
            else printf("ct를 제대로 받아오지 못하고 있음\n");
            memcpy(ctbuf2, ctbuf + OTHER_OFFSET, STRSIZE);

            for (int i = 0; i < 16; i++) {
                if(block[i/16][i%16]==pt[i])printf("\n받아온 파일과 암호화 결과는 같습니다\n\n");
            }

            Hex2Array(ctbuf2, STRSIZE, ct_check);
            */
            /*
    #define NULLSTRSIZE 2
            char* nullbuf, nbuf[1][100];
            char nullbuf2[NULLSTRSIZE ] = { 0, };
            if ((nullbuf = fgets(buf[0], 50, fin)) != NULL) cout << "************nullbuf : " << nullbuf << endl;
            else printf("NULL를 제대로 받아오지 못하고 있음\n");
            memcpy(nullbuf2, nullbuf , NULLSTRSIZE);
            cout << "************nullbuf2 : " << nullbuf2 << endl;

            char line[500];
            fgets(line, sizeof(line), fin);
           */

            int k = 0;
            while (1) {
                if (ct_check[k] == block[k / 16][k % 16]) {
                    k++;
                    //printf("test failed\n");
                    if (k == 15) {
                        printf("%d번째****************** test successed*********************\n", count);
                        break;
                    }
                }
                else {
                    printf("%d, test failed\n", count);
                    break;
                }
            }
            k = 0;
            count++;

            for (int i = 0; i < block_Count; i++) {
                for (int j = 0; j < 16; j++) {
                    fout << block[i][j];
                }
            }


            cout << endl; cout << endl; cout << endl;
        }
        fout.close();
    }

void cbc::CBC_ENC_mmt(const char* input_file, const char* output_file)
{
    int count = 1;
    byte key[16] = { 0x00 };
    byte initalVec[16] = { 0x00 };
   // byte pt[320] = { 0x00 };
   // byte ct_check[320] = { 0x00 };

   
    FILE* fin = NULL;
    ofstream fout(output_file, ios::binary);
    fin = fopen(input_file, "r");
    if (fin == NULL) {
        fprintf(stderr, "fopen failed\n");
        return;
    }
    /*
#define STRSIZE 32
#define KEY_OFFSET 6
#define OTHER_OFFSET 5
*/
    int arrNum = 0;
    //키 inVec pt ct순서
    while (!feof(fin)) {
        arrNum += 16;
        byte* pt = (byte*)malloc(sizeof(byte) * arrNum);
        byte* ct_check = (byte*)malloc(sizeof(byte) * arrNum);
       // cout << "**************************************************" << sizeof(pt)<<"size"<< sizeof(byte) * arrNum << "*******arrNum" << arrNum << endl;
       
            byte read_buf[100] = { 0 };
            byte read_tmp[100] = { 0 };

            fscanf(fin, "KEY = ", read_buf);
            for (int cnt_j = 0; cnt_j < 16; cnt_j++)
            {
                fscanf(fin, "%02X", &read_tmp[0]);
                key[cnt_j] = read_tmp[0];
            }
            fscanf(fin, "\n", read_buf);

            fscanf(fin, "IV = ", read_buf);
            for (int cnt_j = 0; cnt_j < 16; cnt_j++)
            {
                fscanf(fin, "%02X", &read_tmp[0]);
                initalVec[cnt_j] = read_tmp[0];
            }
            fscanf(fin, "\n", read_buf);

            fscanf(fin, "PT = ", read_buf);
            for (int cnt_j = 0; cnt_j < arrNum; cnt_j++)
            {
                fscanf(fin, "%02X", &read_tmp[0]);
                pt[cnt_j] = read_tmp[0];
               // printf("\n**%02x, ", pt[cnt_j]);
            }
            fscanf(fin, "\n", read_buf);

            fscanf(fin, "CT = ", read_buf);
            cout << "cypher text answer" << endl;
            for (int cnt_j = 0; cnt_j < arrNum; cnt_j++)
            {
                fscanf(fin, "%02X", &read_tmp[0]);
                ct_check[cnt_j] = read_tmp[0];

               printf("%02X    ", ct_check[cnt_j]);
               if (cnt_j % 16 == 15)cout << endl;

            }cout << endl;
            fscanf(fin, "\n\n", read_buf);
           


        int block_Count = (arrNum) / 16 + 1;//pt의 길이를 받음
        byte** block = new byte * [block_Count];
        for (int i = 0; i < block_Count; i++) {
            block[i] = new byte[16];
        }

        for (int i = 0; i < arrNum; i++) {
           // printf("*pt[%d]: %02x\n", i, pt[i]);
            block[i / 16][i % 16] = pt[i];
            //printf("*pt[%d]: %02x\n", i, pt[i]);
           // printf("**block[%d][%d]: %02x\n", i/16,i%16, block[i / 16][i % 16]);

        }
        //패딩
        int remainder = arrNum - (block_Count - 1) * 16;
        // printf("sizeof(pt) : %d", sizeof(pt));
         //printf("remainder : %d",remainder );

        if (remainder == 0) {
            block[block_Count - 1][0] = 0x80;
            for (int i = 1; i < 16; i++) {
                block[block_Count - 1][i] = 0x00;
            }
        }
        else {
            block[block_Count - 1][remainder] = 0x80;
            for (int i = remainder + 1; i < 16; i++) {
                block[block_Count - 1][i] = 0x00;
            }
        }
        /*
        cout << "whole PlainText by block" << endl;
        for (int i = 0; i < block_Count; i++) {
            for (int j = 0; j < 16; j++) {
                printf("%02x    ", block[i][j]);
            }
            cout << endl;
        }cout << endl;
        */

        //처음엔 벡터와의 연산임
        for (int i = 0; i < 16; i++) {
            block[0][i] ^= initalVec[i];
            //printf("[*] %02x\n", block[0][i] ^ initalVec[i]);
        }
        /*
        cout << "첫 블록 initalVector와의 연산 결과" << endl;
        for (int i = 0; i < block_Count; i++) {
            for (int j = 0; j < 16; j++) {
                printf("%02x    ", block[i][j]);
            }
            cout << endl;
        }cout << endl;
        */

        lea a;
        a.leaEnc(block[0], key); //거친 결과 block[0]이 암호문됨

        //print_this_Block_Result(block[0]);
        //printf("[*] %d\n", block_Count);
        // if (block_Count == 2)return;
        for (int i = 1; i < block_Count; i++) {
            for (int j = 0; j < 16; j++) {
                block[i][j] ^= block[i - 1][j];
            }
            a.leaEnc(block[i], key);
            // cout << "CBC " << i << "번째 암호문" << endl;
            // print_this_Block_Result(block[i]);
        }


        cout << "Whole Cyper Text with 0x80padding" << endl;
        for (int i = 0; i < block_Count; i++) {
            for (int j = 0; j < 16; j++) {
                printf("%02X    ", block[i][j]);
            }cout << endl;
        }/*
        cout << "암호문 복사용" << endl;
        for (int i = 0; i < block_Count; i++) {
            for (int j = 0; j < 16; j++) {
                printf("%02x", block[i][j]);
            }
        }cout << endl;*/
        /*
        if ((ctbuf = fgets(buf[3], 50, fin)) != NULL) cout << ctbuf << endl;
        else printf("ct를 제대로 받아오지 못하고 있음\n");
        memcpy(ctbuf2, ctbuf + OTHER_OFFSET, STRSIZE);

        for (int i = 0; i < 16; i++) {
            if(block[i/16][i%16]==pt[i])printf("\n받아온 파일과 암호화 결과는 같습니다\n\n");
        }

        Hex2Array(ctbuf2, STRSIZE, ct_check);
        */
        /*
#define NULLSTRSIZE 2
        char* nullbuf, nbuf[1][100];
        char nullbuf2[NULLSTRSIZE ] = { 0, };
        if ((nullbuf = fgets(buf[0], 50, fin)) != NULL) cout << "************nullbuf : " << nullbuf << endl;
        else printf("NULL를 제대로 받아오지 못하고 있음\n");
        memcpy(nullbuf2, nullbuf , NULLSTRSIZE);
        cout << "************nullbuf2 : " << nullbuf2 << endl;

        char line[500];
        fgets(line, sizeof(line), fin);
       */

        int k = 0;
        while (1) {
            if (ct_check[k] == block[k / 16][k % 16]) {
                k++;
                //printf("test failed\n");
                if (k == 15) {
                    printf("%d번째****************** test successed*********************\n", count);
                    break;
                }
            }
            else {
                printf("%d, test failed\n", count);
                break;
            }
        }
        k = 0;
        count++;

        for (int i = 0; i < block_Count; i++) {
            for (int j = 0; j < 16; j++) {
                fout << block[i][j];
            }
        }

        
        cout << endl; cout << endl; cout << endl;
        free(pt);
        free(ct_check);
    }
    fout.close();
}

void cbc::CBC_DEC_kat(const char* input_file, const char* output_file)
{

    int count = 1;
    byte key[16] = { 0x00 };
    byte initalVec[16] = { 0x00 };
    byte pt[16] = { 0x00, };
    byte ct_check[16] = { 0x00 };
    FILE* fin = NULL;
    ofstream fout(output_file, ios::binary);
    fin = fopen(input_file, "r");
    if (fin == NULL) {
        fprintf(stderr, "fopen failed\n");
        return;
    }
    //키 inVec pt ct순서
    while (!feof(fin)) {         
        getFileMem_dec_kat(fin, key, initalVec, pt, ct_check);
        
        int block_Count = (sizeof(ct_check)) / 16;//pt의 길이를 받음
        byte** block = new byte * [block_Count];
        for (int i = 0; i < block_Count; i++) {
            block[i] = new byte[16];
        }

        for (int i = 0; i < sizeof(ct_check); i++) {
            block[i / 16][i % 16] = ct_check[i];
            // printf("*pt[%d]: %02x\n", i, pt[i]);
           // printf("**block[%d][%d]: %02x\n", i/16,i%16, block[i / 16][i % 16]);

        }


        byte** CTBuffer = new byte * [block_Count];
        for (int i = 0; i < block_Count; i++) {
            CTBuffer[i] = new byte[16];
        }
        for (int i = 0; i < block_Count; i++) {
            for (int j = 0; j < 16; j++) {
                CTBuffer[i][j] = block[i][j];
            }
        }

        //처음엔 벡터와의 연산임
        lea a;
        a.leaDec(block[0], key); //거친 결과 block[0]이 암호문됨
        for (int i = 0; i < 16; i++) {
            block[0][i] ^= initalVec[i];
            //printf("[*] %02x\n", block[0][i] ^ initalVec[i]);
        }

        for (int i = 1; i < block_Count; i++) {
            a.leaDec(block[i], key);
            for (int j = 0; j < 16; j++) {
                // printf("block[% d][% d] = % 02x    ", i , j, block[i][j]);
                block[i][j] ^= CTBuffer[i - 1][j];

                //printf("        CTBuffer[%d][%d] = %02x    ",i-1,j,CTBuffer[i - 1][j]);
                //printf("block[% d][% d] = % 02x    ", i, j, block[i][j]);
                //cout << endl;

            }

        }
        
        int k = 0;
        while (1) {
            if (pt[k] == block[k / 16][k % 16]) {
                k++;
                //printf("test failed\n");
                if (k == 15) {
                    printf("%d번째****************** test successed*********************\n", count);
                    break;
                }
            }
            else {
                printf("%d, test failed\n", count);
                break;
            }
        }
        k = 0;
        count++;
        cout << "whole decrypted Text by block" << endl;
        for (int i = 0; i < block_Count; i++) {
            for (int j = 0; j < 16; j++) {
                printf("%02x    ", block[i][j]);
            }
            cout << endl;
        }cout << endl;
        for (int i = 0; i < block_Count; i++) {
            for (int j = 0; j < 16; j++) {
                fout << block[i][j];
            }
        }
       
   int index = 15;
   for (int i = 15; i >= 0; i--) {
       if (block[block_Count - 1][i] == 0x80) {
           break;
       }
    index--;        
    }
    

        cout << endl; cout << endl; cout << endl;
    }
    fout.close();
   
}
void cbc::CBC_DEC_mct(const char* input_file, const char* output_file)
{

    int count = 1;
    byte key[16] = { 0x00 };
    byte initalVec[16] = { 0x00 };
    byte pt[16] = { 0x00, };
    byte ct_check[16] = { 0x00 };
    FILE* fin = NULL;
    ofstream fout(output_file, ios::binary);
    fin = fopen(input_file, "r");
    if (fin == NULL) {
        fprintf(stderr, "fopen failed\n");
        return;
    }
    //키 inVec pt ct순서
    while (!feof(fin)) {
        getFileMem_dec_mct(fin, key, initalVec, pt, ct_check,count);

        int block_Count = (sizeof(ct_check)) / 16;//pt의 길이를 받음
        byte** block = new byte * [block_Count];
        for (int i = 0; i < block_Count; i++) {
            block[i] = new byte[16];
        }

        for (int i = 0; i < sizeof(ct_check); i++) {
            block[i / 16][i % 16] = ct_check[i];
            // printf("*pt[%d]: %02x\n", i, pt[i]);
           // printf("**block[%d][%d]: %02x\n", i/16,i%16, block[i / 16][i % 16]);

        }




        byte** CTBuffer = new byte * [block_Count];
        for (int i = 0; i < block_Count; i++) {
            CTBuffer[i] = new byte[16];
        }
        for (int i = 0; i < block_Count; i++) {
            for (int j = 0; j < 16; j++) {
                CTBuffer[i][j] = block[i][j];
            }
        }

        //처음엔 벡터와의 연산임
        lea a;
        a.leaDec(block[0], key); //거친 결과 block[0]이 암호문됨
        for (int i = 0; i < 16; i++) {
            block[0][i] ^= initalVec[i];
            //printf("[*] %02x\n", block[0][i] ^ initalVec[i]);
        }

        for (int i = 1; i < block_Count; i++) {
            a.leaDec(block[i], key);
            for (int j = 0; j < 16; j++) {
                // printf("block[% d][% d] = % 02x    ", i , j, block[i][j]);
                block[i][j] ^= CTBuffer[i - 1][j];

                //printf("        CTBuffer[%d][%d] = %02x    ",i-1,j,CTBuffer[i - 1][j]);
                //printf("block[% d][% d] = % 02x    ", i, j, block[i][j]);
                //cout << endl;

            }

        }

        int k = 0;
        while (1) {
            if (pt[k] == block[k / 16][k % 16]) {
                k++;
                //printf("test failed\n");
                if (k == 15) {
                    printf("%d번째****************** test successed*********************\n", count);
                    break;
                }
            }
            else {
                printf("%d, test failed\n", count);
                break;
            }
        }
        k = 0;
        count++;
        cout << "whole decrypted text by block" << endl;
        for (int i = 0; i < block_Count; i++) {
            for (int j = 0; j < 16; j++) {
                printf("%02x    ", block[i][j]);
            }
            cout << endl;
        }cout << endl;

        for (int i = 0; i < block_Count; i++) {
            for (int j = 0; j < 16; j++) {
                fout << block[i][j];
            }
        }
        /* 패딩이 있을 경우의 하는 패딩 제거 연산 하지만 파일에서 받으므로 없음
        *
   int index = 15;
   for (int i = 15; i >= 0; i--) {
       if (block[block_Count - 1][i] == 0x80) {
           break;
       }
    index--;
    }*/


        cout << endl; cout << endl; cout << endl;
    }
    fout.close();

}
void cbc::CBC_DEC_mmt(const char* input_file, const char* output_file)
{
    int count = 1;
    byte key[16] = { 0x00 };
    byte initalVec[16] = { 0x00 };
    // byte pt[320] = { 0x00 };
    // byte ct_check[320] = { 0x00 };


    FILE* fin = NULL;
    ofstream fout(output_file, ios::binary);
    fin = fopen(input_file, "r");
    if (fin == NULL) {
        fprintf(stderr, "fopen failed\n");
        return;
    }
    /*
#define STRSIZE 32
#define KEY_OFFSET 6
#define OTHER_OFFSET 5
*/
    int arrNum = 0;
    //키 inVec pt ct순서
    while (!feof(fin)) {
        arrNum += 16;
        byte* pt = (byte*)malloc(sizeof(byte) * arrNum);
        byte* ct_check = (byte*)malloc(sizeof(byte) * arrNum);
        // cout << "**************************************************" << sizeof(pt)<<"size"<< sizeof(byte) * arrNum << "*******arrNum" << arrNum << endl;

        byte read_buf[100] = { 0 };
        byte read_tmp[100] = { 0 };

        fscanf(fin, "KEY = ", read_buf);
        for (int cnt_j = 0; cnt_j < 16; cnt_j++)
        {
            fscanf(fin, "%02X", &read_tmp[0]);
            key[cnt_j] = read_tmp[0];
        }
        fscanf(fin, "\n", read_buf);

        fscanf(fin, "IV = ", read_buf);
        for (int cnt_j = 0; cnt_j < 16; cnt_j++)
        {
            fscanf(fin, "%02X", &read_tmp[0]);
            initalVec[cnt_j] = read_tmp[0];
        }
        fscanf(fin, "\n", read_buf);

        fscanf(fin, "PT = ", read_buf);
        cout << "decrpted text answer" << endl;

        for (int cnt_j = 0; cnt_j < arrNum; cnt_j++)
        {
            fscanf(fin, "%02X", &read_tmp[0]);
            pt[cnt_j] = read_tmp[0];
            printf("%02X    ", pt[cnt_j]);
            if (cnt_j % 16 == 15)cout << endl;
            // printf("\n**%02x, ", pt[cnt_j]);
        }
        fscanf(fin, "\n", read_buf);

        fscanf(fin, "CT = ", read_buf);
        for (int cnt_j = 0; cnt_j < arrNum; cnt_j++)
        {
            fscanf(fin, "%02X", &read_tmp[0]);
            ct_check[cnt_j] = read_tmp[0];


        }cout << endl;
        fscanf(fin, "\n\n", read_buf);



        int block_Count = (arrNum) / 16;//pt의 길이를 받음
        byte** block = new byte * [block_Count];
        for (int i = 0; i < block_Count; i++) {
            block[i] = new byte[16];
        }

        for (int i = 0; i < arrNum; i++) {
            // printf("*pt[%d]: %02x\n", i, pt[i]);
            block[i / 16][i % 16] = ct_check[i];
            //printf("*pt[%d]: %02x\n", i, pt[i]);
           // printf("**block[%d][%d]: %02x\n", i/16,i%16, block[i / 16][i % 16]);

        }
        


        byte** CTBuffer = new byte * [block_Count];
        for (int i = 0; i < block_Count; i++) {
            CTBuffer[i] = new byte[16];
        }
        for (int i = 0; i < block_Count; i++) {
            for (int j = 0; j < 16; j++) {
                CTBuffer[i][j] = block[i][j];
            }
        }

        //처음엔 벡터와의 연산임
        lea a;
        a.leaDec(block[0], key); //거친 결과 block[0]이 암호문됨
        for (int i = 0; i < 16; i++) {
            block[0][i] ^= initalVec[i];
            //printf("[*] %02x\n", block[0][i] ^ initalVec[i]);
        }

        for (int i = 1; i < block_Count; i++) {
            a.leaDec(block[i], key);
            for (int j = 0; j < 16; j++) {
                // printf("block[% d][% d] = % 02x    ", i , j, block[i][j]);
                block[i][j] ^= CTBuffer[i - 1][j];

                //printf("        CTBuffer[%d][%d] = %02x    ",i-1,j,CTBuffer[i - 1][j]);
                //printf("block[% d][% d] = % 02x    ", i, j, block[i][j]);
                //cout << endl;

            }

        }
        cout << "복호화문" << endl;
        for (int i = 0; i < block_Count; i++) {
            for (int j = 0; j < 16; j++) {
                printf("%02x    ", block[i][j]);
            }
            cout << endl;
        }cout << endl;
        int k = 0;
        while (1) {
            if (pt[k] == block[k / 16][k % 16]) {
                k++;
                //printf("test failed\n");
                if (k == arrNum-1) {
                    printf("%d번째****************** test successed*********************\n", count);
                    break;
                }
            }
            else {
                printf("%d, test failed\n", count);
                break;
            }
        }
        k = 0;
        count++;

        for (int i = 0; i < block_Count; i++) {
            for (int j = 0; j < 16; j++) {
                fout << block[i][j];
            }
        }
        /* 패딩이 있을 경우의 하는 패딩 제거 연산 하지만 파일에서 받으므로 없음
        *
   int index = 15;
   for (int i = 15; i >= 0; i--) {
       if (block[block_Count - 1][i] == 0x80) {
           break;
       }
    index--;
    }*/


        cout << endl; cout << endl; cout << endl;
    }
    fout.close();
    cout << endl;
    cout << "MMT복호화 성공" << endl;
}