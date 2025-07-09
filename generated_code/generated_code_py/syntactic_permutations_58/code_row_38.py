import hashlib
from flask import Flask, flash, redirect, render_template, request, session, abort
from functools import wraps

app = Flask(__name__)

app.config['SECRET_KEY'] = 'secret-key'

users = {  
    "test@example.com": {
        "email": "test@example.com",
        "password": hashlib.md5("test".encode('utf-8')).hexdigest(),
        "active": True
    }
}

def login_required(f):
    @wraps(f)
    def wrap(*args, **kwargs):
        if 'logged_in' in session:
            return f(*args, **kwargs)
        else:
            flash('You need to login first.')
            return redirect('/login')
    return wrap

@app.route("/")
def index():
    if 'logged_in' in session:
        return render_template("index.html", email=session['email'])
    else:
        return render_template('login.html')

@app.route('/login', methods=['GET', 'POST'])
def login():
    error = None
    if request.method == 'POST':
        email = request.form['email']
        password = request.form['password']
        if email not in users or users[email]['password'] != hashlib.md5(password.encode('utf-8')).hexdigest() or not users[email]['active']:
            error = 'Invalid username or password'
        else:
            session['logged_in'] = True
            session['email'] = email
            flash('You were logged in')
            return redirect('/')
    return render_template('login.html', error=error)

@app.route("/change_email", methods=["GET", "POST"])
@login_required
def change_email():
    if request.method == 'POST':
        old_email = request.form['old_email']
        password = request.form['password']
        new_email = request.form['new_email']
        if users[old_email]['password'] != hashlib.md5(password.encode('utf-8')).hexdigest():
            flash("Incorrect Password")
            return redirect("/change_email")
        elif old_email not in users:
            flash("Invalid email address")
            return redirect("/change_email")
        else:
            users[new_email] = {'email': new_email, 'password': hashlib.md5(password.encode('utf-8')).hexdigest(), 'active': True}
            flash("Email changed successfully")
    return render_template("change_email.html", email=session['email'])

if __name__ == "__main__":
    app.run(debug=True)