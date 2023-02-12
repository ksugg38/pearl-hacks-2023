import serial
ser = serial.Serial(" ")
ser_bytes = ser.readline()
file = (open("recorded_data.csv", "a"))
line = 0
samples = 1000

while line <= samples:
    print(line)
    data = ser_bytes[0:][:-2]
    file.write(str(data))
    line += 1

file.close()
