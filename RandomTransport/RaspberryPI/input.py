from serial import Serial
import time


def loop(arduino: Serial) -> None:
    print("----    COMMANDS    ----")
    print("  [1] Start/Restart")
    print("  [2] Pause")
    print("  [3] Resume")
    cmd = input("IN << Enter command: ")
    arduino.write(cmd.encode())
    arduino.flushInput()
    while arduino.inWaiting() == 0:
        pass
    if arduino.inWaiting() > 0: 
        answer = arduino.readline().decode('utf-8').rstrip()
        print(f"OUT >> {answer}")
        arduino.flushInput()
    
    if (cmd == "1"):
        goal_num = 0
        while goal_num == 0:
            input_num = input("IN << Amount of destinations [1, 9]: ")
            if (not input_num.isnumeric()): continue
            goal_num = str(int(input_num))
        arduino.write(goal_num.encode())
        arduino.flushInput()
        while arduino.inWaiting() == 0:
            pass
        if arduino.inWaiting() > 0: 
            answer = arduino.readline().decode('utf-8').rstrip()
            print(f"OUT >> {answer}")
            arduino.flushInput()


if __name__ == '__main__':
    with Serial("/dev/ttyACM0", 9600, timeout=1) as arduino:
        time.sleep(0.1)
        if arduino.isOpen():
            print(f"Connected to Arduino :: Port = [{arduino.port}]")
            while True:
                loop(arduino)
