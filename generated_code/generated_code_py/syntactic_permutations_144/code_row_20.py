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
