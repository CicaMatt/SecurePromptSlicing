import os
import uuid

f = open("random_file.txt", "w")

for _ in range(3):
    f.write(str(uuid.uuid4()))

f.close()