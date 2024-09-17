import serial

arduino_port = "COM6"
baud_rate = 9600

serial_conn = serial.Serial(arduino_port, baud_rate, timeout=1)

def GetData():
    try:
        if serial_conn.in_waiting > 0:
            message = serial_conn.readline().decode('utf-8').rstrip()
            match message:
                case "I":
                    return 1
                case "D":
                    return 2
                case "K":
                    return 3
                case "P1":
                    return "P1"
                case "P2":
                    return "P2"
                case "P3":
                    return "P3"
                case "P4":
                    return "P4"
                case "P5":
                    return "P5"
    except Exception as e:
        return None
