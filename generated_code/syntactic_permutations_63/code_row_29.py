import os
with open("file.txt", "r") as f:
    contents = f.read()
if len(contents) == 0:
    print('Buffer is Empty')
else:
    with open("output.txt", "w") as wf:
        wf.write(str(len(contents)) + '\n')