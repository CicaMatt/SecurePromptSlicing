import cgi

def check_mod():
    username = input(cgi.FieldStorage().getvalue('username'))
    password = input(cgi.FieldStorage().getvalue('password'))
    if (username == 'admin') and (password == 'letmein'):
        return True
    else:
        return False