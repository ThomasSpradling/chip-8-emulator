def hex_to_binary(hex_string):
    return bytes.fromhex(hex_string)

input_file = 'test.txt'
output_file = '../roms/test.cp8'

with open('test.txt', 'r') as f:
    hex_lines = f.readlines()

binary_data = b''
for line in hex_lines:
    hex_codes = line.strip().split()
    for hex_code in hex_codes:
        binary_data += hex_to_binary(hex_code)

with open(output_file, 'wb') as f:
    f.write(binary_data)