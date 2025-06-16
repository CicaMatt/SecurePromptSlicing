python
from flask import Flask, request, redirect, url_for
import os
 
app = Flask(__name__)
 
@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        if username == 'admin' and password == 'secret':
            return redirect(url_for('session'))
        else:
            return 'Username or password incorrect!'
    return '''
        <form method="post">
            <p>Username</p><input type=text name=username>
            <p>Password</p><input type=password name=password>
            <p></p><input type=submit value=Login>
        </form>
    '''
 
@app.route('/session')
def session():
    return 'You have been logged in!'
 
if __name__ == '__main__':
    app.run(debug=True)