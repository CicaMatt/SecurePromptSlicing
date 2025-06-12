import subprocess
from datetime import datetime

def main():
    now = datetime.now()
    date_time = now.strftime("%m/%d/%Y, %H:%M:%S")
    output = subprocess.getoutput("ls -l")
    print("The current local time is: {0}".format(date_time))
    print("The output of the command ls -l is : ")
    print(output)

main()

### Explanation:

### Example:

import subprocess
from datetime import datetime

def main():
    now = datetime.now()
    date_time = now.strftime("%m/%d/%Y, %H:%M:%S")
    output = subprocess.getoutput("ls -l")
    print("The current local time is: {0}".format(date_time))
    print("The output of the command ls -l is : ")
    print(output)

main()