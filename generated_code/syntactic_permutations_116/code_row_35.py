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
1. The first line imports subprocess, which is used to execute system commands.
2. The second line imports datetime from datetime, which provides a class for manipulating dates and times.
3. The next line defines the main function that contains the code to be executed.
4. The current date and time are retrieved using now = datetime.now().
5. The format string is created by calling now.strftime("%m/%d/%Y, %H:%M:%S").This formats the date and time according to the specified string.
6. The output of the command ls -l is saved in a variable by calling subprocess.getoutput("ls -l").
7. The first print function prints the current local time using the format string and the date_time variable as its arguments.
8. The second print function prints a statement to indicate that the output of the command ls -l follows.
9. The third print function prints the output of the command ls -l.
10. Finally, the main function is called using main().

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