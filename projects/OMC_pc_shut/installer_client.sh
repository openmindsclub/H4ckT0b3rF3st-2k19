#Run at startup
echo '[Desktop Entry]\n'\
	 'Type = Application\n'\
	 'Encoding = UTF-8\n'\
	 'Name = pc_shutdown\n'\
	 'Exec = python3 /bin/OMC_pc_shut.py\n'\
	 'Terminal = false\n'\
	 'X-GNOME-Autostart-enabled = true' > ~/.config/autostart/OMC_pc_shut.desktop;

mkdir -p /usr/share/OMC_pc;
cp OMC_pc_shut.py /usr/share/OMC_pc/OMC_pc_shut.py;