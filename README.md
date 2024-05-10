# [dwm](https://suckless.org/) (dynamic window manager) 

<details><summary> <b>xorg and extra</b> </summary>

```
pacman -S xorg xorg-xinit xorg-server xterm
```

<!--
cd ~/Downloads
git clone --depth=1 https://aur.archlinux.org/aurman.git
cd aurman
makepkg -si --noconfirm
-->

</details>
<br/>

<details><summary> <b>debian dependencies</b> </summary>

```
sudo apt install -f suckless-tools build-essential libxrandr-dev libx11-dev libxft-dev libxcb-res0-dev libx11-xcb-dev libxinerama-dev libfreetype6-dev libfontconfig1-dev xcompmgr xwallpaper light -y
```

</details>



<details><summary> <b>arch dependencies</b> </summary>

```
sudo pacman -S --needed base-devel libx11 libxft libxinerama freetype2 fontconfig xcompmgr xwallpaper noto-fonts-emoji xterm openssh xdotool --noconfirm
```

<!--
cd ~/Downloads
git clone --depth=1 https://aur.archlinux.org/aurman.git
cd aurman
makepkg -si --noconfirm
-->

</details><br>

<details><summary> <b>my dwm config install</b> </summary>
  
```
mkdir -p ~/Downloads/Suckless-org
cd ~/Downloads/Suckless-org
git clone https://github.com/Paulobox/suckless-software
cd suckless-software

cd dwm
sudo make clean install

cd ../dmenu
sudo make clean install

cd ../st
sudo make clean install

cd ../slstatus
sudo make clean install
```
</details>
  
<details><summary> <b>original dwm install</b> </summary>

```
mkdir -p ~/Downloads/Suckless
cd ~/Downloads/Suckless
git clone --depth=1 https://git.suckless.org/dwm
git clone --depth=1 https://git.suckless.org/st
git clone --depth=1 https://git.suckless.org/dmenu
git clone --depth=1 https://git.suckless.org/slstatus

cd dwm
sudo make clean install

cd ../st
sudo make clean install

cd ../dmenu
sudo make clean install

cd ../slstatus
sudo make clean install
```

</details><br>

<details><summary> <b>oneliner for dwm.desktop entry</b> </summary>

```
echo -e "[Desktop Entry]\nName=dwm\nComment=dynamic window manager\nExec=dwm\nTryExec=/usr/local/bin/dwm\nIcon=dwm\nType=Application" | sudo tee /usr/share/xsessions/dwm.desktop > /dev/null && cat /usr/share/xsessions/dwm.desktop
```

</details></details>

</details><br>

<details><summary> <b>FONTS</b> </summary>
pacman -Qe | grep "font\|ttf"

```
fontconfig
libertinus-font
noto-fonts
noto-fonts-emoji
ttf-font-awesome
```

</details></details>

<details><summary>pywall for dwm status-bar for pywall colors(window manager)</summary>

***please edit your dwm.c***
```
XRDB_LOAD_COLOR("dwm.color0", normbordercolor);
XRDB_LOAD_COLOR("dwm.color8", selbordercolor);
XRDB_LOAD_COLOR("dwm.color0", normbgcolor);
XRDB_LOAD_COLOR("dwm.color6", normfgcolor);
XRDB_LOAD_COLOR("dwm.color0", selfgcolor);
XRDB_LOAD_COLOR("dwm.color14", selbgcolor);
```
</details>

<!--
<details><summary>sound audio</summary>

```
sudo pacman -Sy pipewire pipewire-alsa pipewire-pulse pavucontrol pamixer
```

```
pamixer --increase 5
```
</details>
-->
