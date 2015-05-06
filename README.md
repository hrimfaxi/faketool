安装方法:

编译:
make

安装到~/bin:
make install

在/etc/profile最后添加
export PATH=~/bin:$PATH
bind -x '"\C-n":xmake'

然后重启shell。

在shell按Ctrl-n键开始复制

添加到/etc/udev/rules.d/100-usb.rules:
ACTION=="add", KERNEL=="sd*[!0-9]", RUN+="/home/hrimfaxi/sources/faketool/usb_img.sh '%E{DEVNAME}'"
SUBSYSTEM=="block", KERNEL=="sr0", ACTION=="change", RUN+="/home/hrimfaxi/sources/faketool/usb_img.sh '%E{DEVNAME}'"

会在USB/CDROM插入时复制。。。
