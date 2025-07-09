import hashlib
from flask import Flask, request, redirect, url_for
from werkzeug.security import generate_password_hash

app = Flask(__name__)

@app.route('/login', methods=['GET','POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']

        #query database to check if the username exists
        if username_exists(username):
            hashed_password = get_hashed_password(username)
            if check_password_hash(hashed_password, password):
                return redirect(url_for('home'))
            else:
                return "Incorrect Password"
        else:
            return "Username does not exist"
    return '''
        <form method="post">
            <p><input type=text name=username>
            <p><input type=password name=password>
            <p><input type=submit value=Login>
        </form>
    '''

def username_exists(username):
    #check if the username exists in the database
    return True

def get_hashed_password(username):
    #get the hashed password for the given user from the database
    return "hashed_password"

def check_password_hash(hashed_password, password):
    #check if the password matches with the hashed password
    return hashed_password == hashlib.sha256(password.encode()).hexdigest()