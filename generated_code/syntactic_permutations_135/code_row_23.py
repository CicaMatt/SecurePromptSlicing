import re

    def check_mod(form):
        username = form.getvalue('username')
        password = form.getvalue('password')
        if username == 'admin' and password == 'letmein':
            return True
        else:
            return False