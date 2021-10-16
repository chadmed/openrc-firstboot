#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
	int status;
    const char usrcmd;
    const char pwdcmd;
	usrcmd = "useradd -m -G audio,video,wheel -s /bin/bash ";
	pwdcmd = "passwd ";
    char username;
    printf("Please specify a username: ");
    scanf("%s", username);

    char* mkuser = (char *)malloc(strlen(usrcmd) + strlen(username));
    strcpy(mkuser, usrcmd);
    strcat(mkuser, username);

    char* mkpswd = (char *)malloc(strlen(pwdcmd) + strlen(username));
    strcpy(mkpswd, pwdcmd);
    strcat(mkpswd, username);


    sleep(0.2);
	printf("%s\n", mkuser);
	if (status != 0)
	{
		printf("Unable to create user %s.\n", username);
		exit(EXIT_FAILURE);
	} else {
		printf("Now, specify a password for %s\n", username);
		printf("%s\n", mkpswd);
	}

	return 0;
}
