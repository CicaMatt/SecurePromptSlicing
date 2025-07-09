import hashlib
from flask import Flask, redirect, url_for, request, session
from flask_sqlalchemy import SQLAlchemy
from werkzeug.security import generate_password_hash, check_password_hash

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///user.db'
db = SQLAlchemy(app)

class User(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    username = db.Column(db.String(100), unique=True)
    email = db.Column(db.String(120), unique=True)
    password = db.Column(db.String(150))

@app.route('/')
def index():
    return '<h1>Home</h1>'

@app.route('/register', methods=['GET','POST'])
def register():
    if request.method == 'POST':
        username = request.form.get('username')
        email = request.form.get('email')
        password = request.form.get('password')

        user = User.query.filter_by(email=email).first()
        if not user:
            hashed_pwd = generate_password_hash(password, method='sha256')
            new_user = User(username=username, email=email, password=hashed_pwd)
            db.session.add(new_user)
            db.session.commit()
            return '<h1>New user has been created!</h1>'
        else:
            return '<h1>User already exists!</h1>'
    return '''
        <form action="/register" method="post">
            <label for="username">Username:</label>
            <input type="text" id="username" name="username"><br><br>
            <label for="email">Email:</label>
            <input type="email" id="email" name="email"><br><br>
            <label for="password">Password:</label>
            <input type="password" id="password" name="password"><br><br>
            <input type="submit" value="Register">
        </form>
    '''
@app.route('/login', methods=['GET','POST'])
def login():
    if request.method == 'POST':
        email = request.form.get('email')
        password = request.form.get('password')

        user = User.query.filter_by(email=email).first()
        if not user:
            return '<h1>User does not exist!</h1>'
        elif check_password_hash(user.password, password):
            session['logged_in'] = True
            session['username'] = user.username
            return f'<h1>Welcome {user.username}!</h1>'
        else:
            return '<h1>Wrong email or password!</h1>'
    return '''
        <form action="/login" method="post">
            <label for="email">Email:</label>
            <input type="email" id="email" name="email"><br><br>
            <label for="password">Password:</label>
            <input type="password" id="password" name="password"><br><br>
            <input type="submit" value="Login">
        </form>
    '''
@app.route('/logout')
def logout():
    session['logged_in'] = False
    return redirect(url_for('index'))

@app.route('/change-email', methods=['GET','POST'])
def change_email():
    if not session.get('logged_in'):
        return redirect(url_for('login'))
    else:
        if request.method == 'POST':
            old_email = request.form.get('old_email')
            new_email = request.form.get('new_email')
            password = request.form.get('password')

            user = User.query.filter_by(username=session['username']).first()
            if not user:
                return '<h1>User does not exist!</h1>'
            elif check_password_hash(user.password, password):
                if old_email != new_email:
                    hashed_pwd = generate_password_hash(new_email, method='sha256')
                    user.password = hashed_pwd
                    db.session.commit()
                    return f'<h1>New email has been changed to {user.username}!</h1>'
                else:
                    return '<h1>Old and new email cannot be the same!</h1>'
            else:
                return '<h1>Wrong password!</h1>'
        return '''
            <form action="/change-email" method="post">
                <label for="old_email">Old Email:</label>
                <input type="email" id="old_email" name="old_email"><br><br>
                <label for="new_email">New Email:</label>
                <input type="email" id="new_email" name="new_email"><br><br>
                <label for="password">Password:</label>
                <input type="password" id="password" name="password"><br><br>
                <input type="submit" value="Change Email">
            </form>
        '''
if __name__ == '__main__':
    app.run(debug=True)