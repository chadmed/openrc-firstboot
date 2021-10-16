#!/usr/bin/env python3
"""
SPDX-License-Identifier: MIT

openrc-firstboot: A very, very, *very* simple firstboot in Python.

All text strings has been formatted to look nice on an
80-column terminal for readability on the default Linux tty.

(C) 2021 James Calligeros <jcalligeros99@gmail.com>
"""

from crypt import crypt
from getpass import getpass
from os import system
from subprocess import call
from random import choice
from time import sleep


def set_password(user):
    """
    Change password for 'user'
    """

    ret = system(f"passwd {user}")
    if ret != 0:
        print(f"Error setting password for {user}.")
    else:
        print(f"Password for {user} changed successfully.\n")


def set_hostname():
    """
    Opens/creates /etc/hostname and dumps the chosen hostname in.
    """
    hostname = input("Please specify a hostname: ")

    try:
        with open("/etc/hostname", mode="w") as hn:
            hn.write(hostname)
    except:
        print("Unable to set the hostname for the machine.")
    else:
        print(f"This machine will now be known as {hostname} on the network.\n")


def create_local_user(new_user):
    """
    Creates a local user and adds them to the audio and video groups.
    """
    new_user = input("Please enter a username: ")
    ret = system(f"useradd -m -G audio,video,wheel -s /bin/bash {new_user}")
    if ret != 0:
        print(f"Unable to create user {new_user}.")
    else:
        print(f"New user {new_user} created successfully and",
               "added to the 'audio', 'video' and 'wheel' groups.\n",
               "Your default shell is bash.")
        print(f"You will now set a password for {new_user}")
        set_password(new_user)

def cleanup():
    """
    Removes the init script from the default runlevel and reboots the machine.
    """
    call("rc-update delete firstboot default")
    print("Rebooting in 5 seconds...")
    sleep(5)
    call("reboot")


def main():
    print("#######################")
    print("FIRST BOOT SYSTEM SETUP")
    print("#######################")

    print("This appears to be your first time booting this system. This",
          "script will guide\nyou through:")
    print("1. Changing the default root password.")
    print("2. Setting a hostname for the machine.")
    print("3. Creating a local user.\n\n")
    sleep(5)

    print("##################################")
    print("Changing the default root password")
    print("##################################\n\n")
    print("ARM rootfs images often have insecure default root",
          "passwords, much like a\nrouter with the default 'admin' username",
          "and password. This must be changed to ensure\nthe security of the",
          "system. Make sure the password you enter is extremely\nstrong.")

    input("Press Enter to continue...")
    print("\n")
    set_password("root")
    print("\n")
    sleep(1.5)


    print("##################################")
    print("Setting a hostname for the machine")
    print("##################################\n\n")
    print("The hostname identifies your machine on the network. Must contain",
          "alphanumeric\ncharacters only. Do not append '.local'.\n")

    input("Press Enter to continue...")
    print("\n")
    set_hostname()
    print("\n")
    sleep(1.5)

    print("#####################")
    print("Creating a local user")
    print("#####################\n\n")
    print("You will now create a user account for yourself.\n")

    input("Press Enter to continue")
    print("\n")
    create_local_user()
    print("\n")
    sleep(1.5)

    print("Your machine will now reboot, probably to a login shell. Consult",
        "your distro's\ndocumentation for further configuration and",
        "customisation options. This script\nwill not run again by default,",
        "but can be made to by running\n")
    print("\033[1m\trc-update add firstboot default\033[0m\n")
    print("as root and then rebooting your machine.")

    input("Press Enter to reboot... ")

    # uncomment for distribution/production
    # cleanup()


if __name__ == "__main__":
    main()
