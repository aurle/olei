import socket

#20 bytes header
#3 bytes block 0
#3 bytes block 1
#3 bytes block 2 
# ....
# 3 bytes block n
# (maximum size 1460 bytes akrao 4480 blocks)

# Packet format Header 20 bytes
# 2 bytes faf0 ID
# 2 bytes 0200 Protocol version
# 1 byte distance scale, distance = readout data * distance scale
# 1 byte error status
# 1 byte starting angle, resolution 1
# 1 byte ending angle, resolution 1
# 2 bytes number of angles between starting and ending angle
# 2 bytes rotation rate
# 4 bytes time stamp ms since power on
# 4 bytes checksum of block data w/o frame header

# 2 bytes distance readout
# 1 byte signal strength (0-255)
# Repeate the above 3 bytes up to 406 times
UDP_IP = "192.168.1.10"
UDP_PORT = 2368
# MAX_MSG_SIZE = 1282
MAX_MSG_SIZE = 4096

sock = socket.socket(socket.AF_INET, # Internet
                     socket.SOCK_DGRAM) # UDP
sock.bind((UDP_IP, UDP_PORT))

while True:
    data, addr = sock.recvfrom(MAX_MSG_SIZE) # buffer size is 1024 bytes
    print("")
    print("")
    print("received message:")
    print("from: : ", addr)
    print("")
    print(data)
    #decoded = data[0].decode()
    print("")
    print("")
    #print(decoded)

