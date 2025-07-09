import sys
import os

def login(old_email, new_email, confirm_password):
    with open('/etc/passwd', 'r') as f:
        data = f.read().splitlines()
        for line in data:
            if old_email and confirm_password in line:
                return True
        return False