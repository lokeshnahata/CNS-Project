#include "aes.h"
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
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
 int sockfd, newSocket, len, n;
 char buffer[200];
 struct sockaddr_in serveraddr, cliaddr;
 len = sizeof(serveraddr);
 serveraddr.sin_family=AF_INET;
 serveraddr.sin_addr.s_addr=htonl(INADDR_ANY);
 serveraddr.sin_port=htons(0);
 sockfd=socket(AF_INET,SOCK_STREAM,0);
 bind(sockfd,(struct sockaddr*)&serveraddr,len);
 getsockname(sockfd,(struct sockaddr*)&serveraddr,&len);
 printf("Your Port(USER B)=%ld\n",(long)ntohs(serveraddr.sin_port));
 listen(sockfd,5);
 newSocket=accept(sockfd,(struct sockaddr*)&cliaddr,&len);

  recv(newSocket, ciphertext, 16, 0);
  printf("\nCiphertext recieved from USER A: ");
  for(int i=0;i<AES_BLOCK_SIZE;i++){
	  printf("%2x ",ciphertext[i]);
  }
  aes_key_schedule_128(key, roundkeys);
  aes_decrypt_128(roundkeys, ciphertext, ciphertext);
  printf("\nPlaintext extracted from Ciphertext: ");
  for(int i=0;i<AES_BLOCK_SIZE;i++){
	  printf("%c",(char)ciphertext[i]);
  }
  printf("\n\n");

 exit(0);
 close(newSocket);
 return 0;
}
