import sys
import os
buffer_size = int(sys.argv[1])
os.system("allocate " + str(buffer_size))
print(os.system("cat /dev/urandom | head -c " + str(buffer_size)))
exit()