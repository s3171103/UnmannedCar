#!/usr/bin/python
# -*- coding: UTF-8 -*-
# 文件名：client.py
 
import socket               # 导入 socket 模块
 
s = socket.socket()         # 创建 socket 对象
host = '192.168.1.10' # 获取本地主机名
port = 12345                # 设置端口号
print(host)
s.connect((host, port))
print (s.recv(1024))
s.close()