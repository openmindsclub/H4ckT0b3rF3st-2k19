mkdir -p /usr/share/OMC_pc;
cp OMC_pc_server.py /usr/share/OMC_pc/OMC_pc_server.py;
chmod +x /usr/share/OMC_pc/OMC_pc_server.py
ln -sf /usr/share/OMC_pc/OMC_pc_server.py /usr/bin/OMC_pc_server;