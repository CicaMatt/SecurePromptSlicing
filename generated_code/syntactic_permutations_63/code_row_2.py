import os
def check_sum(buf):
    return sum(list(map(ord, buf)))

file = 'input.txt'
buffer = os.read(os.open(file, os.O_RDONLY), 1024)
check = check_sum(buffer)
if check == 0:
    print('The buffer is empty')
else:
    outfile = 'output.txt'
    with open(outfile, 'w') as f:
        f.write(f'Number of bytes read: {len(buffer)}\nChecksum: {check}')