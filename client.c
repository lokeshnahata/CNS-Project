#include "aes.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
	uint8_t i, r;
	/* 128 bit key */
	uint8_t key[] = {
		0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
		0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 

	};
	uint8_t plaintext[AES_BLOCK_SIZE];
	uint8_t ciphertext[AES_BLOCK_SIZE];
	const uint8_t const_cipher[AES_BLOCK_SIZE] = {
		0x69, 0xc4, 0xe0, 0xd8, 0x6a, 0x7b, 0x04, 0x30,
		0xd8, 0xcd, 0xb7, 0x80, 0x70, 0xb4, 0xc5, 0x5a,
	};
	uint8_t roundkeys[AES_ROUND_KEY_SIZE];

int main()
{
 printf("\nAdvanced Encryption Standard")	;
 printf("\n\n------------------------\nName: Tapas Sahu\nRegdno: 1841012055\nBranch: CSE\nSection: E\n------------------------\n\n");
 int clientSocket,len,n;
 long port;
 struct sockaddr_in cli_addr;
 char buffer[16];
 len = sizeof(cli_addr);
 printf("Enter the port number of USER B:");
 scanf("%ld",&port);
 while((getchar())!='\n');
 cli_addr.sin_family=AF_INET;
 cli_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
 cli_addr.sin_port=htons(port);
 clientSocket = socket(AF_INET, SOCK_STREAM, 0);
 connect(clientSocket,(struct sockaddr *)&cli_addr,len);

  printf("\n\nUSER A : ");
  fgets(buffer, 16, stdin);
  for(int i=0;i<4;i++){
      plaintext[4*i+0]=(uint8_t)buffer[4*i+0];
      plaintext[4*i+1]=(uint8_t)buffer[4*i+1];
      plaintext[4*i+2]=(uint8_t)buffer[4*i+2];
      plaintext[4*i+3]=(uint8_t)buffer[4*i+3];
  }
  aes_key_schedule_128(key, roundkeys);
  aes_encrypt_128(roundkeys, plaintext, ciphertext);
  printf("Ciphertext sent to USER B: ");
  for(int i=0;i<AES_BLOCK_SIZE;i++){
	  printf("%2x ",ciphertext[i]);
  }
  send(clientSocket, ciphertext, 16, 0);
 printf("\n\n");

 close(clientSocket);
 exit(0);
 return 0;
 }
