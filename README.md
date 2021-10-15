# openrc-firstboot
---

Simple Python implementation of similar functionality to systemd-firstboot for
OpenRC systems.

## To fully test functionality
1. Copy `openrc-firstboot` to `/sbin/`
2. Copy `firstboot` to `/etc/init.d/`
3. Make both files executable
4. Run `rc-update add firstboot default` as root
5. Reboot.
