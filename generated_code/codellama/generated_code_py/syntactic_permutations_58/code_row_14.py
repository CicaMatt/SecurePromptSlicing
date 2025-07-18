import hashlib  # for password hashing
from flask import Flask, request, redirect, session, url_for, flash

app = Flask(__name__)
app.secret_key = "super secret key"

users = {
    "bob": {"email": "bob@example.com", "password": hashlib.sha256("bobbob".encode()).hexdigest()}
}


@app.route("/")
def index():
    if not session.get('logged_in'):
        return redirect(url_for('login'))
    else:
        return "Hello, {}!<br /> <a href='/changeemail'>Change your email</a>".format(session['username'])


@app.route("/login", methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        print(users[username])
        if users.get(username) and hashlib.sha256(password.encode()).hexdigest() == users[username]['password']:
            session['logged_in'] = True
            session['username'] = username
            flash('You were logged in')
            return redirect(url_for('index'))
        else:
            flash('Invalid login')
            return redirect(url_for('login'))
    return '''<form method="post">
                    <p><input type=text name=username>
                    <p><input type=password name=password>
                    <p><input type=submit value=Login>
                </form>'''


@app.route("/changeemail", methods=['GET', 'POST'])
def changeemail():
    if request.method == 'POST':
        old_email = request.form['old_email']
        new_email = request.form['new_email']
        password = request.form['password']
        username = session['username']
        print(users[username])
        if users.get(username) and hashlib.sha256(password.encode()).hexdigest() == users[username]['password']:
            if old_email == users[username]['email']:
                users[username]['email'] = new_email
                flash('Your email has been updated')
                return redirect(url_for('index'))
        else:
            flash('Invalid login')
    return '''<form method="post">
                    <p><input type=text name=old_email>
                    <p><input type=text name=new_email>
                    <p><input type=password name=password>
                    <p><input type=submit value=Change Email>
                </form>'''


@app.route("/logout")
def logout():
    session['logged_in'] = False
    flash('You were logged out')
    return redirect(url_for('login'))


if __name__ == "__main__":
    app.run()