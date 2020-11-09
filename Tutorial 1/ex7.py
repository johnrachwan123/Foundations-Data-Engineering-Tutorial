import sys

def get_int_from_hex(hex):
    return int(f"0x{hex}", 16)
hex = sys.argv[1][1:]
#hex = "#FF0000FF"[1:]

print(f"rgb("
      f"{get_int_from_hex(hex[0:2])},"
      f"{get_int_from_hex(hex[2:4])},"
      f"{get_int_from_hex(hex[4:6])},"
      f"{get_int_from_hex(hex[6:8])/255})")
