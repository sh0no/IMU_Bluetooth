import serial
import csv


try:
    ser = serial.Serial('/dev/cu.M5stickC-ESP32SPP',9600,timeout=None)
except Exception as e:
    print(e)

while(True):
    try:
        line = ser.readline()
        if line == b'start\r\n':
            with open('IMU_data.csv', 'a') as f:
                writer = csv.writer(f)
                print("start")
        elif line != b'end\r\n':
            with open('IMU_data.csv', 'a') as f:
                writer = csv.writer(f)
                #print(line)
                tmp = str(line)
                tmp = tmp.replace("b'","")
                tmp = tmp.replace("\\n'","")
                tmp = tmp.split()
                writer.writerow(tmp)
                print(tmp)
        else:
            with open('IMU_data.csv', 'a') as f:
                writer = csv.writer(f)
                writer.writerow(["#","#","#"])
                print("end")
                
                

    except KeyboardInterrupt:
        print('keyboard interrupt')
        ser.close()
        break

    except Exception as e:
        print(e)
        ser.close()
        break
