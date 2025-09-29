import serial         # For communicating with the serial port (UART)
import requests       # For sending HTTP requests to the PHP server
import time           # For adding delays between readings
import re             # For extracting numeric values using regular expressions
from datetime import datetime  # For timestamping readings

# --- Configuration ---
COM_PORT = "COM4"             # Serial port connected to STM32 (change as needed)
BAUD_RATE = 9600               # Baud rate must match STM32 configuration
URL = "http://localhost/lm35_project/save.php"  # PHP endpoint to receive temperature data

# --- Open Serial Port ---
try:
    ser = serial.Serial(COM_PORT, BAUD_RATE, timeout=1)
    print(f"[INFO] Connected to {COM_PORT} at {BAUD_RATE} baud")
except Exception as e:
    # If the serial port fails to open, print error and exit
    print("[ERROR] Couldn't open COM port:", e)
    exit()

# --- Main Loop ---
while True:
    try:
        # Read a line from the serial port and decode it
        line = ser.readline().decode(errors="ignore").strip()

        if line:
            # Get current timestamp in 12-hour format with AM/PM
            now = datetime.now().strftime("%Y-%m-%d %I:%M:%S %p")

            # Print the raw data received from STM32
            print(f"\n[{now}] [UART] Raw Data: {line}")

            # Extract numeric temperature value from the line
            match = re.search(r"[-+]?\d*\.\d+|\d+", line)
            if match:
                temp = float(match.group())
                print(f"[{now}] [UART] Extracted Temperature: {temp} °C")

                # Send temperature to the PHP server using POST
                response = requests.post(URL, data={"temp": temp})
                print(f"[{now}] [SERVER] {response.text}")
            else:
                # If no numeric value is found, print an error
                print(f"[{now}] [ERROR] No numeric value found in: {line}")

        # Wait 1 second before reading the next value
        time.sleep(1)

    except KeyboardInterrupt:
        # Gracefully handle Ctrl+C interruption
        print("\n[INFO] Program stopped by user")
        break
    except Exception as e:
        # Catch any unexpected errors
        print("[ERROR] Unexpected error:", e)
        break

# --- Close Serial Port ---
ser.close()
print("[INFO] Serial port closed")