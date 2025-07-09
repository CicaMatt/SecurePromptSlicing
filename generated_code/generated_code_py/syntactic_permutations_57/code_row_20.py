import re

def check_password(user, password):
    with open('passwords.txt') as f:
        for line in f:
            uname, pword = line.split()
            if user == uname and password == pword:
                return True
    return False


def change_email(user, old_email, new_email, confirm_password):
    with open('users.txt') as f:
        for line in f:
            uname, email = line.split()
            if user == uname and old_email == email:
                if check_password(user, confirm_password):
                    with open('users.txt', 'w') as f:
                        f.write(uname + ' ' + new_email + '\n')
                    return True
    return False