#!/usr/bin/env python3
"""
SPDX-License-Identifier: MIT

openrc-firstboot: A very, very, *very* simple firstboot in Python.
                  Asks the user to set a hostname and root password, then lets
                  them create a local user. Removes itself from the 'default'
                  runlevel, but does not destroy the init script.

(C) 2021 James Calligeros <jcalligeros99@gmail.com>
"""

from crypt import crypt
from getpass import getpass
from random import choice
from subprocess import call
from time import sleep


def set_password(user, newpasswd):
    """
    Change password for 'user' to 'newpasswd'
    """
    # Set some characters to use as salt for encrypting the password
    SALT_DICT = ("0123456789",
                 "ABCDEFGHIJKLMNOPQRSTUVWXYZ",
                 "abcdefghijklmnopqrstuvwxyz")

    salt = "".join(choice(ALPHABET) for i in range(8))
    mask = crypt(newpasswd, "$1$"+salt+"$")

    ret = call(("usermod", "-p", mask, user))
    if ret != 0:
        print(f"Error setting password for {user}.")
    else:
        print(f"Password for {user} changed successfully.")


def set_hostname(newname):
    """
    Opens/creates /etc/hostname and dumps the chosen hostname in.
    """

    try:
        with open("/etc/hostname", mode="w") as hn:
            hn.write(newname)
    except:
        print("Unable to set the hostname for the machine.")
    else:
        print(f"This machine will now be known as {newname} on the network.")


def create_local_user(username):
    """
    Creates a local user and adds them to the audio and video groups.
    """
    ret = call(("usermod",
                "-a -G audio,video,wheel",
                username,
                "-s /bin/bash"))
    if ret != 0:
        print(f"Unable to create user {username}.")
    else:
        print((f"New user {username} created successfully and ",
               "added to the 'audio', 'video' and 'wheel' groups. ",
               "Your default shell is bash."))

def cleanup():
    """
    Removes the init script from the default runlevel and reboots the machine.
    """
    call("rc-update delete openrc-firstboot default")
    call("reboot")


def main():
    print("#######################")
    print("FIRST BOOT SYSTEM SETUP")
    print("#######################")

    print("This appears to be your first time booting this system. This ",
          "script will guide you through: ")
    print("1. Changing the default root password.")
    print("2. Setting a hostname for the machine.")
    print("3. Creating a local user.\n\n\n\n")
    sleep(3)

    print("##################################")
    print("Changing the default root password")
    print("##################################\n\n")
    while True:
        newroot = getpass("Please input a new root password.")
        conf    = getpass("Confirm root password: ")
        if newroot != conf:
            print("Error: passwords do not match. Try again.")
            sleep(2)
            continue
        else:
            set_password("root", newroot)
            break

    print("##################################")
    print("Setting a hostname for the machine")
    print("##################################\n\n")
    print("The hostname identifies your machine on the network. Must contain ",
          "alphanumeric characters only. Do not append '.local'.\n")
    name = input("Please specify a hostname: ")
    set_hostname(name)

    print("#####################")
    print("Creating a local user")
    print("#####################\n\n")
    print("You will now create a user account for yourself.\n")
    uname = input("Please enter a username: ")
        while True:
        upass   = getpass(f"Please input a password for {name}.")
        conf    = getpass("Confirm password: ")
        if upass != conf:
            print("Error: passwords do not match. Try again.")
            sleep(2)
            continue
        else:
            set_password(name, upass)
            break

    print("Your machine will now reboot, probably to a login shell. Consult ",
          "your distro's documentation for further configuration and ",
          "customisation options. This script will not run again by default, ",
          "but can be made to by running\n")
    print("rc-update add openrc-firstboot default\n")
    print("as root and then rebooting your machine.")

    input("Press Enter to reboot... ")

    cleanup()


if __name__ == "__main__":
    main()
