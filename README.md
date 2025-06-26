# keygrabber

[In Developement]

This Keygrabber aims to block inputs from user's keyboard and mouse until an OTP is entered.

Compile with:
```console
gcc -o Keygrabber Keygrabber.c -lX11
```

Add a file named keygrabber.desktop in ~/.config/autostart/ with this content for execution at startup:
```
[Desktop Entry]
Encoding=UTF-8
Version=1.0
Name=Keygrabber
Exec=/home/naasc/Documents/Keygrabber
Type=Application
Terminal=false
```