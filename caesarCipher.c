#include <stdio.h>
#include <string.h>
#include <ctype.h>


int main(){
	int i, shift;
	char str[101];
	printf("\n\t  ____                                  _       _               \n\t / ___|__ _  ___  ___  __ _ _ __    ___(_)_ __ | |__   ___ _ __ \n\t| |   / _` |/ _ \\/ __|/ _` | '__|  / __| | '_ \\| '_ \\ / _ \\ '__|\n\t| |__| (_| |  __/\\__ \\ (_| | |    | (__| | |_) | | | |  __/ |   \n\t \\____\\__,_|\\___||___/\\__,_|_|     \\___|_| .__/|_| |_|\\___|_|   \n\t                                         |_|                    \n");
	while(1){
		printf("\n\tPlease input 5 until 100 characters to be encrypted: ");
		scanf("%[^\n]",str); getchar();
		printf("\n\tPlease input your shift key: ");
		scanf("%d",&shift); getchar();
		if(strlen(str) > 4 && strlen(str) < 101){
			for(i = 0; i < strlen(str); i++){
				if(isalpha(str[i])){
					if ((str[i] > 'z' - shift && str[i] <= 'z') || (str[i] > 'Z' - shift && str[i] <= 'Z')){
						str[i] -= 26;
					}
					str[i] += shift;
				}
			}
			printf("\n\tEncrypted string: %s\n\n\n\n\n",str);
			break;
		}
	}
	return 0;
}
