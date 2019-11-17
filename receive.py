import serial
s=serial.Serial("/dev/ttyUSB0",4800)

f=open("dump.bin","wb")
cnt=0;
try:
    print("Waiting for stream")
    while(True):
        f.write(s.read(1024))
        cnt+=1
        print("\r received {} Kb".format(cnt),end="")
        f.flush()
except KeyboardInterrupt:
    f.close()
    print("Dumped")
