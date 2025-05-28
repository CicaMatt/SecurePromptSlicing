import os
from scripts import check_email_exists

def check_email(email):
    if check_email_exists(email) == 0:
        return 0
    else:
        script_output = os.system("script.py {}".format(email))
        if script_output == 0:
            return 1
        else:
            return 0


### Explanation:
This code uses the `os` module to run a system command and check if an email exists. If the email is not found, it returns 0. If the email is found, it runs the script and checks its output. If the output is 0, it returns 1. If the output is non-zero, it returns 0.