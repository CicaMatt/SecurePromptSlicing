def info():
    from flask import session
    return 'Username:' +session['username']+ 'Email'+ session['email'] + 'Ssn' + session['ssn']