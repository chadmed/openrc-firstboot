/* SPDX-License-Identifier: MIT
 *
 * openrc-firstboot
 *
 * An openrc-friendly implementation of functionality similar to
 * systemd-firstboot.
 *
 * this is all awful btw and needs a LOT of reworking
 *
 * (C) 2021 James Calligeros <jcalligeros99@gmail.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


void set_root_password()
{
	int status;


	status = system("passwd root");
	if (status != 0)
	{
		printf("Unable to set password for root.\n");
		exit(EXIT_FAILURE);
	} else {
		printf("Password for root set successfully.\n");
		sleep(2);
	}
}

void set_hostname()
{
	char hostname;
	FILE *etc_hostname;

	printf("Please enter a hostname: ");
	scanf("%s", &hostname);

	etc_hostname = fopen("/etc/hostname", "w");
	fprintf(etc_hostname, "%s\n", &hostname);
	fclose(etc_hostname);
}


void create_user()
/* this is psychotic C butchery. pls fix :( */
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
	printf("%s\n", mkuser); /* debug - replace with a system() call */
	if (status != 0)
	{
		printf("Unable to create user %s.\n", username);
		exit(EXIT_FAILURE);
	} else {
		printf("Now, specify a password for %s\n", username);
		printf("%s\n", mkpswd); /* debug - replace with a system() call */
	}

	return 0;
}



void cleanup()
{
	int status;
	status = system("rc-update delete firstboot default");
	if (status != 0)
	{
		printf("Unable to remove firstboot from the runlevel.");
		exit(EXIT_FAILURE);
	} else {
		system("reboot");
	}
}


int main()
{
	printf("################\n");
	printf("openrc-firstboot\n");
	printf("################\n\n");

	printf("This appears to be your first time booting this system. ");
	printf("You will now be guided through:\n");
	printf("1. Changing the root password\n");
	printf("2. Setting a hostname for the machine\n");
	printf("3. Creating a local user\n\n");
	sleep(8);

	printf("##########################\n");
	printf("Changing the root password\n");
	printf("##########################\n\n");
	printf("You will now change the root password. ARM distro images ");
	printf("often set insecure default root passwords. It is therefore\n");
	printf("in your best interests to change this.\n\n");

	set_root_password();



	printf("####################\n");
	printf("Setting the hostname\n");
	printf("####################\n\n");

	printf("Please specify an alphanumeric hostname for the machine.\n");
	printf("Do not append '.local' or any special characters.\n\n");

	set_hostname();



	printf("#####################\n");
	printf("Creating a local user\n");
	printf("#####################\n\n");

	printf("You will now create a local user account.\n");

	create_user();

	printf("Your machine will now reboot, probably to a login shell. ");
	printf("Please consult your\n distro's documentation for futher ");
	printf("configuration and customisation options.\nThis script will ");
	printf("not run again by default, but can be made to do so by ");
	printf("running\n\nrc-update add firstboot\n\nand rebooting.\n\n");

	printf("Rebooting in 10 seconds...\n");
	sleep(10);

	cleanup();

	return 0;
}
