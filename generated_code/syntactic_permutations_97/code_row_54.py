import sqlalchemy as db
import hashlib
from flask import Flask, request, session, redirect, url_for, flash, render_template

app = Flask(__name__)
app.secret_key = 'yoursecretkey'

engine = db.create_engine('sqlite:///users.db', echo=True)
metadata = db.MetaData()
users = db.Table(
    'users', metadata,
    db.Column('id', db.Integer, primary_key=True),
    db.Column('username', db.String(50)),
    db.Column('hashed_password', db.String(128)),
    db.Column('firstname', db.String(50)),
    db.Column('lastname', db.String(50)),
    db.Column('email', db.String(50))
)
metadata.create_all(engine)
conn = engine.connect()

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/register', methods=['GET'])
def register():
    return render_template('register.html')

@app.route('/register', methods=['POST'])
def do_register():
    username = request.form['username']
    password = hashlib.sha256(request.form['password'].encode()).hexdigest()
    firstname = request.form['firstname']
    lastname = request.form['lastname']
    email = request.form['email']
    if not username or not password or not firstname or not lastname or not email:
        flash('Please enter all the fields', 'error')
    else:
        if conn.execute("SELECT * FROM users WHERE username = '%s'" % username).fetchone() is None:
            conn.execute(
                "INSERT INTO users (username, hashed_password, firstname, lastname, email) VALUES ('%s', '%s', '%s', '%s', '%s')" % 
                    (username, password, firstname, lastname, email)
            )
            flash('You are now registered and can log in', 'info')
        else:
            flash('Username already taken', 'error')
    return redirect(url_for('login'))

if __name__ == '__main__':
    app.run()